#ifndef NUMEROV_PARAMS_H
#define NUMEROV_PARAMS_H
#include "params.h"


typedef double (*Func_1D)(double, DynamicParams *);
// This defines Func_1D to be a pointer to functions
// that takes a double variable and a DynamicParams type variable
// and returns a double precision number.
// DynamicParams is defined in params.h

typedef struct numerov_params{
  double x_f;
  double x_i;
  double y_0;
  double y_1;
  int nmax;
  double h;

  Func_1D NumerovFunc_F; // The function F in y" = Fy
} NumerovParams; // Define a data type named NumerovParams

#endif
