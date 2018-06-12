#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "interface.h"
#include "main.h"

/**
  * @desc Imprime tela inicial com as opcoes do programa
  *
*/
void display_splash_screen () {
	clrscr();
	printf ("\n\t#################### Matrizes Esparsas #####################\n"
			"\t#\t\t\t\t\t\t\t   #\n\t#  Comandos:						   #"												
			"\n\t#\t\t\t\t\t\t\t   #\n\t#  0 - Sair						   #\n"
			"\t#  1 - Iniciar matriz	   				   #\n"
			"\t#  2 - Excluir matriz 					   #\n" 
			"\t#  3 - Consultar valor de elemento da matriz 		   #\n"
			"\t#  4 - Consultar soma de cada linha da matriz 		   #\n"
			"\t#  5 - Consultar soma de cada coluna da matriz		   #\n"
			"\t#  6 - Adicionar elemento na matriz			   #\n"
			"\t#  7 - Salvar e Sair 					   #\n"
			"\t# 							   #\n"
			"\t############################################################\n");
}

Matrix * read_init () {
	uint64_t m, n;

	printf ("Insira o numero de linhas da matriz.\n");
	scanf ("%lu", &m);
	getchar ();

	printf ("Insira o numero de colunas da matriz.\n");
	scanf ("%lu", &n);
	getchar ();

	// Verifica se o input eh vallido
	while (m < 0 || n < 0) {

		printf ("Valor inserido incorreto\n");

		printf ("Insira o numero de linhas da matriz.\n");
		scanf ("%lu", &m);
		getchar ();

		printf ("Insira o numero de colunas da matriz.\n");
		scanf ("%lu", &n);
		getchar ();

	}
	// Inicia a matriz e retorna o endereco dela
	Matrix *mat = init_matrix (m , n);
	if (mat != NULL) {
		printf ("Matriz inicializada com sucesso\n");
		return mat;
	}
	//else
	return NULL;
}

void option_handle () {
	Matrix *mat;
	char option_read = ' ';
	while (option_read != '0') {
		display_splash_screen ();
		scanf ("%c", &option_read);
		getchar (); // Get return input from keyboard
		int option = option_read - '0';
		switch (option) {
			case 0:
				return;
			case 1:
				mat = read_init ();
				break;
			case 2:
				if (freeMatrix (mat)) printf ("Matriz excluida com sucesso!\n");
				else printf ("Matriz nao existe!\n");
				break;
			case 3:
				if (mat == NULL) {
					printf ("Matriz nao existe\n");
					break;
				}
				// Else
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			default:
				printf ("Opcao invalida, tente novamente.\n");
		}
		printf ("Pressione ENTER para retornar ao Menu\n");
		getchar ();
	}
}