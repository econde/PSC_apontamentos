Árvore binária
==============

Uma árvore binária é um caso particular de contentor de pares chave/valor.
Quando balanceada apresenta custo de pesquisa de ordem :math:`log_2 N`.

Nesta secção é estudada uma árvore binária de utilização genérica,
formada por nós do tipo ``struct tree_node``. ::

   struct tree_node {
   	struct tree_node *left, *right;
   	void *data;
   };

O campo ``data`` aponta para os dados de utilização.
A associação chave/valor é baseada nos dados de utilização.

No programa contador de palavras os elementos de dados são a ``struct word``,
a chave de ordenação é a própria palavra contida nesta *struct*. ::

   struct word {
   	const char *text;
   	int counter;
   };

O contentor de palavras é representada por um ponteiro para ``struct tree_node``,
que deve ser inicializado com ``NULL`` para representar uma árvore vazia -- linha 20.

.. literalinclude:: ../../../code/data_structures/word_counter/wcounter_tree.c
   :language: c
   :lines: 31-85
   :linenos:
   :caption: Programa contador de palavras baseado em árvore binária (tree.c)

A fase de leitura e contabilização de palavras processa-se entre as linhas 23 e 45.
Depois da leitura (linha 23), a palavra é procurada no contentor de palavras
com a função ``tree_search``. Se a palavra já existir (``node != NULL``)
o respetivo contador é incrementado (linha 29).
Se a palavra ainda não exitir,
é necessário alocar memória para um novo objeto ``struct word`` (linha 32),
preenchê-lo com a informação da palavra (linhas 37 a 42)
e por fim inseri-lo no contentor de palavras (linha 43).

Terminda a recolha de palavras, e depois de apresentados os resultados (linhas 46 a 50),
são libertados os recursos.
No que respeita ao contentor de palavras,
primeiro percorre-se a àrvore e eliminam-se os objectos com a informação das palavras
-- todas as ``struct word`` (linha 53).
Em seguida, elimina-se a própria àrvore -- todas as ``struct tree`` (linhas 54).

Inserir nova palavra
....................

A operação de inserção inclui a procura do local de inserção.
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
   :lines: 25-41
   :linenos:
   :caption: Inserir nó na árvore (tree.c)

Procurar palavra
................

A operação de procura da palavra é realizada pela função ``tree_search``.
Esta função recebe a chave de informação a procurar (``key``)
e a função de comparação ``compare``.
Esta função é invocada com o ponteiro para o elemento de informação de cada nó (``node->data``)
e a chave de procura -- linha 5.
Se devolver o valor zero, significa que o ponteiro ``node``
aponta para o nó que contém a informação procurada.
Se devolver um valor positivo a procura continua na sub-árvore direita.
Se devolver um valor negativo a procura continua na sub-árvore esquerda.

.. literalinclude:: ../../../code/data_structures/src/tree.c
   :language: c
   :lines: 12-23
   :linenos:
   :caption: Procurar elemento na árvore (tree.c)


Ambas as funções recebem a mesma função de comparação ``word_cmp_text``
que compara a palavra presente num nó da árvore, acessível pelo parâmetro a,
com uma segunda palavra, acessível pelo parâmetro b.

Não faz sentido a função de comparação ser diferente nas funções de inserção e nas funções de procura.

Alternativas de implementação:
Esta função poderia ser intrínseca à própria árvore e definida no momento da sua criação/inicialização.

tree_insert
