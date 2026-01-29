#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "numerov.h"
#include "numerov_params.h"
#include "vector_mtx.h"

void Numerov_Make_Fn(double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params);

void Numerov_Advance_A_Step(double *y, int n, double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params);


void Numerov_Advance(double *y, NumerovParams *N_Params, DynamicParams *D_Params)
// Solves y" = Fy by creating numerov_F[n], allocating an arry, obtaining predetermined parameters for y_0 and y_1, and calculating the value of y_(n+1) given the aforementioned.
{
  double *numerov_F; // Declares variable types
  int n;
  int nmax;

  nmax = N_Params->nmax; // Sets the maximum value of n according to the input_params.txt file

  numerov_F = vector_malloc(nmax+1); // Allocate memory space for numerov_F[0]...numerov_F[nmax]

  Numerov_Make_Fn(numerov_F, N_Params, D_Params); // Make numerov_F[n] to be used in the algorithm


  y[0] = N_Params->y_0; // Getting the initial values from N_Params
  y[1] = N_Params->y_1;

  for(n=2; n<=nmax; n++){
    // Calculates the value of y[n] for n >= 2
    Numerov_Advance_A_Step(y, n, numerov_F, N_Params, D_Params);
  }
  return;
}// Numerov_Advance



void Numerov_Make_Fn(double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params)
// Calculates F(x) for the equation y"=F(x)y(x) by mean of setting the function numerov_F evaluated at an integer n to the NumerovFunc_F function evaluated at x_n with D_Params.
{
  // Declares variable types
  int n;
  double x_n;
  double x_i;
  double h;

  x_i = N_Params->x_i; // Obtains value of x_i from N_Params
  h = N_Params->h; // Obtains value of h from N_Params
  for(n=0; n<=N_Params->nmax; n++){
    // A 'for' loop that ranges the value of n from 0 to nmax at integer steps
    x_n = x_i + h*n; // Calculates the value of x_n based on the integer value of n
    numerov_F[n] = (N_Params->NumerovFunc_F)(x_n, D_Params); // Sets the function numerov_F evaluated at n to the NumerovFunc_F function evaluated at x_n with D_Params
  }
  return;
}// Numerov_Make_Fn



void Numerov_Advance_A_Step(double *y, int n, double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params)
// Calculates
// y[n] = ( 1/(1 - (h^2/12)F[n]) )
//       *( 2(1 + (5h^2/12)F[n-1])y[n-1] - (1 - (h^2/12)F[n-2])y[n-2] )
{
  // Declares variable types
  double h;
  double h2_over_12;

  h = N_Params->h; // Obtains value of h from N_Params
  h2_over_12 = h*h/12; // Calculates h^2/12
  y[n] = 0.0; // Sets y[n] = 0

  if(y[n-1] != 0.0){
    // 'If' statement where we add 2(1 + (5h^2/12)F[n-1])y[n-1] to y[n] only if y[n-1] is non-zero
    y[n] += 2.0*(1 + 5.0*h2_over_12*numerov_F[n-1])*y[n-1];
  }
  if(y[n-2] != 0.0){
    // 'If' statement where we add -(1 - (h^2/12)F[n-2])y[n-2] to y[n] only if y[n-2] is non-zero
    y[n] += -1.0*(1 - h2_over_12*numerov_F[n-2])*y[n-2];
  }
  // y[n] is then finally divided by (1 - (h^2/12)F[n]) and the final value of y[n] is returned
  y[n] /= (1 - h2_over_12*numerov_F[n]);

  return;
}// Numerov_Advance_A_Step
