#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "interface.h"

/**
  * @desc A matriz sera inicializada utilizando a estrutura DOK,
  * como eh sugerido em https://en.wikipedia.org/wiki/Sparse_matrix#Storing_a_sparse_matrix
  *
  * @param long unsined $m - guarda o numero de linhas da matriz
  * 	   long unsigned $n - guarda o numero de colunas da matriz
  *
  * @return mat - retorna a matrix inicializada ou NULL caso a alocacao falhe
*/

Matrix *init_matrix (uint64_t m, uint64_t n) {

	Matrix *mat = malloc (sizeof (Matrix));
	mat->elem = malloc (sizeof (Elem));

	if (mat == NULL || mat->elem == NULL) return NULL;

	// Else
	mat->m = m;
	mat->n = n;
	return mat;
}


/**
  * @desc Apaga a matriz percorrendo todos os elementos adicionados
  *
  * @param Matrix *mat - matriz a ser apagada
  *
  * @return bool $status - true se apagar a matriz com sucesso, false contrario
  *
*/

bool freeMatrix (Matrix *mat) {
	if (mat == NULL) {
		return false;
	}
	// ELSE - Apaga todos os elementos da matriz
	Elem *tmp = mat->elem;
	while (mat->elem != NULL) {
		tmp = mat->elem;
		mat->elem = mat->elem->next;
		free(tmp);
	}
	// Apaga a matriz
	free(mat);
	return true;
}


/**
  * @desc Compara valor de 'a' e 'b' para a func qsort()
  *
  * @param const void * a, const void * b - valores a serem comparados
  *
*/

int cmpfunc (const void * a, const void * b) {
   return ( *(uint64_t*)a - *(uint64_t*)b );
}


/**
  * @desc Retorna um valor na posicao (i, j) da matriz
  *
  * @param Matrix *mat - matriz a ser consultada
  *		   long unsigned i, j - coordenadas do elemento a ser consultado
  *
  *	@return node->val se elemento for nao nulo ou 0 se for nulo
  *
*/

float get_element (Matrix *mat, uint64_t i, uint64_t j) {
	Elem *node = mat->elem;
	while (node != NULL) {
		if (node->row_idx == i && node->col_idx == j) {
			return node->val;
		}
		node = node->next;
	}
	return 0;
}


/**
  * @desc Adiciona um elemento na posicao (m,n) da matriz
  *
  * @param Matrix *mat - matriz a ser consultada
  *		   long unsigned m, n - coordenadas do elemento a ser consultado
  *		   float val - valor a ser adicionado na matriz
  *
*/

void add_element (Matrix *mat, uint64_t m, uint64_t n, float val) {
	Elem *node = mat->elem;
	while (node->next != NULL) {
		node = node->next;
	}
	node->next = malloc (sizeof (Elem));
	node = node->next;
	node->row_idx = m;
	node->col_idx = n;
	node->val = val;
	node->next = NULL;
}


/**
  * @desc Retorna um vetor de long unsined contendo a posicao de colunas
  *		  com elementos nao nulos
  *
  * @param Elem *elem - Elementos da matriz
  *
  * @return long unsigned *not_null - vetor com posicoes de cols nao nulas
  *
*/

static uint64_t *get_not_null_col (Elem *elem) {
	Elem *node = elem;
	bool got_col;
	uint64_t *not_null = malloc (sizeof (uint64_t));
	uint64_t not_null_num = 0;

	while (node->next != NULL) {
		node = node->next;
		got_col = false;

		for (int i = 0; i < not_null_num; ++i) {
			if (node->col_idx == not_null[i]) {
				got_col = true;
				break;
			}
		}

		if (got_col) continue;
		not_null[not_null_num++] = node->col_idx;
		not_null = realloc (not_null, sizeof(uint64_t) * (not_null_num + 1));
	}

	return not_null;

}


/**
  * @desc Retorna a quantidade de colunas com elementos nao nulos
  *
  * @param Elem *elem - Elementos da matriz
  *
  * @return long unsigned not_null_num - numero de colunas nao nulas
  *
*/

static uint64_t get_not_null_col_num (Elem *elem) {
	Elem *node = elem;
	bool got_col;
	uint64_t *not_null = malloc (sizeof (uint64_t));
	uint64_t not_null_num = 0;

	while (node->next != NULL) {
		node = node->next;
		got_col = false;

		for (int i = 0; i < not_null_num; ++i) {
			if (node->col_idx == not_null[i]) {
				got_col = true;
				break;
			}
		}

		if (got_col) continue;
		not_null[not_null_num++] = node->col_idx;
		not_null = realloc (not_null, sizeof(uint64_t) * (not_null_num + 1));
	}

	return not_null_num;

}


/* Veja l109 */

static uint64_t get_not_null_row_num (Elem *elem) {
	Elem *node = elem;
	bool got_row;
	uint64_t *not_null = malloc (sizeof (uint64_t));
	uint64_t not_null_num = 0;

	while (node->next != NULL) {
		node = node->next;
		got_row = false;

		for (int i = 0; i < not_null_num; ++i) {
			if (node->row_idx == not_null[i]) {
				got_row = true;
				break;
			}
		}

		if (got_row) continue;
		not_null[not_null_num++] = node->row_idx;
		not_null = realloc (not_null, sizeof(uint64_t) * (not_null_num + 1));
	}

	return not_null_num;

}


/* Veja l146 */

static uint64_t *get_not_null_row (Elem *elem) {
	Elem *node = elem;
	bool got_row;
	uint64_t *not_null = malloc (sizeof (uint64_t));
	uint64_t not_null_num = 0;

	while (node->next != NULL) {
		node = node->next;
		got_row = false;

		for (int i = 0; i < not_null_num; ++i) {
			if (node->row_idx == not_null[i]) {
				got_row = true;
				break;
			}
		}

		if (got_row) continue;
		not_null[not_null_num++] = node->row_idx;
		not_null = realloc (not_null, sizeof(uint64_t) * (not_null_num + 1));
	}

	return not_null;

}


/**
  * @desc Imprime na tela a soma dos elementos de linhas nao nulas
  *
  * @param Matrix *mat - matriz a ser consultada
  *
*/

void display_rows_sum (Matrix *mat) {
	uint64_t *not_null_row = get_not_null_row (mat->elem);
	uint64_t not_null_sz = get_not_null_row_num (mat->elem), row_idx;
	float hold_sum = 0;
	Elem *node = mat->elem;

	qsort(not_null_row, not_null_sz, sizeof(uint64_t), cmpfunc);

	for (row_idx = 0; row_idx < not_null_sz; ++row_idx) {
		while (node->next != NULL) {
			node = node->next;
			if (node->row_idx == not_null_row[row_idx]) {
				hold_sum += node->val;
			}
		}
		printf ("Linha %lu - Soma = %f\n", not_null_row[row_idx], hold_sum);
		hold_sum = 0;
		node = mat->elem;
	}
}


/* Veja l241 */

void display_cols_sum (Matrix *mat) {
	uint64_t *not_null_col = get_not_null_col (mat->elem);
	uint64_t not_null_sz = get_not_null_col_num (mat->elem), col_idx;
	float hold_sum = 0;
	Elem *node = mat->elem;

	qsort(not_null_col, not_null_sz, sizeof(uint64_t), cmpfunc);

	for (col_idx = 0; col_idx < not_null_sz; ++col_idx) {
		while (node->next != NULL) {
			node = node->next;
			if (node->col_idx == not_null_col[col_idx]) {
				hold_sum += node->val;
			}
		}
		printf ("Coluna %lu - Soma = %f\n", not_null_col[col_idx], hold_sum);
		hold_sum = 0;
		node = mat->elem;
	}
}


int main (void) {	
	option_handle ();
	Matrix *mat = init_matrix (20, 20);
	add_element (mat, 0, 1, 2.2);
	add_element (mat, 8, 5, 2.3);
	add_element (mat, 1, 1, 22.1);
	//print_non_null (mat);
	display_rows_sum (mat);
	display_cols_sum (mat);
	//printf ("%lu\n", get_not_null_num (mat->elem));

	return 0;
}