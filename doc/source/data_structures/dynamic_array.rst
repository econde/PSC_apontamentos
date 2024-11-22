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

Nesta versão do programa contador de palavras é utilizado um *array* dinâmico de objetos do tipo

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :lines: 18-21

O *array* é referenciado pelo ponteiro ``words``
e representado por uma estrutura ``struct vector`` criada dinamicamente.

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :lines: 23

O ciclo de processamento de palavras consiste na leitura de palavra (linha 7),
na procura da palavra (linha 10)
e pela inserção, se a palavra ainda não estiver presente (linhas 15 a 17).

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_vector.c
   :language: c
   :linenos:
   :lines: 48-49,54-67,72-83
   :caption: Contagem de palavras baseada em *array* dinâmico
   :name: wcounter_vector_main

Criação do *array*
------------------

O *array* dinâmico é criado pela função ``vector_create`` (linha 4). 
O primeiro argumento é a dimensão dos elementos do *array*
e o segundo argumento é o acréscimo, em número de elementos, quando o
*array* é aumentado. A utilização do valor 2 é por acaso.
  
O *array* dinâmico genérico é baseado na ``struct vector``.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :lines: 7-10

* O campo ``buffer`` aponta a zona da memória de dados do *array*.
* O campo ``element_size`` a dimensão dos elementos do *array*, em número de bytes.
* O campo ``current_size`` o atual número de elementos.
* O campo ``max_size`` a capacidade da memória alocada, em número de elementos.
* O campo ``chunck_size`` o acréscimo, em número de elementos, quando o *array* for aumentado.

vector_create
.............

A função ``vector_create`` aloca memória para a ``struct vector`` (linha 2)
e para a zona de dados do *array* (linha 5). 

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 12-27

Procura da palavra
------------------

Cada palavra lida do texto é procurada no *array*.
O *array* é mantido ordenado para permitir
a utilização de pesquisa dicotómica que tem custo :math:`log_2 N`.

A procura é realizada pela função ``vector_sorted_search``.
Recebe como argumentos a palavra a procurar e a função de comparação.
Devolve duas informações: se encontrou -- o índice onde se encontra; 
ou se não encontrou -- o índice onde deveria encontrar.

vector_sorted_search
....................

Esta função assume que o *array* se encontra ondenado
com um critério compatível com a função de comparação recebida no parâmetro ``compare``.
Essa função devolve um valor positivo se o primeiro argumento for de ordem superior ao segundo,
um valor negativo se for de ordem inferior ou zero se forem da mesma ordem (iguais).

Esta função aplica um algoritmo de procura dicotómica subdividindo o *array*
em sucessivas metades até encontrar o elemento procurado
ou até não poder subdividir mais,
o que significa que o elemento procurado não está no *array*.

A variável ``ref`` serve para anotar a posição do *array*
onde o elemento procurado se deveria encontrar, caso estivesse presente.
Este valor é devolvido através do parâmetro de saída ``index``.
O objetivo é poder vir a seu utilizado na inserção desse elemento,
mantendo a ordenação, e dispensando uma nova procura.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 39-61
   
Inserção de palavra
-------------------

A inserção de uma nova palavra dá-se nas linhas 15 a 17.
Ocorre depois de se verificar que a palavra ainda não existe no *array*.

Na inserção é utilizada a variável local ``w`` alojada em *stack* (linha 15)
onde se concentra a informação relativa à palavra
-- o ponteiro para o texto da palavra e o contador.
A inserção é realizada pela função ``vector_insert``, 
que recebe o ponteiro para ``w`` e copia o conteúdo apontado
para a posição ``index`` do *array*.

É utilizado o valor de ``index`` devolvido pela função ``vector_sorted_search``
com a posição do *array* onde o elemento deve ser inserido para manter a ordenação.
Este aproveitamento dispensa uma nova procura da posição de inserção.

vector_insert
.............
A função ``vector_insert`` insere o elemento apontado pelo parâmetro ``element``
na posição indicada por ``index``.

Se essa posição estiver aquém da dimensão atual (linha 14),
os elementos das posições seguintes são deslocados uma posição para a frente (linhas 21 a 23).

Devido a este deslocamento, se toda a memória alocada estiver utilizada,
é necessário aumentar a porção de memória alocada (linha 15).

Se essa posição estiver além da memória alocada (linha 4),
a alocação de memória é aumentada até cobrir a posição indicada (linhas 5 e 6).

O aumento de memória afeta aos dados do *array*
implica alocar um novo bloco, copiar os dados do bloco antigo para o novo bloco
e libertar o bloco antigo. 

A função ``realloc``, pertencente à biblioteca normalizada da linguagem C,
satisfaz esta necessidade.
Recebe o ponteiro para um bloco de memória previamente alocado
e uma nova dimensão e altera a dimensão desse bloco para essa dimensão,
mantendo o conteúdo de dados.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 147-174

Eliminação do *array*
---------------------

Quando os dados no *array* e o próprio *array* não são mais necessários, deve-se
libertar os recursos de memória associados. Essa libertação decorre em duas fases,
a libertação dos elementos seguida da eliminação do próprio *array*.
A primeira deve ser realizada no contexto de utilização, na :numref:`wcounter_vector_main`,
linha 26, são percorridas todas as posições do *array*, invocando em *callback* a função ``free_word``.
A segunda é realizada pela função ``vector_destroy`` (:numref:`wcounter_vector_main`,
linha 27). 

vector_destroy
..............

A função ``vector_destroy`` liberta a memória alocada para os dados do *array* (linha 3).
Esta memória foi alocada na função ``vector_create`` utilizando a função ``malloc``
ou numa expansão utilizando a função ``realloc``.
Por último liberta a memória da própria ``struct vector``.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 29-33


vector_at
.........

Devolve o ponteiro para a posição do *array* indicada pelo parâmetro ``index``.
A partir deste ponteiro, e aplicando aritmética de ponteiros,
pode-se obter o ponteiro para outras posições do *array*.

.. literalinclude:: ../../../code/data_structures/src/vector.c
   :language: c
   :linenos:
   :lines: 127-130

   
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
   :lines: 188-191

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
   :lines: 222-226
