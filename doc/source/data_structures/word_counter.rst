Programa de contagem de palavras
================================

O programa de contagem de palavras engloba quatro fases:
criação do contentor de palavras; leitura e contabilização das palavras;
apresentação dos resultados e por fim a libertação dos recursos alocados.

As operações necessárias sobre o contentor de palavras são:
a criação, a procura, a inserção, a consulta e a eliminação.

Esqueleto do programa contador de palavras: ::

   int main(int argc, char *argv[]) {
   	FILE *fd = fopen(argv[1], "r");
   	if (NULL == fd) {
   		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
   						argv[1], strerror(errno));
   		return EXIT_FAILURE;
   	}
   	int nwords = 0;
   	words =    	/* criar/inicializar contentor de palavras */
   
   	long initial_timepoint = get_time();
   	char *word_string = word_read(fd);
   	while (word_string != NULL) {
   		nwords++;
   		/*
   		if (palavra já existe no contentor)
   			incrementar contador da palavra
   		else
   			inserir nova palavras no contentor
   		*/
   		word_string = word_read(fd);
   	}
   	long duration = get_time() - initial_timepoint;
   	printf("Total de palavras = %d; "
   	       "Palavras diferentes = %ld; Tempo gasto = %ld ms\n",
   	       nwords, cardinal(words), duration);
   	fclose(fd);
   	/* vazar e eliminar o contentor de palavras */
   }