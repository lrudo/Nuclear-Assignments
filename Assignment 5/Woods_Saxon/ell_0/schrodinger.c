#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "numerov.h"
#include "numerov_params.h"
#include "radial_eq_functions.h"
#include "params.h"
#include "schrodinger.h"
#include "solve.h"
#include "init.h"

// Common variables to be used only within this file
// These variables are needed because our equation solvers
// Solve_Bisect and Solve_Newton needs a function that is
// a function only of a single double argument.

NumerovParams *COM_N_PARAMS_F;
NumerovParams *COM_N_PARAMS_B;
DynamicParams *COM_D_PARAMS;
double *COM_Y_F; // Forward wavefunction
double *COM_Y_B; // Backward wavefunction

// These functions are needed only within this file
double Schrodinger_GetDf_nmax(double *y, NumerovParams *N_Params);
void Schrodinger_InitializeCommonVar(void);

double Schrodinger_GetError(void);
void Schrodinger_EvolveForward(void);
void Schrodinger_EvolveBackward(void);
void Schrodinger_CalcRunScales(double Et);
double Schrodinger_CalcRc(double Eb, double r_init);
double Schrodinger_GetBoundStateError(double Et);
void Schrodinger_PlotData(double Et_min, double Et_max);


void Schrodinger_GetBoundState(DynamicParams *D_Params, NumerovParams *N_Params_f, NumerovParams *N_Params_b, double *yf, double *yb)
{// Calculates the bound state error as well the value of Et when the error is 0 using the Solve_Bisect function. Also creates a file that saves the error value and the corresponding of Et to a .DAT file.


  double Et_min, Et_max, tol, err;// Declares variables
  int count;
  double x, y;

  COM_N_PARAMS_F = N_Params_f;
  COM_N_PARAMS_B = N_Params_b;
  COM_D_PARAMS = D_Params;
  COM_Y_F = yf;
  COM_Y_B = yb;

  Et_min = D_Params->Et_min;// Sets the values of Et_min and Et_max
  Et_max = D_Params->Et_max;

  // To plot the error err = u’_I/u_I - u’_II/u_II at x = xc
  Schrodinger_PlotData(Et_min, Et_max);
  // Schrodinger_GetBoundStateError returns
  // err = u’_I/u_I - u’_II/u_II at x = xc
  count = 0;// The original value for the variable count
  tol = 1.0e-6; // The value that we want our error value to be smaller than
  Solve_Bisect(0.0, Schrodinger_GetBoundStateError, Et_min, Et_max, tol, &count);
  //This function solves Schrodinger_GetBoundStateError = 0 using the bisect method from the range Et_min to Et_max, count refers to the number of times this function has been called, and tol a small number. This function keeps calcultaing new values for Et_min and Et_max, based on the value for Et_mid, in order to find a solution so that |f_mid| < tol. Once this is achieved, the value for Et_mid at that step is returned as the solution.
  fprintf(stderr, "count= %d\n", count);// Prints how many counts it took to find a solution using Solve_Bisect

  return;
}// Schrodinger_GetBoundState



void Schrodinger_PlotData(double Et_min, double Et_max)
// To plot
// err = u’_I/u_I - u’_II/u_II at x = xc
// between Et_min and Et_max
// Calculates the bound state error between Et_min and Et_max
{
  FILE *output;
  int n, nmax;
  double dEt, Et, err;// Declares variables

  output = fopen("261023938_CA_5_Woods_ell_0_bound_state_err.dat", "w");// Sets the output file to write

  nmax = 1000;// Number of increments
  dEt = (Et_max - Et_min) / (nmax);// Calculates the increment that we want to change out value of Et by

  for(n=0; n<=nmax; n++)
  // A FOR loop that calculates the bound state error for each new value of Et, which is calculated by adding n*dEt, which is the increment amount multiplied by the increment number, to the Et_min value.
  {
    Et = Et_min + n*dEt;// Calculates the new value of Et
    err = Schrodinger_GetBoundStateError(Et);// Calculates the new bound state error for each new value of Et
    fprintf(output, "%e %e\n", Et, err);// Prints the value of Et and the subsequent error value to the output file
  }
  fclose(output);// Closes the output file
  return;
}// Schrodinger_Plot_Data


double Schrodinger_GetBoundStateError(double Et)
// This function returns
// err = u’_I/u_I - u’_II/u_II at x = xc
{
  double err;
  Schrodinger_CalcRunScales(Et);
  Schrodinger_InitializeCommonVar();
  Schrodinger_EvolveForward();
  Schrodinger_EvolveBackward();

  err = Schrodinger_GetError();// Calculates the bound state erro

  return err;
}// Schrodinger_GetBoundStateError


void Schrodinger_CalcRunScales(double Et)
{
  double r_init, r_min, r_c, Ea, Eb;// Declares variables

  Ea = PARAM_DATA.Ea; // Energy scale
  Eb = Et*Ea;         // Energy corresponding to Et

  COM_D_PARAMS->kb = sqrt(2.0*Eb*PARAM_DATA.mass);
 // getting mass from PARAM_DATA
  COM_D_PARAMS->Et = Et;
  COM_D_PARAMS->Eb = Eb;
  r_min = PARAM_DATA.r0;
  r_init = 1.1*r_min;// Calculates r_init

  // This calculates the classical turning point
  // by solving -Eb = V(r) + ell(ell+1)/(2 mass r^2)
  r_c = Schrodinger_CalcRc(Eb, r_init);
  COM_D_PARAMS->rc = r_c;
  COM_D_PARAMS->xc = r_c*PARAM_DATA.ka;

  // The wavefunction behaves like exp(-(kb/ka)*x)
  // where kb = sqrt(2*mass*Eb)
  // We take x_f = 20*(ka/kb)

  COM_D_PARAMS->xf = 20*(PARAM_DATA.ka/COM_D_PARAMS->kb);
  COM_D_PARAMS->rf = (COM_D_PARAMS->xf/PARAM_DATA.ka);

  return;
}// Schrodinger_CalcRunScales



double Schrodinger_CalcRc(double Eb, double r_init)
// Solves -Eb = Veff(r), where Veff(r) =  V(r) + ell(ell+1)/(2mu r^2), using Solve_Newton. It does so by knowing that r_(n+1) = r_n + (-Eb - Veff(r_n))/Veff'(r_n), where r_init is the original value for r, count is the number of times the function is called, and tol is the desired error value to reach.
// Returns the turning point value, rc, that is larger than Rmin.
{
  double f, E_min, r_c, tol;// Declares the variables
  int count;

  tol = 1.0e-8;// Desired error value to reach
  count = 0;// The original value for the variable count
  r_c = Solve_Newton(-1*Eb, RadialEqFunctions_Veff, r_init, tol, &count);
  // Solves -Eb = RadialEqFunctions_Veff, knowing that r_(n+1) = r_n + (-Eb - RadialEqFunctions_Veff(r_n))/RadialEqFunctions_Veff'(r_n), where r_init is the original value for r, count is the number of times the function is called, and tol is the desired error value to reach.

  return r_c;
}// Schrodinger_CalcRc


void Schrodinger_InitializeCommonVar(void)
// Initialize all other necessary variables
{
  double kb, rf, h;// Declares the variables

  // For the forward evolution, x_i = 0 and x_f = xc
  // y_0 = y[0] = 0 and y_1 = y[1] can be any small number
  // We set it to 0.1

  COM_N_PARAMS_F->x_i = 0.0;
  COM_N_PARAMS_F->x_f = COM_D_PARAMS->xc;
  COM_N_PARAMS_F->y_0 = 0.0;
  COM_N_PARAMS_F->y_1 = 0.1;
  COM_N_PARAMS_F->h = (COM_N_PARAMS_F->x_f - COM_N_PARAMS_F->x_i)/(COM_N_PARAMS_F->nmax);
  // h = (x_f - x_i)/nmax

  // Backward evolution params
  // The wavefunction behaves like exp(-(kb/ka)*x)
  // where kb = sqrt(2*mass*Eb)
  // We take x_f = 20*(ka/kb)
  // so that y[0] = exp(-20) = 2E-9
  // and y[1] = exp(-(kb/ka)*(x_f-h))
  // y_0 = y[0] should be a small number and
  // y_1 = y[1] should be a small number > y[0]
  // The x range is xc < x < xf
  // or 0 < x’ < xf-xc

  COM_N_PARAMS_B->x_i = 0.0;
  COM_N_PARAMS_B->x_f = COM_D_PARAMS->xf - COM_D_PARAMS->xc;
  COM_N_PARAMS_B->h = (COM_N_PARAMS_B->x_f - COM_N_PARAMS_B->x_i)/(COM_N_PARAMS_B->nmax);
  // h = (x_f - x_i)/nmax
  kb = COM_D_PARAMS->kb;
  rf = COM_D_PARAMS->rf;
  h  = COM_N_PARAMS_B->h;
  COM_N_PARAMS_B->y_0 = exp(-1*kb*rf);
  COM_N_PARAMS_B->y_1 = exp(-1*kb*(rf-h));
 return;
}// Schrodinger_Initialize



void Schrodinger_EvolveForward(void)
{
  double f, df;// Declares the variables
  int nmax;
  double *yf;
  NumerovParams *N_Params_f;
  DynamicParams *D_Params_f;

  yf = COM_Y_F;
  N_Params_f = COM_N_PARAMS_F;
  D_Params_f = COM_D_PARAMS;

  nmax = N_Params_f->nmax;
  N_Params_f->NumerovFunc_F = RadialEqFunctions_F_Forward;

  Numerov_Advance(yf, N_Params_f, D_Params_f);
  return;
}// Schrodinger_EvolveForward

void Schrodinger_EvolveBackward(void)
{
  double f, df;// Declares the variables
  int nmax;
  double *yb;
  NumerovParams *N_Params_b;
  DynamicParams *D_Params_b;
  yb = COM_Y_B;
  N_Params_b = COM_N_PARAMS_B;
  D_Params_b = COM_D_PARAMS;
  nmax = N_Params_b->nmax;
  N_Params_b->NumerovFunc_F = RadialEqFunctions_F_Backward;

  Numerov_Advance(yb, N_Params_b, D_Params_b);

  return;
}// Schrodinger_EvolveBackward

// This implements the numerical derivative at the end of the list.
// That is, given y[n-2], y[n-1], y[n], get the slope at y[n].
// Given these 3 points, the slope at x_n is given by
// y’[n] = (3y[n] - 4y[n-1] + y[n-2])/(2h)
//

double Schrodinger_GetDf_nmax(double *y, NumerovParams *N_Params)
{
  double df, h;// Declares the variables
  int nmax;

  nmax = N_Params->nmax;
  h = N_Params->h;

  df = (3*y[nmax] - 4*y[nmax-1] + y[nmax-2]) / (2*h);

  return df;
}// Schrodinger_GetDf_nmax

double Schrodinger_GetError(void)
{
  double *yf, *yb;// Declares the variables
  NumerovParams *N_Params_f, *N_Params_b;
  double df, df_f, df_b;
  int nmax;

  N_Params_f = COM_N_PARAMS_F;
  N_Params_b = COM_N_PARAMS_B;
  yf = COM_Y_F;
  yb = COM_Y_B;

  //nmax = N_Params_f->nmax;
  df_f = Schrodinger_GetDf_nmax(yf, N_Params_f);// calculates the forward derivative
  df_f /= yf[N_Params_f->nmax];

  df_b = -1*Schrodinger_GetDf_nmax(yb, N_Params_b);
  df_b /= yb[N_Params_b->nmax];

  df = df_f - df_b;
  return df;
}// Schrodinger_GetError
