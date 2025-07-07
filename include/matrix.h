#ifndef MATRIX_H
#define MATRIX_H

double **alloc_matrix(int n);
void free_matrix(double **m, int n);
double *alloc_vector(int n);
void mat_copy(double **A, double **B, int n);
void mat_mult(double **A, double **B, double **C, int n);
void mat_vec_mult(double **A, double *x, double *y, int n);
double dot(double *x, double *y, int n);
double norm(double *x, int n);
void normalize(double *x, int n);

#endif
