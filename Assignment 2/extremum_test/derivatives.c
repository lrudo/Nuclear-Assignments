#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"



double Derivative_FirstD(double x, double (*func)(double)){
  // This function calculates the first derivative for an arbitrarty function f(x) by way of f'(x) = (f(x+h) - f(x-h))/(2h) where h is a small number.
  double df, h; // Declaring variable types
  h = 1.0E-5; // Unlike in calculus, where we would take the limit as h->0, we set h to be a small enough number, h = 1.0E-5*x, for double precision.
  if(x != 0.0) {h = h*x;} // Setting a new value of h, h = h_old*x, in order to obtain double precision so long as x does not equal 0.
  df = (*func)(x+h) - (*func)(x - h); //
  df /= 2.0*h; // Calculates the value of the derivative df = [f(x+h)-f(x-h)]/2h
  return df;
}


double Derivative_SecondD(double x, double (*func)(double)){
  // This function calculates the second derivative for an arbitrarty function f(x) by way of f"(x) = (f(x+h) + f(x-h) - 2f(x))/(h^2) where h is a small number.
  double ddf, h; //Declaring variable types
  h = 1.0E-5; // Unlike in calculus, where we would take the limit as h->0, we set h to be a small enough number, h = 1.0E-5*x, for double precision.
  if(x != 0.0) {h = h*x;} // Setting a new value of h, h = h_old*x, in order to obtain double precision so long as x does not equal 0.
  ddf = (*func)(x+h) + (*func)(x-h) - 2*(*func)(x);
  ddf /= h*h; // Calculates the value of the second derivative ddf = [f(x+h)+f(x-h)-2f(x)]/(h^2)
  return ddf;
}
