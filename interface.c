#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
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
			"\t# 							   #\n"
			"\t############################################################\n");
}


/**
  * @desc Le numero de linhas e colunas para inicializar matriz
  *
  * @return Retorna struct matrix com memoria alocada 
  *
*/

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


/**
  * @desc Chama a funcao que libera memoria da matriz e seus elementos
  *
  * @param Matrix *$mat - Matriz a ser desalocada da memoria
  *
*/

void option_free (Matrix *mat) {
	if (!freeMatrix (mat)) {
		printf ("Matriz nao existe!\n");
	}
	else printf ("Matriz excluida com sucesso!\n");
}


/**
 * @desc Chama a funcao que encontra elementos na matriz e imprime na tela
 *
 * @param Matrix *$mat - Matriz a ser consultada
 *
*/

void option_find_elem (Matrix *mat) {
	if (mat == NULL) {
		printf ("Matriz nao existe!\n");
		return;
	}
	uint64_t x = read_x (mat->m);
	uint64_t y = read_y (mat->n);
	printf ("%0.2f\n", get_element (mat, x, y));
}	


/**
 * @desc Le do usuario um valor x para ser consultado na matriz
 *
 * @param long unsigned $m - Numero de linhas da matriz
 *
 * @return $x - Valor lido do usuario
*/

uint64_t read_x (uint64_t m) {
	uint64_t x;

	printf ("Insira a coordenada x.\n");
	scanf ("%lu", &x);
	getchar ();

	// Verifica se o input eh vallido
	while (x > m) {
		printf ("Valor inserido incorreto\n"
				"Insira a coordenada x.\n");
		scanf ("%lu", &x);
		getchar ();
	}
	return x;
}


/**
 * @desc Le do usuario um valor y para ser consultado na matriz
 *
 * @param long unsigned $n - Numero de colunas da matriz
 *
 * @return $y - Valor lido do usuario
*/

uint64_t read_y (uint64_t n) {
	uint64_t y;

	printf ("Insira a coordenada y.\n");
	scanf ("%lu", &y);
	getchar ();

	// Verifica se o input eh vallido
	while (y > n) {
		printf ("Valor inserido incorreto\n"
				"Insira a coordenada y.\n");
		scanf ("%lu", &y);
		getchar ();
	}
	return y;
}


/**
 * @desc Imprime na tela a soma das linhas ou das colunas da matriz
 *
 * @param Matrix *$mat - Matriz a ser consultada
 *        bool $row - True imprime linha, false coluna
 *
*/

void get_sum (Matrix *mat, bool row) {
	if (mat == NULL) {
		printf ("Matriz nao existe!\n");
		return;	
	}
	if (row) display_rows_sum (mat);
	else display_cols_sum (mat);
}


/**
 * @desc Adiciona elemento na matriz
 * 
 * @param Matrix *$mat - Matriz a ser adicionado elemento
*/

void option_set_element (Matrix *mat) {
	if (mat == NULL) {
		printf ("Matriz nao existe!\n");
		return;	
	}
	float val;
	uint64_t x = read_x (mat->m);
	uint64_t y = read_y (mat->n);
	printf ("Insira o valor a ser inserido\n");
	scanf ("%f", &val);
	add_element (mat, x, y, val);
}


/**
 * @desc Inicia matriz de exemplo
 *
 * @return Retorna matriz de exemplo
*/

Matrix * init_sample_matrix () {
	// Reseta o time do sistema para gerar posicoes aleatorias
	srand((unsigned int)time(NULL));
	uint64_t rand_x, rand_y;
	float rand_val;
	// Inicia uma matriz 1 milhao x 1 milhao para exemplo
	Matrix *mat = init_matrix (1000000, 1000000);
	// Adiciona 10000 valores em posicoes aleatorias da matriz
	// Valores em float com range ate 1000
	for (int i = 0; i < 10000; ++i) {
		rand_x = rand () % 1000000;
		rand_y = rand () % 1000000;
		rand_val = ((float)rand () / (float)(RAND_MAX)) * 1000;
		add_element (mat, rand_x, rand_y, rand_val);
	}
	return mat;
}


/**
 * @desc Le do usuario as opcoes da tela inicial e chama devidas funcoes
 *
 * @param bool $sample - Caso true, inicia a matriz exemplo
*/

void option_handle (bool sample) {
	Matrix *mat;
	char option_read = ' ';
	int option;

	if (sample) mat = init_sample_matrix ();

	while (option_read != '0') {

		display_splash_screen ();
		scanf ("%c", &option_read);
		getchar (); // Get return input from keyboard
		option = option_read - '0';

		switch (option) {
			case 0:
				return;
			case 1:
				mat = read_init ();
				break;
			case 2:
				option_free (mat);
				break;
			case 3:
				option_find_elem (mat);
				break;
			case 4:
				get_sum (mat, true);
				break;
			case 5:
				get_sum (mat, false);
				break;
			case 6:
				option_set_element (mat);
				break;
			default:
				printf ("Opcao invalida, tente novamente.\n");
		}

		printf ("Pressione ENTER para retornar ao Menu\n");
		getchar ();
	}
}
