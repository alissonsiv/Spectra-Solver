#ifndef POWER_ITERATION_H
#define POWER_ITERATION_H

double power_iteration(double **A, int n, double *v, double tol, int max_iter);
void power_iteration_deflation(double **A, int n, double *lambda, double **V, double tol, int max_iter);

#endif
