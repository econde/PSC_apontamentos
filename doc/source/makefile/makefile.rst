*Makefile*
**********

Um ficheiro Makefile contém uma sucessão de regras encadeadas.
Uma regra divide-se em três áreas: objetivo, dependências e comandos,
dispostos da seguinte forma:

::

   objetivo: dependências
   <TAB>comando

Uma regra interpreta-se do seguinte modo: se alguma dependência for mais nova
-- tiver uma data de criação ou modificação mais recente -- que o objetivo,
o comando será executado para atualizar o objetivo.

As dependências são ficheiros originais -- ficheiros com código fonte -- ou,
por sua vez, são objetivos de outras regras.

   .. code-block::
      :linenos:
      :caption: Makefile

      main.elf: main.o stack.o
          gcc main.o stack.o -o main.elf

      main.o: main.c
          gcc -c main.c -o main.o

      stack.o: stack.c stack.h
          gcc -c stack.c -o stack.o

      clean:
          rm -rf *.o main.elf

A invocação simples do programa ``make``,
procura o ficheiro com nome ``makefile`` na diretoria corrente
e processa a primeira regra.
No exemplo, a regras das linhas 1 e 2.

::

   $ make

Começa por verificar as dependências. As que forem objetivos de outras regras,
são processadas segundo essas regras. Neste caso ``main.o``
e ``stack.o`` são objetivos de outras regras.
Depois de processadas as dependências,
são comparadas as datas das dependências com a data do objetivo,
neste caso comparadas as datas de ``main.o`` e ``stack.o``
com a data de ``main.elf``.
Se alguma dependência for mais recente que o objetivo o comando ``gcc main.o stack.o -o main.elf`` é acionado.


Se as dependências não forem objetivos de outras regras, são ficheiros originais.
Neste caso passa-se logo para a comparação de datas.
Na segunda regra (linhas 4 e 5) é comparada a data de ``main.o`` -- objetivo
-- com a data de ``main.c`` -- dependência -- se esta for mais recente então
é executado o comando ``gcc -c main.c -o main.o``.

Gerar todos os objetivos presentes em ``makefile`` independentemente das datas:

::

   $ make -B 

Especificar a regra que se pretende aplicar.
Neste caso, apenas a regra ``clean`` que aciona a eliminação os ficheiros intermédios.

::

$ make clean

Usar um ficheiro Makefile com nome diferente de ``makefile``. Por exemplo, ``makelib``.

::

   $ make -f makelib

Num ficheiro Makefile podem usar-se artifícios de escrita para agilizar a sua definição,
designadamente: variáveis; variáveis automáticas; regras implícitas.

A variável ``CFLAGS``, definida na linha 3, é usada para especificar opções de compilação comuns.
É utilizada nas linhas 8 e 11.

A variável ``OBJECTS``, aplicada como dependência da regra das linhas 7 e 8,
permite especificar os ficheiros que irão ser usado para gerar o executável ``main.elf``.

Aos objetivos terminados em ``.o``,
para os quais exista uma dependência com o mesmo nome e terminada em ``.c``,
e não exista um regra explicita, é aplicada a regras implícita das linhas 10 e 11.
Utilizando regras implícitas dispensa-se a escrita de uma regras explicita para cada ficheiro fonte,
o que se traduz em grande simplificação nos projetos extensos.

   .. code-block::
      :linenos:
      
      CC = gcc

      CFLAGS = -Wall -g -Og

      OBJECTS = main.o stack.o

      main.elf: $(OBJECTS)
          $(CC) $(CFLAGS) $^ -o $@

      %.o: %.c
          $(CC) $(CFLAGS) -c -o $@ $<

      clean:
          rm -rf *.o main      

Variáveis automáticas
---------------------

====== =================================================
``$@`` nome completo do objetivo
``$^`` todas as dependências
``$<`` nome da primeira dependência
``$?`` nome das dependência mais recentes que o objetivo
``$*`` nome do objetivo sem a extensão
====== =================================================

Referências
===========

**GNU make** -- http://www.gnu.org/software/make/manual/make.html
