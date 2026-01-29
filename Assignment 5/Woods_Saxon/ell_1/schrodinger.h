#ifndef SCHRODINGER_H
#define SCHRODINGER_H

#include "params.h"
#include "numerov_params.h"

void Schrodinger_GetBoundState
(DynamicParams *D_Params, NumerovParams *N_Params_f,
 NumerovParams *N_Params_b, double *yf, double *yb);
 
#endif
