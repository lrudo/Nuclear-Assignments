#ifndef PARAMS_H
#define PARAMS_H

#define hbarc (197.3);
// MeV.fm = eV.nm

// This is a collection of parameters that do not change
// during the calculation. This will be set once in the beginning
// of the calculation and be accessed via PARAM_DATA below.

typedef struct params{
  double mass; // Mass of the particle
  double Ea; // Energy scale
  double ka; // Momentum scale
  double r0; // Length scale
  double x0; // x0 = k*r0
  int ell;

  char *mass_unit; // The unit of mass. Either MeV or eV
  char *length_unit; // The unit of length. Either fm (goes with MeV)
                    // or nm (goes with eV)

  double nucA; // Atomic mass. For later.
  double nucZ;// Atomic number. For later.
} Params;


// This is a collection of variables that change during the calculation
// and need to be passed frequently
// Some of these parameters will be used in later assignments

typedef struct dynamic_params{
  double Eb; // Absolute value of the bound energy
  double kb; // sqrt(2*mass*Eb)
  double rc; // The turning point radius
  double Et; // Eb/Ea
  double xc; // ka*rc
  double rf; // The last point
  double xf; // xf = ka*rf
} DynamicParams;

extern Params PARAM_DATA; // Run specific data

// The key word extern here specifies that this variable
// can be accessed by any function as long as params.h is included.
// Any variable declared as an extern in a header file must be declared
// once in a .c file. We’ll do that in the main_numerov.c.

#endif
