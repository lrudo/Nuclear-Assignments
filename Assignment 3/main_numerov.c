#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "numerov.h"
#include "numerov_params.h"
#include "params.h"

double TestF(double x, DynamicParams *D_Params); // Test function

void ReadInN_Params(char *input_file_name, NumerovParams *N_Params);
void PrintParams(NumerovParams N_Params);
void PrintY(double *y, NumerovParams N_Params);


int main(int argc, char **argv)
// Main file where input_data.txt is read in, the N_Params are filled, and the values of the params are recorded in the params.dat file. An array is then allocated via the vector_malloc function, NumerovFunc_F is then assigned the test function - thereby creating y" = Fy. The Numerov_Advance function then solves y" = Fy and then calculates the value of xn via the equatiopn xn = x_i + n*h, where n is an integer that ranges from 0 to nmax, and writes the values of xn and y[n] for each value of n into the output file. Lastly we free the allocated memory after use.
{
  double *y; // 1D array of doubles when a memory space is allocated
  char *input; // 1D array of characters when a word is assigned to it
  NumerovParams N_Params; //To hold static data needed for Numerov method
  DynamicParams D_Params; // To hold data that may change during the calculations
                         // Not used for now

  input = argv[1]; // This is the data from the input_data file

  ReadInN_Params(input, &N_Params); // Fill N_Params
  PrintParams(N_Params); // Check if everything is read-in correctly
                    // Record the read-in data in an output file
  y = vector_malloc(N_Params.nmax+1); // Allocates an array

  N_Params.NumerovFunc_F = TestF; // Assign the F function in y" = Fy
  // to be used in the calculation
  // The name of a function (in this case TestF) is the pointer to the function

  Numerov_Advance(y, &N_Params, &D_Params); // Solve y" = Fy
  PrintY(y, N_Params); // Print y to an output file
  free(y); // Frees allocated memory after use
  return 0;
}// main



double TestF(double x, DynamicParams *D_Params)
// Test functions: F(x) = -1 and F(x) = -x
{
  return -1.0;
  //return -x;
}// TestF



void ReadInN_Params(char *input_file_name, NumerovParams *N_Params)
// Reads in the input file input_data.txt, and assigns the values in that file to x_i, x_f, y_0, y_1, and nmax. The value of h is then calculated via h = (x_f - x_i)/nmax, and then this value is then assigned to the h parameter and the input_data.txt file is finally closed.
{
  FILE *input_file;
  // States variable type
  double x;
  double x_f;
  double y_0;
  double y_1;
  double h;
  int ix;

  input_file = fopen(input_file_name, "r"); // Opens the input file using "r"ead in order to read in the variables

  fscanf(input_file, "%le", &x); // Reads in the first line and put its value in x
  N_Params->x_i = x;
  fscanf(input_file, "%le", &x_f); // Reads in the second line and put its value in x_f
  N_Params->x_f = x_f;
  fscanf(input_file, "%le", &y_0); // Reads in the third line and put its value in y_0
  N_Params->y_0 = y_0;
  fscanf(input_file, "%le", &y_1); // Reads in the fourth line and put its value in y_1
  N_Params->y_1 = y_1;
  fscanf(input_file, "%d", &ix); // Reads in the fifth line, which is an integer, and put its value in ix
  N_Params->nmax = ix;

  h = (x_f - x); // Calculates the value of h = (x_f - x_i)/nmax where x is x_i and ix is nmax
  h /= ix;
  N_Params->h = h; // Puts its value in h
  fclose(input_file); // Closes file
  return;
}// ReadInN_Params


void PrintParams(NumerovParams N_Params)
// Creates a DAT file, params.dat, that records the values of the  x_i, x_f, y_0, y_1, nmax, and h parameters.
{
  FILE *output;
  output = fopen("params.dat", "w"); // Creates DAT file for witing param values to

  // Prints the values of x_i, x_f, y_0, y_1, nmax, and h to the output file
  fprintf(output, "x_i = %e\n", N_Params.x_i);
  fprintf(output, "x_f = %e\n", N_Params.x_f);
  fprintf(output, "y_0 = %e\n", N_Params.y_0);
  fprintf(output, "y_1 = %e\n", N_Params.y_1);
  fprintf(output, "nmax = %d\n", N_Params.nmax);
  fprintf(output, "h = %e\n", N_Params.h);

  fclose(output); // Closes the output file
  return;
}// PrintParams



void PrintY(double *y, NumerovParams N_Params)
// Accepts the solution to y" = Fy and N_Params. The file 261023938_CA_3_Results.dat is created that the output data will be written to. Then by using a 'for' loop, the value of xn is calculated, and the function y is evaluated at n, for each integer value of n which ranges from 0 to nmax.
{
  FILE *output;

  int n; // Declares variable types
  double xn;
  output = fopen("261023938_CA_3_Results.dat", "w"); // The output file that the data will be written to

  for(n=0; n<=N_Params.nmax; n++){
    // A 'for' loop that calculates the value of xn via the equatiopn xn = x_i + n*h and writes the values of xn and y[n] for each value of n into the output file
    xn = N_Params.x_i + n*N_Params.h;
    fprintf(output, "%e %e\n", xn, y[n]);
  }
  fclose(output); // Closes the output file
  return;
}// PrintY
