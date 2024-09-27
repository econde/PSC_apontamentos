*Arrays*, *structs* e ponteiros
*******************************

Array
=====

*Arrays* são sequências de valores do mesmo tipo, dispostas em posições contiguas da memória.

*Array* unidimensional
----------------------

Sintaxe de definição de *array* unidimensional: ::

	type identifier [constant-expression]; 

**Exemplos**

*Array* com cinco elementos do tipo ``int``. ::

   int x[5];

Equivalente em Java: ``int[5] x;``
Equivalente em Kotlin: ``var x: IntArray(5)``

**Exemplo**

*Array* com cinco elementos do tipo ``int`` inicializado com os valores indicados. ::

   int x[] = { 10, 20, 30, 40, 50 };

Equivalente em Java: ``int[] x = { 10, 20, 30, 40, 50 };``
Equivalente em Kotlin: ``var x: IntArray = intArrayOf(10, 20, 30, 40, 50)``

O acesso aos elementos do *array* realiza-se através do operador indexação.
Os índices vão de 0 -- primeira posição -- à dimensão menos um -- última posição.

Em linguagem C não é válido escrever uma expressão de afetação de um *array*
com a totalidade do conteúdo de outro *array*.
Pode-se contudo, realizar a afetação posição a posição.

**Exemplo** ::

   int a[3];
   int b[] = {10, 20, 30}:

::

  a = b;

é inválido em linguagem C.

::

   a[0] = b[0];
   a[1] = b[1];
   a[2] = b[2];

é válido, embora não seja a solução adequada para copiar um *array* extenso.


*Array* multidimensional
------------------------

Ponteiro
========

Os tipos básicos são representados em memória por grupos de células de memória.
Um ponteiro é um grupo de células capaz de guardar um endereço de memória.
Na arquitetura **X86-64** um ponteiro tem a dimensão de 8 *bytes*. ::

   char c;
   char *p = &c;

O operador **&** aplica-se a uma variável e serve para obter o ponteiro para essa variável
(que ao nível da arquitetura do computador é o seu endereço de memória). ::

   *p = 20;

O operador **\*** aplica-se a um ponteiro e dá acesso ao conteúdo da variável apontada (conteúdo de).
Também se designa por operador desreferenciação.

Sendo **q** um ponteiro para inteiro (``int *``), **\*q** representa um valor inteiro
e pode aparecer na escrita de programas em qualquer lugar onde possa aparecer um inteiro.

Mnemónica: **&** -- \"ponteiro para\" **\*** -- \"conteúdo de\"

Ponteiro como argumento de função
=================================

A linguagem C só tem passagem de parâmetros por valor.
O tipo ponteiro permite passar, como valor de um parâmetro,
a referência de uma variável (endereço).
Através desse ponteiro pode-se aceder ao conteúdo da variável,
simulando-se assim uma passagem por referência. ::

   void swap(int *pa, int *pb) {
   	int aux = *pa;
   	*pa = *pb;
   	*pb = aux;
   }

   int a = 22, b = 33;
   int main() {
   	swap(&a, &b);
   }

Ponteiros e arrays
==================
::

   int a[10], *p;

O identificador do array -- ``a`` é equivalente ao ponteiro para a primeira posição -- ``&a[0]``.

``p = a`` é equivalente a ``p = &a[0]``.

``a`` não é uma variável, é um valor constante do tipo ponteiro.
Não é possível realizar ``a++`` ou ``a = p``.

As operações sobre *arrays* com operador indexação podem ser substituidas pela notação de ponteiros.

+---------------------+------------------------------+----------------------------------+
|                     | acesso a conteúdo            | ponteiros para posições do array |
+---------------------+------------------------------+----------------------------------+
|operador indexação   | ``a[0]  a[1]      a[i]``     | ``&a[0]   &a[1]   &a[i]``        |
+---------------------+------------------------------+----------------------------------+
|notação de ponteiro  | ``*a    *(a + 1)  *(a + i)`` | ``a       a + 1   a + i``        |
+---------------------+------------------------------+----------------------------------+

**Exemplo**

Ordenar um array de inteiros. ::

   void sort(int array[], size_t size) {
   	for (size_t i = 0; i < size - 1; ++i)
   		for (size_t j = 0; j < size - i - 1; ++j)
   			if (array[j] > array[j + 1])
   				swap(&array[j], &array[j + 1]);
   }

   void print(int array[], size_t size) {
   	putchar('\n');
   	for (size_t i = 0; i < size; ++i)
   		printf("%d ", array[i]);
   	putchar('\n');
   }

   int array[] = {1, 2, 20, 4, 5, 30, 10, 34, 22};

   int main() {
   	print(array, ARRAY_SIZE(array));
   	sort(array, ARRAY_SIZE(array));
   	print(array, ARRAY_SIZE(array));
  }

Programação alternativa usando notação de ponteiro.
(A utilização de notação de ponteiro pode ter, em algumas arquiteturas,
uma tradução mais eficiente para linguagem máquina). ::

   void sort(int *array, size_t size) {
   	for (size_t i = 0; i < size - 1; ++i)
   		for (int *p = array; p < array + size - i - 1; ++p) {
   			if (*p > *(p + 1))
   				swap(p, p + 1);
   		}
   }

Ponteiro para carateres
=======================

``char message[] = “texto para teste”;`` define ``message`` como um *array* de carateres inicializado com ``"texto para teste"``.

``char *pmessage = “texto para teste”;`` define ``pmessage`` como um ponteiro para caractere,
ao qual foi atribuido o ponteiro para a primeiro caracter da *string* ``"texto para teste"``.

Como um ponteiro pode ser utilizado como endereço base de um **array**,
``pmessage[i]`` representa o mesmo caractere **\'t\'** que ``message[i]``.

*String*
========

Na linguagem C, **string** é uma sequência de raracteres terminada com o caractere cujo código é 0.
Uma *string* é guardada em memória numa variável do tipo *array* de caracteres
cujo conteúdo são os códigos numéricos dos caracteres que compõem a *string*
finalizados pelo código ``'\0'``.

A biblioteca normalizada da linguagem C define funções para manipulação de *strings*.

Array como argumento de função
==============================

Quando se passa um *array* como argumento de função,
efetivamente está-se a passar o ponteiro para a primeira posição do *array*.
Internamente à função, o parâmetro é como uma variável local do tipo ponteiro
para o tipo de elementos do *array*.

A declaração ``void to_upper(char str[])`` é equivalente a ``void to_upper(char *str)``.

Na invocação, o argumento pode ser um identificador de *array*
-- ``to_upper(array)`` sendo ``char array[10]`` -- 
ou uma variável do tipo ponteiro -- ``to_upper(ptr)`` sendo ``char *ptr``.


Aritmética de ponteiros
=======================

Princípio básico: se **p** é um ponteiro para um elemento de um *array*
então **p + 1** é o ponteiro para o elemento seguinte.

Admitindo que a unidade de endereçamento da arquitetura de processador é o *byte*.
Se o tipo **char** ocupar um *byte* em memória, **p + 1** incrementa o endereço de uma unidade.
Se o tipo **float** ocupar quatro *bytes* em memória **p + 1** incrementa o endereço de quatro unidades.

========= ======================================================================================
``p++``   pós-incrementa ``p`` do número de bytes igual à dimensão de um elemento.
``++*p``  pré-incrementa o valor apontado por ``p``.
``*++p``  pré-incrementa o ponteiro e depois desreferencía-o acedendo ao valor apontado.
``*p++``  desreferencía o ponteiro acedendo ao elemento apontado e depois incrementa o ponteiro.
``p + n`` aponta para o elemento ``n`` posições à frente do elemento apontado por ``p``.
``p - q`` representa o número de elementos entre os ponteiros ``p`` e ``q``.
========= ======================================================================================

Não é possível realizar outras operações sobre ponteiros.
Por exemplo, não é possível somar dois ponteiros.


Ponteiro para *void*
====================

Um ponteiro para ``void`` não pode ser desreferenciado, adicionado ou subtraído,
porque o elemento apontado é indefinido.
Por omissão, o compilador **gcc** trata o ponteiro para ``void``
como um ponteiro para ``char`` para efeito de aritmética de ponteiros (não está segundo a norma).
Uma variável do tipo ponteiro para ``void`` pode receber ponteiros de qualquer tipo.
Assim como afetar ponteiros de qualquer tipo.

Array bidimensional
===================

.. table::
   :widths: 20 20

   +-------------------------------------------+-----------------------------+
   | ``char a[6] = “abcd”;``                   | .. image:: array_char.svg   |
   +-------------------------------------------+-----------------------------+
   | ``char a[][6] = {“luis”, “rui”, “ana”};`` | .. image:: array_char_2.svg | 
   +-------------------------------------------+-----------------------------+


**Visualização na memória**

   .. image:: array_char_3.svg

**Exemplo**

Ordenar uma sequência de nomes de pessoas, representados num *array* bidimensional de caracteres.

.. literalinclude:: ../../../code/array_struct_pointer/sort_names/sort_names_array_bi.c
   :language: c
   :linenos:
   :caption: Ordenação de nomes em *array* bidimensional

Array de ponteiros
==================

.. table::
   :widths: 20 20

   +-------------------------------------------+-----------------------------+
   | ``char *a[] = {“luis”, “rui”, “ana”};``   | .. image:: array_char_4.svg | 
   +-------------------------------------------+-----------------------------+

**Visualização na memória**

   .. image:: array_char_5.svg



**Exemplo**

Ordenar uma sequência de nomes de pessoas, representada num *array* de ponteiros para *strings*.

.. literalinclude:: ../../../code/array_struct_pointer/sort_names/sort_names_array_ptr.c
   :language: c
   :linenos:
   :caption: Ordenação de nomes em *array* bidimensional

Argumentos na linha de comando
==============================

As palavras escritas na linha de comando são enviadas como argumentos para o programa.
São passadas como argumentos da função ``main``,
na forma de um *array* de ponteiros para caracteres,
apontando cada posição, para o início de cada palavra. ::

   int main(int argc, char *argv[]);

Por exemplo, na invocação do comando: ::

   $ gcc myprog.c -o myprog

o programa gcc vai receber os seguintes argumentos:

   .. image:: array_char_6.svg

**Exercícios**

   1. Fazer um programa que imprima os argumentos de um programa no terminal.
   2. Fazer uma função para separar as palavras numa linha de texto.
      ``size_t string_split(char *text_line, char *words[], size_t words_size);``
   3. Fazer um programa para listar as últimas **n** linhas do texto de entrada.
      ``$ tail -n``

Opções na linha de comando
--------------------------

As opções na linha de comando são de dois tipos curtas e longas.
As curtas são definidas por um sinal **\'-\'** seguido de uma letra
e as longas são definidas por dois sinais **\'--\'** seguidos de uma palavra.
Há opções com e sem argumento.

A biblioteca POSIX define a função ``getopt`` e um conjunto de variáveis
para auxiliar na programação com opções curtas

::

   #include <unistd.h>

   int getopt(int argc, char *const argv[], const char *optstring);
   extern char *optarg;
   extern int opterr, optind, optopt;
========== =============================================
``optarg`` ponteiro para o argumento da opção
``optind`` índice da opção corrente no *array* ``argv``
``opterr`` indicação da ocorrência de erro
``optopt`` opção onde ocorreu erro
========== =============================================

**Exemplo**

Considere-se um programa apto a receber quatro opções, ``-a`` e ``-b`` com argumento e
 ``-c`` e ``-e`` sem argumento.

Invocações possíveis: ::

   $ program -a aaa -c ccc -d -e argument1 argument2

   $ program argument1 argument2

   $ program -d argument1 -c argument2 -a aaa
 
``argument1`` e ``argument2`` são argumentos do programa e ``aaa`` e ``ccc`` são argumentos as opções.


.. literalinclude:: ../../../code/application/getopt.c
   :language: c
   :linenos:
   :caption: Exemplo de utilização da função ``getopt``.
   
A função ``getopt`` reposiciona o conteúdo de ``argv`` de modo que
em primeiro lugar ficam as opções e respetivos argumentos
e em segundo lugar os argumentos do programa que não são opções.

Variáveis de ambiente
=====================

Variáveis de ambiente são pares chave-valor disponíveis nos ambientes de execução de um programa.

Tanto a chave como o valor são *strings* C.

Podem ser definidas e consultadas através de comandos de linha e programaticamente.

Definir uma variável de ambiente na linha de comando: ::

   $ export MY_DIR=/home/ezequiel/my_dir

Consultar variáveis de ambiente na linha de comando: ::

   $ env | grep MY_DIR
   MY_DIR=/home/ezequiel/my_dir
   
Consultar uma variável de ambiente num programa em C: ::

   #include <stdlib.h>
   #include <stdio.h>

   int main() {
   		const char *name = "MY_DIR";
   		const char *dir = getenv(name);
   		if (dir != NULL)
   			printf("A variável %s é equivalente a %s\n", name, dir);
   	}

Uma variável de ambiente criada num dado processo é propagada para os processos
descendentes, não afeta o sistema na globalidade.


Structs
=======

Ponteiros e structs
===================

Alojamento de struct em memória
===============================

Array de struct
===============

Array de ponteiros para struct
==============================

Structs com cmapos baseados em bits
===================================

Union
=====

