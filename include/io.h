#ifndef IO_H
#define IO_H

int count_lines(const char *filename);
int read_matrix_file(const char *filename, double ***A, int *n);

#endif
