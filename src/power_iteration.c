#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"
#include "power_iteration.h"

// Produto matriz-vetor e normalização já estão em matrix.c

double power_iteration(double **A, int n, double *v, double tol, int max_iter) {
    double *w = malloc(n * sizeof(double));

    // Inicializa v com valores aleatórios
    for (int i = 0; i < n; i++)
        v[i] = (double)rand() / RAND_MAX;
    normalize(v, n);

    double lambda_old = 0.0;
    double lambda = 0.0;

    for (int iter = 0; iter < max_iter; iter++) {
        mat_vec_mult(A, v, w, n);
        lambda = dot(v, w, n);
        normalize(w, n);

        double err = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = v[i] - w[i];
            err += diff * diff;
        }
        err = sqrt(err);

        for (int i = 0; i < n; i++)
            v[i] = w[i];

        if (err < tol)
            break;

        lambda_old = lambda;
    }

    free(w);
    return lambda;
}

void power_iteration_deflation(double **A, int n, double *lambda, double **V, double tol, int max_iter) {
    double **B = alloc_matrix(n);
    mat_copy(A, B, n);

    for (int k = 0; k < 3; k++) {
        lambda[k] = power_iteration(B, n, V[k], tol, max_iter);

        // Deflação: B = B - lambda_k * v_k * v_k^T
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                B[i][j] -= lambda[k] * V[k][i] * V[k][j];
            }
        }
    }

    free_matrix(B, n);
}
