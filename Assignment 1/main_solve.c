#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"


double f_solve(double x);

int main(void) {
  // This file is where we state what our x range is for the Solve Bisect Method as well as what our initial value for x_n is for Newton's Method. We are trying to solve for sin(x) = 0, and to do so we first call Solve_Bisect where we specify the original count number, the desired error value, as well as the x range. The outputs from our program will be presented in the terminal once our program is compiled and then run.

  // We then call Solve_Newton where we specify the value of nu, the desired error value, the initial value for x_n, as well as re-set the value of count to 0. As in the case for the Bisect Method, we specify that the number of counts that it takes for our program to converge, and the value that it converges to, will be displayed in the terminal.
  double x_max, x_min, x, tol;
  int count;
  fprintf(stdout, "Solve_Bisect for sin(x)\n");
  count = 0; // The original value for the variable count
  tol = 1.0E-10; // The value that we want our error value to be smaller than
  x = Solve_Bisect(0.0, f_solve, 0.1, 4.0, tol, &count); // Calls the Solve Bisect function to solve f(x) = 0 between the range 0.1 < x < 4.0
  fprintf(stdout, "count = %d\n", count);
  fprintf(stdout, "x = %e\n", x); // Prints out the number of iterations that were required in order to solve f(x) = 0 as well as the value of x
  fprintf(stdout, "Solve_Newton for sin(x)\n");
  count = 0;// Sets the value for the count variable back to 0
  tol = 1.0E-10;// The value that we want our error value to be smaller than
  x = Solve_Newton(0.0, f_solve, 4.0, tol, &count);// Calls the Solve Newton function to solve f(x) = 0, where the original value of x is 4.0
  fprintf(stdout, "count = %d\n", count);
  fprintf(stdout, "x = %e\n", x);// Prints out the number of iterations that were required in order to solve f(x) = 0 as well as the value of x
  return 1;
}

double f_solve(double x) {
  return sin(x); // the function, f(x), that we are trying to solve f(x)=nu for
  //return x*exp(x) - 3.0;
}
