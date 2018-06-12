#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*
 *
 *	A matriz sera inicializada utilizando a estrutura DOK
 *	Veja: https://en.wikipedia.org/wiki/Sparse_matrix
 *	
*/

struct elem {
	uint64_t row_idx, col_idx;
	float val;
	struct elem *next;
}; typedef struct elem Elem;


struct matrix {
	uint64_t m, n;
	Elem *elem;
}; typedef struct matrix Matrix;


Matrix *init_matrix (uint64_t m, uint64_t n) {
	Matrix *mat = malloc (sizeof (Matrix));
	mat->m = m;
	mat->n = n;
	mat->elem = malloc(sizeof(Elem));
	mat->elem->next = NULL;
	return mat;
}

void freeMatrix (Matrix *mat) {
	// Apaga todos os elementos da matriz
	Elem *tmp = mat->elem;
	while (mat->elem != NULL) {
		tmp = mat->elem;
		mat->elem = mat->elem->next;
		free(tmp);
	}

	// Apaga a matriz
	free(mat);
}


float get_element (Matrix *mat, uint64_t m, uint64_t n) {
	Elem *node = mat->elem;
	while (node != NULL) {
		if (node->row_idx == m && node->col_idx == n) {
			return node->val;
		}
		node = node->next;
	}
	return 0;
}


void add_element (Matrix *mat, uint64_t m, uint64_t n, float val) {
	Elem *node = mat->elem;
	// Encontra ultimo elemento da lista
	while (node->next != NULL) {
		node = node->next;
	}
	// Aloca memoria e adiciona elemento
	node->next = malloc (sizeof (Elem));
	node = node->next;
	node->next = NULL;
	node->row_idx = m;
	node->col_idx = n;
	node->val = val;
}



uint64_t get_not_null_num (Elem *elem) {
	Elem *node = elem;
	bool got_row;
	uint64_t *not_null = malloc (sizeof (uint64_t));
	uint64_t not_null_num = 0;

	while (node != NULL) {

		got_row = false;

		for (int i = 0; i < not_null_num; ++i) {
			if (node->row_idx == not_null[i]) {
				node = node->next;
				got_row = true;
				break;
			}
		}

		if (got_row) continue;
		not_null[not_null_num++] = node->row_idx;
		not_null = realloc (not_null, sizeof(uint64_t) * not_null_num);
		node = node->next;
	}

	for (int i = 0; i < not_null_num; ++i) {
		printf ("%lu ", not_null[i]);
	}
	printf ("\n");

	return 0;

}


int main (void) {

	Matrix *mat = init_matrix (20, 20);
	add_element (mat, 10, 5, 23);
	add_element (mat, 2, 5, 21);

	get_not_null_num (mat->elem);

	//printf ("%f\n", get_element (mat, 0, 0));

	return 0;
}