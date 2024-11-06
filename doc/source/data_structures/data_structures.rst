Estruturas de dados dinâmicas
*****************************

Na linguagem C a gestão dinâmica da memória é realizada manualmente.
O programador, ao escrever código, tem que manter uma consciência permanente
sobre a utilização da memória.

Estruturas de dados dinâmicas tratadas:
   * Lista ligada
   * Árvore binária
   * Array dinâmico
   * Tabela de dispersão (*hash table*)

O estudo destas estruturas de dados é suportado em dois programas de aplicação.
Um programa de simulação de uma fila de espera, no estudo das listas ligadas
e um programa de contagem de palavras, no estudo das restantes estruturas.

Nas listas ligadas, vai ser feita uma evolução,
desde realizações elementares até realizações mais elaboradas,
concretizadas em diferentes versões do programa de simulação da fila de espera.

.. toctree::
   :maxdepth: 1

   waiting_queue.rst

.. toctree::
   :maxdepth: 2

   list.rst

No estudo das restantes estruturas de dados,
são realizadas diferentes versões do programa de contagem de palavras,
empregando em cada versão,
uma estrutura de dados diferente como contentor de palavras.

.. toctree::
   :maxdepth: 1

   word_counter.rst

.. toctree::
   :maxdepth: 1

   dynamic_array.rst
   tree.rst
   hash_table.rst

Referências
===========
