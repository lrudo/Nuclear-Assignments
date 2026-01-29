#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"
#include "extremum.h"
#include "solve.h"

typedef double (*FuncPT)(double);// A pointer to a function that accepts a double and then returns a double

FuncPT ORIG_FUNC;
double Extremum_DF(double x);


double Extremum_GetExtremum(FuncPT func, double x_init, double *curvature){
  // This function finds the minimum or maximum within a range, which begins at x_init, and returns the value of x where the extremum is. It does this by calculating the first derivative for the function f(x) using the Derivative_FirstD function, and finds the value of x at this extremum by using Newton's Method to solve for f'(x) = 0. It then returns the value of x at the extremum and calculates the curvature, which is the second derivative evaluated at that value of x.


  double x, tol, ddf, extreme; // Declares variable types
  int count;
  count = 0; // The original value for the variable count
  tol = 1.0E-10; // Desired error value to reach
  ORIG_FUNC = func; // was *func
  extreme = Solve_Newton(0.0, Extremum_DF, x_init, tol, &count); // Solves f'(x) = 0 using Newton's Method where x_init is the original value for x, count is the number of times the function is called, and tol is the desired error value to reach.
  ddf = Derivative_SecondD(extreme, ORIG_FUNC); // Calculates the second derivative of f(x) and evaluates it at the extremum.
  *curvature = (ddf); // Declares the value for curvature, which is the second derivative of f(x), ddf, evaluated at the extremum.
  return extreme;
}


double Extremum_DF(double x){
  double df;
  df = Derivative_FirstD(x, ORIG_FUNC);// Calculates the first derivative df for an arbitrary function f(x)
  return df;
}
