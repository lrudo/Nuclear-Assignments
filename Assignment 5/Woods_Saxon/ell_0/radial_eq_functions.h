#ifndef RADIAL_EQ_FUNCTIONS_H
#define RADIAL_EQ_FUNCTIONS_H

#include "params.h" // Because we used DynamicParams below
// Potential energy in r
double RadialEqFunctions_V(double r);
// V_eff = V + ell(ell+1)/(2m r^2)
double RadialEqFunctions_Veff(double r);
// The F function in the RHS of the differential equation y’’ = Fy
double RadialEqFunctions_F_Forward(double x, DynamicParams *D_Params);
double RadialEqFunctions_F_Backward(double x, DynamicParams *D_Params);
#endif
