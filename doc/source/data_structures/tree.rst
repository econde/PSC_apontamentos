Árvore binária
==============
Nesta versão do programa contador de palavras é utilizado como
contentor de palavras uma árvore binária de utilização genérica.

Uma árvore binária é um caso particular de contentor de pares chave/valor.
Quando balanceada apresenta custo de pesquisa de ordem :math:`log_2 N`.

Os elementos de dados são a ``struct word``,
a chave de ordenação é o texto da própria palavra contida nesta *struct*.

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_tree.c
   :language: c
   :lines: 18-21


.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_tree.c
   :language: c
   :lines: 34-35,40-53,58-59,64-70,73-76
   :linenos:
   :caption: Programa contador de palavras baseado em árvore binária (wcounter_tree.c)
   :name: wcounter_tree_main

A fase de leitura e contabilização de palavras processa-se entre as linhas 7 e 29.
Depois da leitura (linha 7), a palavra é procurada no contentor de palavras
com a função ``tree_search``. Se a palavra já existir (``node != NULL``)
o respetivo contador é incrementado (linha 13).
Se a palavra ainda não exitir,
é necessário alocar memória para um novo objeto ``struct word`` (linha 16),
preenchê-lo com a informação da palavra (linhas 17 e 18)
e por fim inseri-lo no contentor de palavras (linha 19).

Terminda a recolha de palavras, e depois de apresentados os resultados (linhas 22 a 26),
são libertados os recursos alocados.
No que respeita ao contentor de palavras,
primeiro percorre-se a àrvore e eliminam-se os objectos com a informação das palavras
-- todas as ``struct word`` (linha 28).
Em seguida, elimina-se a própria àrvore -- todas as ``struct tree`` (linhas 29).

Criação da árvore
-----------------

A árcore binária genérica é formada por nós do tipo  ``struct tree_node``.

.. literalinclude:: ../../../code/data_structures/src/tree.c
   :language: c
   :lines: 4-7


Os campos ``left`` e ``right`` apontam, respetivamente, para as sub-árvores esquerda e direita.
O campo ``data`` aponta para os dados de utilização.

A associação chave/valor é baseada nos dados de utilização.

Uma árvore é representada por um ponteiro para o nó raíz.
Uma árvore vazia não contém qualquer nó.
Por isso, uma árvore vazia é representada pelo valor NULL (linha 4).

Procura da palavra
------------------

A operação de procura da palavra é realizada pela função ``tree_search``.
Esta função recebe a chave de informação a procurar (``&key``)
e a função de comparação ``word_cmp_text``.

``key`` é uma variável local, pois serve apenas para a operação de procura.
Porque é que o ponteiro ``word_text``, que aponta para a palavra acabada de ler,
não pode ser utilizada diretamente como chave de procura?

tree_search
...........

A fução de comparação é invocada com o ponteiro para o elemento de informação de cada nó (``node->data``)
e a chave de procura (linha 5).
Se devolver o valor zero, significa que o ponteiro ``node``
aponta para o nó que contém a informação procurada.
Se devolver um valor positivo a procura continua na sub-árvore direita.
Se devolver um valor negativo a procura continua na sub-árvore esquerda.

.. literalinclude:: ../../../code/data_structures/src/tree.c
   :language: c
   :lines: 17-28
   :linenos:
   :caption: Procurar elemento na árvore (tree.c)

Inserção da palavra
-------------------

tree_insert
...........

A operação de inserção engloba a procura do local de inserção.
Nessa procura, a palavra que se pretende inserir (parâmetro ``data``)
é comparada com as palavras já inseridas.
A comparação é realizada por uma função específica,
fornecida pelo código de utilização,
no parâmetro ``compare``.

Essa função recebe os ponteiros para a palavra corrente
e para a palavra que se pretende inserir -- linha 11.

Se a palavra já existir, caso em que a função de comparação devolve zero,
é retornado o ponteiro para o nó corrente e não é inserido novo nó.
Caso contrário, é realizada uma invocação recursiva na direção da inserção ordenada.
Quando se chega ao ponto em que já não há mais nós descendentes (``root == NULL``)
é altura de criar um novo nó (linhas 4 a 9).

O estabelecimento da ligação de um nó para o nó descendente
é realizado na intância de chamada anterior à instância de criação (linhas 13 e 15).

.. literalinclude:: ../../../code/data_structures/src/tree.c
   :language: c
   :lines: 30-46
   :linenos:
   :caption: Inserir nó na árvore (tree.c)


.. note::

   A função de procura ``tree_search`` e a função de inserção ``tree_insert``
   têm ambas como parâmetro a função de comparação.
   Esta caraterística de interface permite utilizar funções de comparação
   diferentes. Compete ao utilizador garantir
   a compatibilidade das funções a fim de evitar inconsistências.

   Como alternativas de desenho da interface,
   a função de comparação poderia ser intrínseca à própria árvore
   e definida no momento da sua criação/inicialização da árvore.

Eliminação da árvore
--------------------

Quando os dados na árvore e a própria árvore não são mais necessários,
deve-se libertar os recursos de memória associados. Essa libertação decorre em duas fases,
a libertação dos elementos de dados e a eliminação da própria árvore.
A primeira deve ser realizada no contexto de utilização, na :numref:`wcounter_tree_main`,
linha 27, são percorridas todas as posições da árvore, invocando em *callback* a função ``free_word``.
A segunda é realizada pela função ``tree_destroy`` (:numref:`wcounter_tree_main`,
linha 28). 

tree_destroy
............

A função ``tree_destroy`` liberta em cada instância a memória para o nó corrente,
depois de ter percorrido recursivamente as sub-árvores esquerda e direita.

.. literalinclude:: ../../../code/data_structures/src/tree.c
   :language: c
   :linenos:
   :lines: 9-15
