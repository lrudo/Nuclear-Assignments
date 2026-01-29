#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "init.h"
#include "radial_eq_functions.h"
#include "solve.h"
#include "extremum.h"
#include "derivatives.h"

double Init_Rmin_Function(double r);
   // The function to minimize to get Ea and ka
   // Equals V(r) + 1/(2 m r^2)

void Init_CalcStaticScales(void)
// Gets the energy and length scales and prepares to solve the differential eq
{
  double r_min, r_init, E_min, Eb, mass, r_c, curvature; // Declares variables
  double R_A;
  double ka;
  double x0;
  FILE *output; // Sets output file
  mass = PARAM_DATA.mass; // Sets mass value
  if(PARAM_DATA.nucA == 0.0){ // Not a nuclear potential
    // An 'IF' statement that states that if there is no atomic mass then the extremum of Init_Rmin_Function should be found using a range starting at r_init and using the curvature value 'curvature'.
    // This value is r_min, and it is saved in PARAM_DATA as r0. It is then used to calculate E_min which is Init_Rmin_Function evaluated at r_min. The absolute value of E_min is then taken and stored in PARAM_DATA as Ea.

      r_init = 0.01; // to start the iteration
      r_min = Extremum_GetExtremum(Init_Rmin_Function, r_init, &curvature);
      // Calculates the minimum radius by evaluating Extremum_GetExtremum on Init_Rmin_Function
      PARAM_DATA.r0 = r_min; // Sets the radius value r0 to r_min
      E_min = Init_Rmin_Function(r_min);
   // Calculate E_min as the value of Init_Rmin_Function evaluated at r_min
      PARAM_DATA.Ea = fabs(E_min); // Calculates the absolute value of E_min and puts that value in Ea in PARAM_DATA
  }
  else // Nuclear potential. We know scales in this case.
  {
      PARAM_DATA.r0 = 1.3*pow(PARAM_DATA.nucA, 1.0/3.0); // Nuclear radius
      PARAM_DATA.Ea = 50.0/hbarc; // about 50 MeV
  }
  //ka = sqrt(2.0*mass*(PARAM_DATA.Ea));
  PARAM_DATA.ka = sqrt(2.0*mass*(PARAM_DATA.Ea)); // Calculates ka = sqrt(2*m*Ea)and puts it in ka in PARAM_DATA
  PARAM_DATA.x0 = (PARAM_DATA.ka)*(PARAM_DATA.r0); // Calculates x0 = ka*r0 and puts it in x0 in PARAM_DATA
  return;
}// Init_CalcStaticScales



double Init_Rmin_Function(double r) // Function that we would like to minimize in order to calculate Ea and ka. It is equal to V(r) + 1/(2mr^2)
  {
    double f, mass; // Declares varialbes

    mass = PARAM_DATA.mass; // Sets mass value

    f = RadialEqFunctions_V(r) + 1/(2*mass*r*r); // Calculates V(r) + 1/(2mr^2) using the RadialEqFunctions_V equation defined in `radial_eq_functions.c`
    return f;
  }// Init_Rmin_function
