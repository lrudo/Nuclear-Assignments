#ifndef DERIVATIVES_H
#define DERIVATIVES_H

double Derivative_FirstD(double x, double (*func)(double));
double Derivative_SecondD(double x, double (*func)(double));
//double Solve_Newton
//(double nu, double (*func)(double), double x_0, double tol, int *count);

#endif
