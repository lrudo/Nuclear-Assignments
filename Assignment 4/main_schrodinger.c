#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "params.h"
#include "numerov_params.h"
#include "init.h"
#include "schrodinger.h"
#include "vector_mtx.h"


// Functions needed only in this file
// Read in Params parameters
void ReadInParams(char *input_file);
// Read in NumerovParams parameters
void ReadIn_N_Params
(char *input_file_name, NumerovParams *N_Params_f, NumerovParams *N_Params_b);
// Record parameters
void RecordParams(NumerovParams N_Params_f, NumerovParams N_Params_b);
// Record results
void RecordResults(DynamicParams D_Params,
NumerovParams N_Params_f, NumerovParams N_Params_b,
double *yf, double *yb);
// This is declared as an extern in params.h
// As such, it needs to be declared outside params.h, but only once.
Params PARAM_DATA;
// This program is to be invoked as
// executable input_file1 input_file2
// the word "input_file1" and "input_file2" are then put into "argv" below
// argv[0] is the name of the executable (e.g. schrodinger)
// argv[1] is the name of the first input file (e.g. input_coulomb)
// argv[2] is the name of the second input file (e.g. input_n_params)
int main(int argc, char **argv)
{
  DynamicParams D_Params; // These parameters are calculated
  NumerovParams N_Params_f; // For the forward evolution of u_I
  NumerovParams N_Params_b; // For the backward evolution of u_II
  double *yf, *yb; // yf contains u_I, yb contains u_II
  ReadInParams(argv[1]); // Reads in the initial data
                        // from the first input file
                        // This is for PARAM_DATA
  ReadIn_N_Params(argv[2], &N_Params_f, &N_Params_b);
                           // Reads in the initial data
                           // from the second input file
                           // This is for N_Params_f and N_Params_b
  Init_CalcStaticScales();
                      // Get the energy and length scales
                      // to prepare for solving the differential eq
 // Record the parameters
  RecordParams(N_Params_f, N_Params_b);
 /* Will be implemented in the next assignment */
 /*
 // Allocate memory for the forward wavefunction yf

 yf = vector_malloc(N_Params_f.nmax+1);
 // Allocate memory for the backward wavefunction yb
 yb = vector_malloc(N_Params_b.nmax+1);
 Schrodinger_GetBoundState(&D_Params, &N_Params_f, &N_Params_b, yf, yb);
 RecordResults(D_Params, N_Params_f, N_Params_b, yf, yb);
 */
 /* Next assignment */
  return 0;
}// main



void ReadInParams(char *input_file)
// Reads in the values of the parameters from the input file and ensures that they are in the correct units. If they are not, the program raises an error that states the given unit, declares the accepted units, and then exits. If the appropriate unit is given, then the program procedes and begins to fill the variables from PARAM_DATA with their corresponding values from the input file. The mass value is converted to units of 1/length unit.
{
  FILE *input; // Sets the input file
  // Declares variables
  double x;
  double mass;
  int ix;
  char *mass_unit;
  int ell;
  double A;
  double Z;

  input = fopen(input_file, "r"); // Opens the input file to "r"ead
  fscanf(input, "%le", &mass); // Reads in the value for mass, and divides it by hbarc in order to have it in units of 1/length unit
  mass /= hbarc;
  PARAM_DATA.mass = mass; // Puts the mass in PARAM_DATA.mass.

  // Read in the mass unit
  mass_unit = (char *) malloc(sizeof(char)*10);
             // First allocate enough memory to hold it.
             // 10 should be enough for any mass units
  // From the second line, read in a line and put it in PARAM_DATA.mass_unit
  fscanf(input, "%s", mass_unit);
  PARAM_DATA.mass_unit = mass_unit;

  // According to the mass unit, determine the length unit
  // strcmp is defined in string.h. It means "string compare".
  // If the two strings are the same, then it returns 0.
  // If the two strings are not the same, it returns non-zero.
  if(strcmp(mass_unit, "eV")==0) {PARAM_DATA.length_unit = "nm";}
  else if(strcmp(mass_unit, "MeV")==0) {PARAM_DATA.length_unit = "fm";}
  // Sets the length scale depending on whether the input was eV or MeV
  else
  // If the input length scale is nether eV or MeV then an error is produced that states that the input unit is unknown, states the units that the program will accept, and then the program exits.
  {
    fprintf(stderr, "ReadInParams: %s is an unknown unit.\n", mass_unit);
    fprintf(stderr, "Known units are eV and MeV.\n");
    fprintf(stderr, "Exiting.\n");
    exit(0);
  }

  fscanf(input, "%d", &ell); // Reads the orbital angular momentum ell and puts its value in PARAM_DATA.ell
  PARAM_DATA.ell = ell;
  fscanf(input, "%le", &A); // Reads in the atomic mass A as a double and puts its value in PARAM_DATA.nucA
  PARAM_DATA.nucA = A;
  fscanf(input, "%le", &Z); // Reads in the atomic number Z as a double and puts its value in PARAM_DATA.Z
  PARAM_DATA.nucZ = Z;

  fclose(input); // Closes the file
  return;
}// ReadInParams


void RecordParams(NumerovParams N_Params_f, NumerovParams N_Params_b)
// Creates a '.dat' file for recording parameter values. Reads in the parameter values from PARAM_DATA, and converts the mass, energy, and momentum back into the eV unit. The values of all of the parameters, and their units, are then written to the '.dat' file.
{
  double x; // Declares variables
  int i;
  double mass;
  double Ea;
  double ka;
  FILE *output; // Declares the output file

  output = fopen("261023938_CA_4_Results.dat", "w"); // Creates DAT file for witing param values to

  // Converts the mass, energy, and momentum back to the eV unit by multiplying their values by hbarc.
  mass = PARAM_DATA.mass * hbarc;
  Ea = PARAM_DATA.Ea * hbarc;
  ka = PARAM_DATA.ka * hbarc;

  // Writes the values of the mass, r0, Ea, ka, ell, x0, nucA, nucZ, nmax forward, and nmax backward to the output file. Mass, r0, Ea, and ka also include their units.
  fprintf(output, "mass = %e %s\n", mass, PARAM_DATA.mass_unit);
  fprintf(output, "r0 = %e %s\n", PARAM_DATA.r0, PARAM_DATA.length_unit);
  fprintf(output, "Ea = %e %s\n", Ea, PARAM_DATA.mass_unit);
  fprintf(output, "ka = %e %s\n", ka, PARAM_DATA.mass_unit);
  fprintf(output, "ell = %d\n", PARAM_DATA.ell);
  fprintf(output, "x0 = %e\n", PARAM_DATA.x0);
  fprintf(output, "nucA = %e\n", PARAM_DATA.nucA);
  fprintf(output, "nucZ = %e\n", PARAM_DATA.nucZ);
  fprintf(output, "nmax_forward = %d\n", N_Params_f.nmax);
  fprintf(output, "nmax_backward = %d\n", N_Params_b.nmax);

  fclose(output); // Closes the output file

  return;
}// RecordParams



void ReadIn_N_Params
(char *input_file_name, NumerovParams *N_Params_f, NumerovParams *N_Params_b)
// Reads in NumerovParams data and sets the value for nmax forward and nmax backward
{
  FILE *input_file; // Declares the input file
  double x; // Declares variables
  int ix;
  int nmax_f;
  int nmax_b;

  input_file = fopen(input_file_name, "r"); // Opens the input file using "r"ead in order to read in the variables

  fscanf(input_file, "%d", &nmax_f); // Reads in nmax for the forward evolution and puts it in N_Params_f->nmax
  N_Params_f->nmax = nmax_f;
  fscanf(input_file, "%d", &nmax_b); // Reads in nmax for the backward evolution and puts it in N_Params_b->nmax
  N_Params_b->nmax = nmax_b;

  fclose(input_file); // Closes the file
  return;
}// ReadIn_N_Params

void RecordResults(DynamicParams D_Params,
NumerovParams N_Params_f, NumerovParams N_Params_b,
double *yf, double *yb)
{
  // Next assignment
  return;
}// RecordResults
