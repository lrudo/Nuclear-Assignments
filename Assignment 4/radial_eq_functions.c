#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "radial_eq_functions.h"
#include "numerov_params.h"
#include "params.h"

#define alpha_EM (1.0/137.0)

// RadialEqFunctions_V(double r) is the only function one should change.
// This is in the unit of 1/fm or 1/nm
double RadialEqFunctions_V(double r)
{
  double f;
  double A, R_A, a, R0, V0; // Defines variables

  f = -1*alpha_EM/r;  // The Coulomb potential for the hydrogen atom

  // Nuclear Woods-Saxon potential
  // Next assignment
  /*
  V0 = 50.0/hbarc; // MeV to 1/fm
  a = 0.7;
  R_A = PARAM_DATA.r0;
  f = -V0/(1.0 + exp((r-R_A)/a));
  */
  return f;
}// RadialEqFunctions_V


// Veff(r) = V(r) + ell(ell+1)/(2 m r^2)
double RadialEqFunctions_Veff(double r)
{
  double f, ell, mass;// Defines variables
  ell = (double) PARAM_DATA.ell; // PARAM_DATA.ell is an integer
                                // ell here is a double.
  mass = PARAM_DATA.mass; // Sets the mass value from PARAM_DATA
  f = RadialEqFunctions_V(r) + ell*(ell+1)/(2*mass*r*r); // Calculates Veff(r) = V(r) + l(l+1)/(2 *mu* r^2)

  return f;
}// RadialEqFunctions_Veff


// F in y’’ = Fy for u_I
// This is in x = ka*r
double RadialEqFunctions_F_Forward(double x, DynamicParams *D_Params)
{
  double x0, ka, r, f, g, Ea, Et, ell, eps; // Defines variables
  ell = (double) PARAM_DATA.ell; // Converts PARAM_DATA.ell into a double
  x0 = PARAM_DATA.x0; // Defines variables according to PARAM_DATA
  ka = PARAM_DATA.ka;
  Ea = PARAM_DATA.Ea;
  Et = D_Params->Et;

  eps = 1.0e-15; // Small number to prevent x = 0
  x += eps; // Ensures that x != 0
  r = x/ka; // re-writes x = k_a * r

  f = RadialEqFunctions_V(r)/Ea + ell*(ell+1)/(x*x) + Et;
  // V(r)/Ea + l(l+1)/x^2 + Et, where V(r)/Ea is V_tilda(x) and Et is equivalent to -E_tilda_nl

  return f;
}// RadialEqFunctions_F_Forward


// F in Y’’ = FY Backward evolution
// Here we use y = x_f - x
double RadialEqFunctions_F_Backward(double y, DynamicParams *D_Params)
{
  double ka, r, f, g, ell, Ea, Et, x, x0; // Declaring variables
  ell = (double) PARAM_DATA.ell; // Converts PARAM_DATA.ell into a double
  x0 = PARAM_DATA.x0; // Defines variables according to PARAM_DATA
  ka = PARAM_DATA.ka;
  Ea = PARAM_DATA.Ea;
  Et = D_Params->Et;

  x = D_Params->xf - y; // Defines x  as x = x_f - y, where x_f = k_a * r_f with r_f being the last point

  r = x/ka; // re-writes x = k_a * r

  f = RadialEqFunctions_V(r)/Ea + ell*(ell+1)/(x*x) + Et;
  // V(r)/Ea + l(l+1)/x^2 + Et, where V(r)/Ea is V_tilda(x) and Et is equivalent to -E_tilda_nl

  return f;

}// RadialEqFunctions_F_Backward
