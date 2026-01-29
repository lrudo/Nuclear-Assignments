#ifndef EXTREMUM_H
#define EXTREMUM_H

typedef double (*FuncPT)(double);
double Extremum_GetExtremum(FuncPT func, double x_init, double *curvature);


#endif
