#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"

double test_func(double x);

int main(void){

  // This is the main function where we state our variable types, set our minimum and maximum values of x, and state the number of points we want to calcualte between them. We then calculate the values of the function f, the first derivative df, and the second derivative ddf,  for each value of x. A .dat file is then created and the values of x, f(x), f'(x), and f"(x) are then recorded for each value of x.

  int i, imax;
  double x, dx, x_min, x_max, f, df, ddf;
  FILE *output;
  x_min = 0.0; //Sets minimum value of x
  x_max = 15.0; // Sets maximum value of x
  imax = 1000; // Sets the number of increments we want on our range
  dx = (x_max - x_min) / ((double) imax); // Calculates how much we should increase our x value by each time it is called.
  output = fopen("261023938_CA_2_Deriv_Test.dat", "w"); // Creates a .dat file that we can write to

  for(i=0; i<=imax; i++)
  {// A loop that ranges from 0 to imax for the variable i
    x = x_min + dx*i; // Calculates our new value of x based on x_min, dx, and the increment number i
    f = test_func(x); // Calls the test function
    df = Derivative_FirstD(x, test_func); // Calculates the first derivative of the test function for this particular value of x
    ddf = Derivative_SecondD(x, test_func); // Calculates the second derivative of the test function for this particular value of x
    fprintf(output, "%e %e %e %e\n", x, f, df, ddf); // Writes the values of x, f, df, and ddf to the .dat file
  }// This loop is repeated until i reaches the value of imax
  fclose(output); // Closes the .dat file
  return 0;

}

double test_func(double x){
  return sin(x); // Sets the test function as sin(x)
}
