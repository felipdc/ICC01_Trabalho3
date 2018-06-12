#ifndef _MAIN_H_
#define _MAIN_H_

struct elem {
	uint64_t row_idx, col_idx;
	float val;
	struct elem *next;
}; typedef struct elem Elem;


struct matrix {
	uint64_t m, n;
	Elem *elem;
}; typedef struct matrix Matrix;


Matrix *init_matrix (uint64_t m, uint64_t n);
int cmpfunc (const void * a, const void * b);
float get_element (Matrix *mat, uint64_t m, uint64_t n);

static uint64_t *get_not_null_col (Elem *elem);
static uint64_t get_not_null_col_num (Elem *elem);
static uint64_t get_not_null_row_num (Elem *elem);
static uint64_t *get_not_null_row (Elem *elem);

void add_element (Matrix *mat, uint64_t m, uint64_t n, float val);
void freeMatrix (Matrix *mat);
void display_rows_sum (Matrix *mat);
void display_cols_sum (Matrix *mat);


#endif /* _MAIN_H_ */