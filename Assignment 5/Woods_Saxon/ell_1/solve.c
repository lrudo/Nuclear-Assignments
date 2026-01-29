#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"

double Solve_Get_Df(double (*func)(double), double x);

double Solve_Bisect
(double nu, double (*func)(double), double x_min, double x_max, double tol, int *count)
//This function solves f(x) = nu using the bisect method from the range x_min to x_max, count refers to the number of times this function has been called, and tol a small number. This function keeps calcultaing new values for x_min and x_max, based on the value for x_mid, in order to find a solution so that |f_mid/nu| < tol. Once this is achieved, the value for x_mid at that step is returned as the solution.
 {
  double x_mid, f_max, f_min, f_mid, err; // Stating variable types
  int count_max;
  count_max = 1000; // Setting the maximum number of times this function can be run
  *count += 1;// Each time this function is called the value for the count variable increases as well
  x_mid = (x_min + x_max)/2.0; // Calculated the value of x_mid by taking the average between x_min and x_max
  if(*count > count_max)
  {
    // If the value for the count variable surpasses the maximum number of times this function can be called, then the program flags this issue, informs the user the number of iterations performed without convergence, and then exits the program.
    fprintf(stderr, "Solve_Bisect: Done %d iterations without convergence.\n", count_max);
    fprintf(stderr, "Exiting.\n");
    exit(0);
  }
  // f_max and f_min are caluclated via the formula f(x) - nu, where f_max is a function of x_max and f_min is a function of x_min
  f_max = (*func)(x_max) - nu;
  f_min = (*func)(x_min) - nu;
  if(f_max*f_min > 0.0)
  {
    // If the product of f_max and f_min is greater than 0, that implies that a solution may not exist within the given range. This statement flags this issue and informs the user before exiting the program.
    fprintf(stderr, "Cannot find solution within the range.\n");
    fprintf(stderr, "Exiting.\n");
    exit(0);
  }

  f_mid = (*func)(x_mid) - nu; // Calculates f_mid as a function of x_mid
  if(nu != 0.0) {err = fabs(f_mid/nu);} // Calculating and setting the value for the error, |f_mid/nu|, if nu = 0.0
  else {err = fabs(f_mid);} // Calculates the error, |f_mid|, if nu is any other value other than 0.0
  if(err < tol) {return x_mid;} // If the error is smaller than tol, which itself is a small number, then the solution to the Bisect method is that value of x_mid, which is the result that this statement returns.
  if(f_max*f_mid < 0.0)// In this statement, if the product of f_max and f_mid is less than 0.0 then the Solve_Bissect function is called again, but this time x_min=x_mid.
  {
    return Solve_Bisect(nu, func, x_mid, x_max, tol, count);
  }
  else if(f_min*f_mid < 0.0)// In this statement, if the product of f_min and f_mid is less than 0.0 then the Solve_Bissect function is called again, but this time x_max=x_mid.
  {
    return Solve_Bisect(nu, func, x_min, x_mid, tol, count);
  }
  else
  {
    // If none of the above statements hold, then another if/else statement follows that specifies what value of x (ie. x_min or x_max) should be returned given the present circumstances.
    if(f_mid == 0.0) {return x_mid;}
    else if(f_max == 0.0) {return x_max;}
    else {return x_min;};
  }
}

double Solve_Get_Df
(double (*func)(double), double x_old)
// This function calculates the derivative for the function f(x) by way of df = [f(x_old + h) - f(x_old - h)]/2h, where h is a very small number
{
  double h, df;
  if(x_old != 0.0) {h = x_old*1.0E-5;} // This states that so long as x_old is not 0.0, then the value of h can be expressed as the product of a very small number and x_old
  else {h = 1.0E-5;} // If x_old = 0.0, then we set h to a value of 1.0E-5
  df = (*func)(x_old+h) - (*func)(x_old - h);
  df /= 2.0*h;// Calculates the value for the derivative df = [f(x_old + h) - f(x_old - h)]/2h
return df;
}

double Solve_Newton
(double nu, double (*func)(double), double x_0, double tol, int *count)
// Solves nu = func(x), knowing that x_(n+1) = x_n + (nu - f(x_n))/f'(x_n), where x_0 is the original value for x, count is the number of times the function is called, and tol is the desired error value to reach.
{
  double x_n, x_new, err, df, h;
  int count_max;
  count_max = 1000; // Maximum number of times this function can be called
  x_n = x_0;// Sets the x_n to be the original value of x
  do {
    // This statement specifies that the below should continuously occur so long as the requirement, that the error is greater than the desired error, has not been fulfilled. However, once this requirement has been met, then this function returns x_new.
    df = Solve_Get_Df(func, x_n); // Calculates the derivative with respect to x_n
    if(fabs(df) < tol)
    {
      // If the |df| < tol, then the derivative has become too small and the user is warned before the program is exited.
      fprintf(stderr, "Solve Newton: Derivative is too small.\n");
      fprintf(stderr, "Exiting.\n");
      exit(0);
    }
    x_new = x_n + ((nu - (*func)(x_n))/df); // Calculated the value of x_new (x_(n+1)) based off of x_n
    err = fabs((x_new - x_n)/x_n);// Calculates the error as |((x_(n+1) - x_n)/ x_n|
    x_n = x_new;// Sets the new value of x_n to the current value of x_(n+1)
    *count += 1;// Each time this function is called the value for the count variable increases as well
    if(*count == count_max)
    {
      // If there have been too many iterations of this function, ie. we have surpassed the max count number, the user is then warned, and the program exited.
      fprintf(stderr, "Too many iterations.\n");
      fprintf(stderr, "Exiting.\n");
      exit(0);
    }
  } while(err > tol);
  return x_new;// Once the error is smaller than the chosen value of tol then the value for x_new will be returned as the solution to Newton's Method.
}
