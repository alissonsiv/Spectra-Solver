#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "io.h"

// Conta quantas linhas tem no arquivo (usado para determinar a dimensão da matriz)
int count_lines(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;

    int lines = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') lines++;
    }

    fclose(fp);
    return lines;
}

// Lê a matriz quadrada de um arquivo e aloca dinamicamente a matriz A e sua dimensão n
int read_matrix_file(const char *filename, double ***A, int *n) {
    int size = count_lines(filename);
    if (size <= 0) {
        printf("Erro: arquivo vazio ou nao pode contar linhas\n");
        return 0;
    }

    *n = size;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Erro: nao foi possivel abrir arquivo %s\n", filename);
        return 0;
    }

    *A = alloc_matrix(*n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(fp, "%lf", &((*A)[i][j])) != 1) {
                printf("Erro na leitura da matriz (linha %d, coluna %d)\n", i + 1, j + 1);
                fclose(fp);
                free_matrix(*A, *n);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}
