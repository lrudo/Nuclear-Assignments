#ifndef NUMEROV_H
#define NUMEROV_H
#include "numerov_params.h"

void Numerov_Advance(double *y, NumerovParams *N_Params, DynamicParams *D_Params);

#endif
