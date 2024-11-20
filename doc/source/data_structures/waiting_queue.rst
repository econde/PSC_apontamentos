Programa de simulação de fila de espera
=======================================

O estudo da estrutura de dados **lista ligada** em linguagem C, aqui apresentado,
vai ser suportado num programa de aplicação
que simula uma fila de espera de utentes para um serviço.

A fila de espera é representada por uma lista ligada
em que cada elemento da lista corresponde a um utente na fila.

São realizadas várias versões do programa para exemplificar a utilização
de diversos tipos de lista e técnicas de programação em linguagem C.

Na perpetiva do utilizador,
o programa tem o mesmo comportamento em todas as versões.
A atividade principal do programa,
consiste em realizar ciclos sucessivos de aceitação e execução de comandos.

Os comandos disponíveis são os mostrados na função ``help``.
O utilizador identifica o comando através de uma letra,
eventualmente seguida de um argumento.

.. literalinclude:: ../../../code/data_structures/waiting_queue/wqueue1.c
   :language: c
   :lines: 121-130
   :linenos:
   :caption: Comandos do programa de simulação de fila de espera.

A letra identificadora do comando e o argumento são isolados utilizando a função
``strtok`` -- :numref:`wqueue_main` linhas 7 e 10.
Considera-se que o utilizador escreve sempre bem a entrada de comando.

A manipulação da lista ligada é realizada nas funções de execução dos comandos
(``user_insert``, ``user_remove``, ``user_answer``, etc).
A utilização de diferentes listas ligadas concretiza-se em diferentes
realizações destas funções.

.. literalinclude:: ../../../code/data_structures/waiting_queue/wqueue1.c
   :language: c
   :lines: 132-170
   :linenos:
   :name: wqueue_main
   :caption: Atividade principal do programa de simulação de fila de espera.
