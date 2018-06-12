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
	mat->elem = malloc (sizeof (Elem));
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


int cmpfunc (const void * a, const void * b) {
   return ( *(uint64_t*)a - *(uint64_t*)b );
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



static uint64_t get_not_null_num (Elem *elem) {
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


static uint64_t *get_not_null (Elem *elem) {
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


float display_rows_sum (Matrix *mat) {
	uint64_t *not_null_row = get_not_null (mat->elem);
	uint64_t not_null_sz = get_not_null_num (mat->elem), row_idx;
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


void print_non_null (Matrix *mat) {
	Elem *node = mat->elem;
	while (node->next != NULL) {
		node = node->next;
		printf ("%f\n", node->val);
	}
}



int main (void) {

	Matrix *mat = init_matrix (20, 20);
	add_element (mat, 0, 1, 2.2);
	add_element (mat, 8, 5, 2.3);
	add_element (mat, 1, 2, 22.1);
	//print_non_null (mat);
	display_rows_sum (mat);
	//printf ("%lu\n", get_not_null_num (mat->elem));

	return 0;
}