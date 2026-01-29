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
void ReadInParams(char *input_file, DynamicParams *D_Params);
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
  ReadInParams(argv[1], &D_Params); // Reads in the initial data
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

 //Allocate memory for the forward wavefunction yf
  yf = vector_malloc(N_Params_f.nmax+1);
 // Allocate memory for the backward wavefunction yb
  yb = vector_malloc(N_Params_b.nmax+1);
  Schrodinger_GetBoundState(&D_Params, &N_Params_f, &N_Params_b, yf, yb);
  RecordResults(D_Params, N_Params_f, N_Params_b, yf, yb);

  return 0;
}// main



void ReadInParams(char *input_file, DynamicParams *D_Params)
// Reads in the values of the parameters from the input file and ensures that they are in the correct units. If they are not, the program raises an error that states the given unit, declares the accepted units, and then exits. If the appropriate unit is given, then the program procedes and begins to fill the variables from PARAM_DATA with their corresponding values from the input file. The mass value is converted to units of 1/length unit.
{
  FILE *input; // Sets the input file
  // Declares variables
  double x;
  int ix;
  char *mass_unit;


  input = fopen(input_file, "r"); // Opens the input file to "r"ead
  fscanf(input, "%le", &x); // Reads in the value for mass, and divides it by hbarc in order to have it in units of 1/length unit
  //mass /= hbarc;
  PARAM_DATA.mass = x; // Puts the mass in PARAM_DATA.mass.
  PARAM_DATA.mass /= hbarc;
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


  fscanf(input, "%d", &ix); // Reads the orbital angular momentum ell and puts its value in PARAM_DATA.ell
  PARAM_DATA.ell = ix;
  fscanf(input, "%le", &x); // Reads in the atomic mass A as a double and puts its value in PARAM_DATA.nucA
  PARAM_DATA.nucA = x;
  fscanf(input, "%le", &x); // Reads in the atomic number Z as a double and puts its value in PARAM_DATA.Z
  PARAM_DATA.nucZ = x;

  fscanf(input, "%le", &x);// Reads in the minimum value of Et for the energy eigenvalue search and puts its value in D_Params->Et_min
  D_Params->Et_min = x;

  fscanf(input, "%le", &x);// Reads in the mamimum value of Et for the energy eigenvalue search and puts its value in D_Params->Et_max
  D_Params->Et_max = x;

  fclose(input); // Closes the file
  fprintf(stderr, "Done reading in.\n");
  return;
}// ReadInParams


void RecordParams(NumerovParams N_Params_f, NumerovParams N_Params_b)
// Creates a '.dat' file for recording parameter values. Reads in the parameter values from PARAM_DATA, and converts the mass, energy, and momentum back into the eV unit. The values of all of the parameters, and their units, are then written to the '.dat' file.
{
  double mass;
  double Ea;
  double ka;
  double Eb;
  double kb;
  double et_min;
  double et_max;
  FILE *output; // Declares the output file
  DynamicParams D_Params;
  output = fopen("261023938_CA_5_Coloumb_ell_0_schrodinger_params.dat", "w"); // Creates DAT file for witing param values to

  // Converts the mass, energy, and momentum back to the eV unit by multiplying their values by hbarc.
  mass = PARAM_DATA.mass * hbarc;
  Ea = PARAM_DATA.Ea * hbarc;
  ka = PARAM_DATA.ka * hbarc;
  Eb = D_Params.Eb * hbarc;
  kb = D_Params.kb * hbarc;

  // Writes the values of the mass, r0, Ea, ka, ell, x0, nucA, nucZ, nmax forward, and nmax backward to the output file. Mass, r0, Ea, and ka also include their units.
  fprintf(output, "Parameters: \n");
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

  fprintf(output, "\n");
  fprintf(output, "Dynamic Parameters: \n");

  fprintf(output, "Eb = %e %s\n", Eb, PARAM_DATA.mass_unit);
  fprintf(output, "kb = %e %s\n", kb, PARAM_DATA.mass_unit);
  fprintf(output, "rc = %e %s\n", D_Params.rc, PARAM_DATA.length_unit);
  fprintf(output, "Et = %e\n", D_Params.Et);
  fprintf(output, "xc = %e\n", D_Params.xc);
  fprintf(output, "rf = %e\n", D_Params.rf);
  fprintf(output, "xf = %e\n", D_Params.xf);
  fprintf(output, "Et_min = %e\n", D_Params.Et_min);
  fprintf(output, "Et_max = %e\n", D_Params.Et_max);

  fprintf(output, "\n");
  fprintf(output, "Numerov Parameters (forward): \n");
  fprintf(output, "x_f_f = %e\n", N_Params_f.x_f);
  fprintf(output, "x_i_f = %e\n", N_Params_f.x_i);
  fprintf(output, "y_0_f = %e\n", N_Params_f.y_0);
  fprintf(output, "y_1_f = %e\n", N_Params_f.y_1);
  fprintf(output, "nmax_f = %d\n", N_Params_f.nmax);
  fprintf(output, "h_f = %e\n", N_Params_f.h);

  fprintf(output, "\n");
  fprintf(output, "Numerov Parameters (backward): \n");
  fprintf(output, "x_f_b = %e\n", N_Params_b.x_f);
  fprintf(output, "x_i_b = %e\n", N_Params_b.x_i);
  fprintf(output, "y_0_b = %e\n", N_Params_b.y_0);
  fprintf(output, "y_1_b = %e\n", N_Params_b.y_1);
  fprintf(output, "nmax_b = %d\n", N_Params_b.nmax);
  fprintf(output, "h_b = %e\n", N_Params_b.h);



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

  input_file = fopen(input_file_name, "r"); // Opens the input file using "r"ead in order to read in the variables

  fscanf(input_file, "%d", &ix); // Reads in nmax for the forward evolution and puts it in N_Params_f->nmax
  N_Params_f->nmax = ix;
  fscanf(input_file, "%d", &ix); // Reads in nmax for the backward evolution and puts it in N_Params_b->nmax
  N_Params_b->nmax = ix;

  fclose(input_file); // Closes the file
  return;
}// ReadIn_N_Params

void RecordResults(DynamicParams D_Params,
NumerovParams N_Params_f, NumerovParams N_Params_b,
double *yf, double *yb)
{
  double Et;
  FILE *output;
  int n;
  double x;
  output = fopen("261023938_CA_5_Coulomb_ell_0_schrodinger_data.dat", "w");
  Et = D_Params.Et;
  x = Et * PARAM_DATA.Ea * hbarc;
  fprintf(output, "Et = %e\n", Et);
  fprintf(output, "Eb = %e %s\n", x, PARAM_DATA.mass_unit);
  fclose(output);

  output = fopen("261023938_CA_5_Coulomb_ell_0_yf.dat", "w");
  for(n=0; n<=N_Params_f.nmax; n++)
  {
    x = N_Params_f.x_i + n*N_Params_f.h;// Dimensionless
    x /= PARAM_DATA.ka; // 1/energy
    x *= hbarc;         // length dimension
    fprintf(output, "%e  %e\n", x, yf[n]/yf[N_Params_f.nmax]);
  }
  fclose(output);

  output = fopen("261023938_CA_5_Coulomb_ell_0_yb.dat","w");
  for(n=0; n<=N_Params_b.nmax; n++)
  {
  // 0 < x’ < x_f - x_c
    x = D_Params.xf - (N_Params_b.x_i + n*N_Params_b.h);
    x /= PARAM_DATA.ka;
    x *= hbarc;
  // TD: Implement x = x_f - (x_i + n*h)
  // TD: getting x_i and h from N_Params_b
  // TD: and xf from D_Params.
  // TD: Convert x to the length unit
   fprintf(output, "%e  %e\n", x, yb[n]/yb[N_Params_b.nmax]);
  }
  fclose(output);

}// RecordResults
