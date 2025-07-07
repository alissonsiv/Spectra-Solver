#ifndef QR_H
#define QR_H

void qr_decomposition(double **A, int n, double **Q, double **R);
int qr_iteration_no_shift(double **A, int n, double tol, int max_iter, double *lambda);
int qr_shift_iteration(double **A, int n, double tol, int max_iter, double *lambda);

#endif
