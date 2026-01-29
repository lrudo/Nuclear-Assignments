#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "extremum.h"

double test_func(double x);

int main(void){

  // This is the file where we state our original value of x, x_init, create a writeable .dat file for our results, and solve x for f'(x) = 0. This x is our x_extremum, our value of x at the minimum or maximum of f(x), which we then use to evaluate the function f(x) at i.e. f(x_extremum). A .dat file of the values of x_extremum, f_extremum (f(x) evaluated at x_extremum), and the curvature (which is the value of f"(x_extremum)) is then created.

  double x_init, curvature, test_func_extreme, x_extremum; // Declares variable types
  x_init = 0.5; // Sets the initial value of x
  FILE *output;
  x_extremum = Extremum_GetExtremum(test_func, x_init, &curvature); // Calculates the extremum using Newton's Method to solve for f'(x) = 0 for the initial value x_init as well as the value of the curvature
  test_func_extreme = test_func(x_extremum); // Evaluates f(x) at x_extremum
  output = fopen("261023938_CA_2_Results.dat", "a");// Creates a .dat file that we can write our results to
  fprintf(output, "x_extremum: %e , f_extremum: %e , curvature: %e\n", x_extremum, test_func_extreme, curvature); // Writes our values of x_extremum, f(x_extremum), and the curvature into the .dat file
  fclose(output); // Closes the .dat file
  return 0;
}


double test_func(double x)
{
  double f;
// These are the different functions we will use for f(x)
  // Uncomment for Test 1
  f = x*x - 2.0*x + 1;

  // Uncomment for Test 2
  //f = 1.0/x/x - 2.0/x;

  // Uncomment for Test 3
  //f = 1.0/x/x - 1.0/(1.0 + exp(x - 5.0));

  return f;
}
