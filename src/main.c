#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "io.h"
#include "power_iteration.h"
#include "qr.h"

#define TOL_QR 1e-12
#define MAX_ITER 10000

#define TOL_PI 1e-8
#define MAX_ITER_PI 10000

int main() {
    char filename[150];
    int n;
    double **A;
    int continuar;

    do {
        printf("Escolha a matriz para carregar (3, 10, 100, 300, 500): ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }

        snprintf(filename, sizeof(filename), "input/mat_%d.txt", choice);

        if (!read_matrix_file(filename, &A, &n)) {
            printf("Erro ao ler matriz %s\n", filename);
            return 1;
        }

        printf("\n>>> Matriz %d x %d carregada com sucesso!\n", n, n);

        // --- Power Iteration com deflation ---
        double *lambda_pi = alloc_vector(3);
        double **V = malloc(3 * sizeof(double*));
        for (int i = 0; i < 3; i++)
            V[i] = alloc_vector(n);

        srand(time(NULL));
        clock_t start = clock();
        power_iteration_deflation(A, n, lambda_pi, V, TOL_PI, MAX_ITER_PI);
        clock_t end = clock();
        double time_pi = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n===========================\n");
        printf(" POWER ITERATION COM DEFLATION\n");
        printf("===========================\n");
        printf("Tempo de execucao: %.6fs\n", time_pi);
        for (int i = 0; i < 3; i++)
            printf("  lambda[%d] = %.8f\n", i + 1, lambda_pi[i]);

        // --- QR Iteration sem deslocamento ---
        double *lambda_qr_no = alloc_vector(n);
        start = clock();
        int iter_qr_no = qr_iteration_no_shift(A, n, TOL_QR, MAX_ITER, lambda_qr_no);
        end = clock();
        double time_qr_no = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n===========================\n");
        printf(" QR ITERATION SEM DESLOCAMENTO\n");
        printf("===========================\n");
        printf("Iteracoes:         %d\n", iter_qr_no);
        printf("Tempo de execucao: %.6fs\n", time_qr_no);

        // --- QR Iteration com deslocamento ---
        double *lambda_qr_shift = alloc_vector(n);
        start = clock();
        int iter_qr_shift = qr_shift_iteration(A, n, TOL_QR, MAX_ITER, lambda_qr_shift);
        end = clock();
        double time_qr_shift = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n===========================\n");
        printf(" QR ITERATION COM DESLOCAMENTO\n");
        printf("===========================\n");
        printf("Iteracoes:         %d\n", iter_qr_shift);
        printf("Tempo de execucao: %.6fs\n", time_qr_shift);

        // Libera memória
        free_matrix(A, n);
        free(lambda_pi);
        for (int i = 0; i < 3; i++)
            free(V[i]);
        free(V);
        free(lambda_qr_no);
        free(lambda_qr_shift);

        printf("\n===========================\n");
        printf("Deseja continuar? (1 - Sim, 0 - Nao): ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada invalida. Encerrando programa.\n");
            break;
        }

    } while (continuar == 1);

    printf("\n>>> Programa finalizado.\n");
    return 0;
}
