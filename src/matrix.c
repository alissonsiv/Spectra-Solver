#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// Aloca uma matriz quadrada n x n
double **alloc_matrix(int n) {
    double **m = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        m[i] = malloc(n * sizeof(double));
    return m;
}

// Libera a memória de uma matriz n x n
void free_matrix(double **m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

// Aloca um vetor de tamanho n
double *alloc_vector(int n) {
    return malloc(n * sizeof(double));
}

// Copia matriz A para B (ambas n x n)
void mat_copy(double **A, double **B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];
}

// Multiplicação de matrizes: C = A * B
void mat_mult(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Multiplicação matriz-vetor: y = A * x
void mat_vec_mult(double **A, double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = 0.0;
        for (int j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    }
}

// Produto escalar de dois vetores
double dot(double *x, double *y, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += x[i] * y[i];
    return sum;
}

// Norma 2 de um vetor
double norm(double *x, int n) {
    return sqrt(dot(x, x, n));
}

// Normaliza o vetor x (x / ||x||)
void normalize(double *x, int n) {
    double nrm = norm(x, n);
    if (nrm > 1e-20) {
        for (int i = 0; i < n; i++)
            x[i] /= nrm;
    }
}
