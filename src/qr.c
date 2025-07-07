#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "qr.h"

// Decomposição QR pelo método de Gram-Schmidt modificado
void qr_decomposition(double **A, int n, double **Q, double **R) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
            Q[i][k] = A[i][k];

        for (int j = 0; j < k; j++) {
            R[j][k] = 0.0;
            for (int i = 0; i < n; i++)
                R[j][k] += Q[i][j] * A[i][k];
            for (int i = 0; i < n; i++)
                Q[i][k] -= R[j][k] * Q[i][j];
        }

        double norm = 0.0;
        for (int i = 0; i < n; i++)
            norm += Q[i][k] * Q[i][k];
        norm = sqrt(norm);
        R[k][k] = norm;
        for (int i = 0; i < n; i++)
            Q[i][k] /= norm;
    }
}

void subtract_shift(double **A, int n, double mu) {
    for (int i = 0; i < n; i++)
        A[i][i] -= mu;
}

void add_shift(double **A, int n, double mu) {
    for (int i = 0; i < n; i++)
        A[i][i] += mu;
}

int qr_shift_iteration(double **A, int n, double tol, int max_iter, double *lambda) {
    double **Ak = alloc_matrix(n);
    double **Q = alloc_matrix(n);
    double **R = alloc_matrix(n);

    mat_copy(A, Ak, n);

    for (int i = 0; i < n; i++)
        lambda[i] = Ak[i][i];

    int iter;
    for (iter = 0; iter < max_iter; iter++) {
        double mu = Ak[n - 1][n - 1];
        subtract_shift(Ak, n, mu);
        qr_decomposition(Ak, n, Q, R);
        mat_mult(R, Q, Ak, n);
        add_shift(Ak, n, mu);

        double diff = 0.0;
        for (int i = 0; i < n; i++)
            diff += fabs(Ak[i][i] - lambda[i]);

        if (diff < tol)
            break;

        for (int i = 0; i < n; i++)
            lambda[i] = Ak[i][i];
    }

    for (int i = 0; i < n; i++)
        lambda[i] = Ak[i][i];

    free_matrix(Ak, n);
    free_matrix(Q, n);
    free_matrix(R, n);

    return iter + 1;
}

int qr_iteration_no_shift(double **A, int n, double tol, int max_iter, double *lambda) {
    double **Ak = alloc_matrix(n);
    double **Q = alloc_matrix(n);
    double **R = alloc_matrix(n);

    mat_copy(A, Ak, n);

    for (int i = 0; i < n; i++)
        lambda[i] = Ak[i][i];

    int iter;
    for (iter = 0; iter < max_iter; iter++) {
        qr_decomposition(Ak, n, Q, R);
        mat_mult(R, Q, Ak, n);

        double diff = 0.0;
        for (int i = 0; i < n; i++)
            diff += fabs(Ak[i][i] - lambda[i]);

        if (diff < tol)
            break;

        for (int i = 0; i < n; i++)
            lambda[i] = Ak[i][i];
    }

    for (int i = 0; i < n; i++)
        lambda[i] = Ak[i][i];

    free_matrix(Ak, n);
    free_matrix(Q, n);
    free_matrix(R, n);

    return iter + 1;
}
