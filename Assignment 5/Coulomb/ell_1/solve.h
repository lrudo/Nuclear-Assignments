#ifndef SOLVE_H
#define SOLVE_H

double Solve_Bisect
(double nu, double (*func)(double), double x_min, double x_max, double tol, int *count);

double Solve_Newton
(double nu, double (*func)(double), double x_0, double tol, int *count);

#endif
