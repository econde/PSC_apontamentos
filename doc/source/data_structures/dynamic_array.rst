*Array* dinâmico
================

Um *array* carateriza-se por ser uma sequência de objetos               
alojados em posições de memória contíguas.
Tem como principais vantagens, a possibilidade de acesso direto aos elementos
a custo unitário e, quando ordenado, permite pesquisa dicotómica a custo :math:`log_2 N`.

Designa-se por *array* estático um *array* cuja dimensão não pode ser alterada
durante a execução do programa.
Um *array* estático pode ser definido em tempo de compilação
-- os *arrays* próprios da linguagem --
ou ser definidos em tempo de execução
-- os *arrays* de âmbito local alojados em *stack*
ou os alojados dinamicamente com a função ``malloc``.

Designa-se por *array* dinâmico um *array* cuja dimensão pode variar durante
a execução do programa.
A sua concretização basea-se na realocação da memória de suporte de dados
à medida da necessidade.
Por exemplo, a escrita numa posição além da dimensão atual do *array*,
pode desencadear uma operação de subtituição da zona da memória de suporte de dados
por uma zona de memória de dimensão maior.

No programa contador de palavras é utilizado um *array* dinâmico de objetos do tipo

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :lines: 11-14

O *array* é referenciado pelo ponteiro ``words``
e representado por uma estrutura ``struct vector``

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :lines: 22

criada dinamicamente.

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :lines: 47

O primeiro argumento de ``vector_create`` é a dimensão do elemento
e o segundo argumento é o acréscimo, em número de elementos, quando o
*array* é aumentado. A utilização do valor 2 é por acaso.

O ciclo de processamento de palavras consiste na leitura de palavra -- linha 11,
na procura da palavra pela função ``vector_sorted_search`` -- linha 14
e pela inserção se a palavra ainda não estiver presente -- linhas 19 a 25.

Para a inserção é utilizada a variável local ``w`` alojada em *stack* -- linha 19.
A inserção é realizada pela função ``vector_insert``
que copia o conteúdo de ``word`` para a posição ``index`` do *array*.
É utilizado o valor de ``index`` devolvido pela função ``vector_sorted_searc``
com a posição do *array* onde o elemento deve ser inserido para manter a ordenação.
Este aproveitamento dispensa uma nova procura da posição de inserção.

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :linenos:
   :lines: 47-48,53-66,71-82

Implementação
-------------

O *array* dinâmico genérico é baseado na ``struct vector``.

.. literalinclude:: ../../../code/data_structures/include/vector.h
   :language: c
   :lines: 4-7

* O campo ``buffer`` aponta a zona da memória de dados do *array*.
* O campo ``element_size`` a dimensão dos elementos do *array*, em número de bytes.
* O campo ``currente_size`` o número de elementos atual.
* O campo ``max_size`` a capacidade da memória alocada.
* O campo ``chunck_size`` o acréscimo de elementos quando o *array* for aumentado.

vector_create
.............

A função ``vector_create`` aloca memória para a ``struct vector`` (linha 2)
e para a zona de dados do *array* (linha 5). 

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 7-21

vector_destroy
..............

A função ``vector_destroy`` liberta a memória alocada para os dados do *array* (linha 2).
Esta memória foi alocada na função ``vector_create`` utilizando a função ``malloc``
ou numa expansão utilizando a função ``realloc``.
Por último liberta a memória da própria ``struct vector``.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 23-26


vector_sorted_search
....................

Esta função assume que o *array* se encontra ondenado
com o critério da função de comparação recebida no parâmetro ``compare``.
Esta função devolve um valor positivo se o primeiro argumento for de ordem superior ao segundo,
um valor negativo se for de ordem inferior ou zero se forem da mesma ordem (iguais).

Esta função aplica um algoritmo de procura dicotómico subdividindo o *array*
em sucessivas metades até encontrar o elemento procurado
ou até não poder subdividir mais, o que significa que o elemento procurado não está no *array*.

A variável ``ref`` serve para anotar a posição onde um elemento deve ser inserido,
caso não esteja presente, e se pretenda manter a ordenação.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 32-53

vector_at
.........

Devolve o ponteiro para a posição do *array* indicada pelo parâmetro ``index``.
A partir deste ponteiro, e aplicando aritmética de ponteiros,
pode-se obter o ponteiro para outras posições do *array*.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 116-118

vector_insert
.............

   
   
A função ``realloc`` pertencente à biblioteca normalizada da linguagem C
ajusta-se a esta necessidade.
Formalmente, recebe a referência para um bloco de memória previamente alocado
e uma dimensão e altera a dimensão desse bloco para essa dimensão.

A operação de alteração da memória de suporte de dados
implica alocar um novo bloco, copiar os dados do bloco antigo para o novo bloco
e libertar o bloco antigo. 



Insere o elemento referenciado pelo parâmetro ``element``
na posição indicada por ``index``.

Se essa posição estiver além da memória alocada (linha 4),
a alocação de memória é aumentada até cobrir a posição desejada (linhas 5-6).

Se essa posição estiver aquém da dimensão atual do *array* (linha 14),
os elementos das posições seguintes são deslocados uma posição para frente (linhas 21-23).

Se nessa altura toda a memória alocada estiver a ser usada (linha 15),
a alocação é aumentada de uma porção ``chunck_size`` (linhas 16-17).

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 134-160

vector_sort
...........

Ordena o *array* por ordem crescente. Utiliza a função
`qsort <https://en.cppreference.com/w/c/algorithm/qsort>`_
pertencente à biblioteca normalizada da linguagem C, que aplica o algoritmo *quick-sort*.

A comparação dos elementos é realizada por uma função dada pelo programa utilizador -- ``compare``.
A função retorna um valor positivo se o primeiro argumento for de ordem superior ao segundo,
um valor negativo se for de ordem inferior e zero se forem da mesma ordem (iguais).
A função de comparação, quando invocada, recebe os ponteiros para dois elementos
do *array* que o algoritmo de ordenção determine comparar.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 173-175

vector_foreach
..............

Itera sobre todas as posições do *array*,
invocando a função passada no parâmetro ``do_it`` em cada iteração.
Em cada invocação são passados como primeiro argumento o ponteiro para o elemento
corrente do *array* e como segundo argumento o ponteiro recebido no parâmetro ``context``.
O parâmetro ``context`` é opaco do ponto de vista desta função e serve para o código utilizador
passar informação de contexto à função ``do_it``.

Os parâmetros da função ``do_it`` não são ``const`` para permitir
a que esta função realize modificações aos elementos do *array*
assim como ao objeto de contexto.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 206-209

  
