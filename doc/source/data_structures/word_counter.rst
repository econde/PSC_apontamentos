Programa de contagem de palavras
================================

O programa de contagem de palavras engloba quatro fases:
criação do contentor de palavras (linha 4);
leitura e contabilização das palavras (linhas 6 a 14);
apresentação dos resultados (linhas 15 a 18)
e por fim a libertação dos recursos alocados (linhas 19 e 20).

As operações necessárias sobre o contentor de palavras são:
a criação, a procura, a inserção, a consulta e a eliminação.

Esqueleto do programa contador de palavras:

   .. code-block:: c
      :linenos:
      
      int main(int argc, char *argv[]) {
      	FILE *fd = fopen(argv[1], "r");
      	int nwords = 0;
      	// criar e inicializar contentor de palavras
      	long initial_timepoint = get_time();
      	char *word_string = read_word(fd);
      	while (word_string != NULL) {
      		nwords++;
      		// if (palavra já existe no contentor)
      		//	incrementar contador da palavra
      		// else
      		//	inserir nova palavras no contentor
      		word_string = read_word(fd);
      	}
      	long duration = get_time() - initial_timepoint;
      	printf("Total de palavras = %d; "
      	       "Palavras diferentes = %ld; Tempo gasto = %ld ms\n",
      	       nwords, cardinal(words), duration);
      	fclose(fd);
      	// eliminar o contentor de palavras
      }
   
