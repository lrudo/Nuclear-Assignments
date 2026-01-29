# ReadMe for schrodinger

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca

## Project Overview

This projects lays the groundwork for solving the Schrodinger equation via the Shooting method, which will be implemented in the next assignment.

Once compiled, and the `./schrodinger input_coulomb.txt input_n_params.txt` executable run from the terminal, the resulting parameter values for mass, r0 (radius), Ea (energy), ka (momentum), ell (angular momentum l), x0 (initial value of x), nucA (atomic mass), nucZ (atomic number), nmax forward, and nmax backward (maximum number of integer steps to be taken) are saved to 261023938_CA_4_Results.dat.

Compiler: gcc 11.2.0

## Physics Background

This project was created in order to numerically the Schrodinger equation:

(-d^2/dx^2 + l(l+1)/x^2 + V_tilda(x) + E_tilda_nl)u_tilda_nl(x) = 0

where mu is the effective mass, the momentum ka = sqrt(s*mu*Ea), and x = ka*r. V_tilda(x) and E_tilda_nl can be written in terms of:
  V_tilda(x) = V(x/ka)/Ea  and  
  E_tilda_nl = -|E_nl|/Ea

We can define the energy scale Ea as the minimum value of the potential V_eff = 1/(2*mu*r^2) + V(r). Here we let l(l+1)->1 and assume that V(r) is no more singular than 1/r as r->0. In order to obtain the minimum point we need to solve the equation

V'_eff(r) = -1/(mu*r^3) + V'(r) = 0

This can be done by using the first derivative of the function fo calculate the extremum.

Following this, the goal is to numerically solve the Schrodinger equation with the following boundary conditions:

    lim x->0 u_tilda_nl(x) = 0
    lim x ->oo u_tilda_nl(x) = 0

The process for solving the differential equation can be broken into two parts were the equation is solved for two different conditions, and then they are matched at x_c:

1.) 0 < x <= x_c : u_tilda_1(x)
2.) x_c <= x < x_f : u_tilda_11(x) with x_f >> 1

The boundary condition at x = 0 is u_tilda_1(0) = 0.

We can then implement the Shooting method, which begins with choosing a value for E_tilda_nl, calculates u_tilda_1(x) and u_tilda_11(x), and then adjusts the value for E_tilda_nl until u_tilda_1'(x)/u_tilda_1(x) and u_tilda_11'(x)/u_tilda_11(x) match at x_c.

In order to calculate x_c we can use the classical turning point which is defined as the point where
  l(l+1) + x_c^2 * (V_tilda(x_c) + E_tilda_nl) = 0

This equation can be solved via Newton's Method, described below.

This project sets up the preparation for the Shooting method, which will be implemented in the next assignment.


# First and Second Derivative

Using the Taylor expansion on the function f(x), we obtain the expression:

f(x+h) = f(x) + hf'(x) + h^2/2 f"(x) + h^3/6 f"'(x) + O(h^4)

From here we can obtain an expression for f'(x):

f'(x) = [f(x+h) - f(x-h)]/2h + O(h^2)

And using that expression as well as the one for f(x+h), we can obtain an expression for f"(x):

f"(x) = [f(x+h) + f(x-h) - 2f(x)]/(h^2) + O(h^3).

In calculus the limit as h->0 would be taken, however we set h to a small value: h = x*1E-5, for all x, so long as x!= 0. The reason h = x *1E-5 is chosen is that this value is best for achieving double precision in our results.



# Newton's Method

In Newton's Method we use the approximate definition of the derivative:

f'(x_n) = [f(x_(n+1)) - f(x_n)] / (x_(n+1) - x_n),

rearrange it, and let f(x_(n+1)) = nu, in order to achieve the expression:

x_(n+1) = x_n + (nu - f(x_n))/ f'(x_n).

Unlike the Bisect Search Method that was used in the previous computing assignment, we do not specify a range, instead we specify a starting point value for x, x_0.


## Description of Files

- `main_schrodinger.c`: This is the main executable that reads in the input files, performs the desired calculations, and records the results in the 261023938_CA_4_Results.dat file.
- `schrodinger.h`: This is the header file for `main_schrodinger.c`.

- `init.c`: This ensures that the input variables are in the correct units and solves for the extremum of the function f(x) that we would like to solve. The extremum is then evaluated at this point, and the result has the absolute value taken of it and the resulting value is E_min.
- `init.h`: This is the header file for `init.c`.

- `radial_eq_functions.c`: Defines the radial potential that we will be using, as well as V_eff and the forward and backward evolution that will be used to solve the Schrodinger equation.
- `radial_eq_functions.h`: This is the header file for `radial_eq_functions.c`.

- `extremum.c`: Defines the Extremum_GetExtremum function, which calculates the first derivative of a function, finds the value of the extremum, and calculates the curvature (the second derivative of the function evaluated at the extremum).
- `extremum.h`: This is the header file for `main_extremum.c`.

- `derivatives.c`: Defines functions that calculate the first and second derivative for an arbitrary function.
- `derivatives.h`: This is the header file for `derivatives.c`.

- `solve.c`:  This defines the bisect method as well as Newton's method for solving f(x) = nu, for an arbitrary function f(x) as well as an arbitrary value nu.
- `solve.h`: This is the header file for `solve.c`.

- `vector_mtx.c`: This file defines vectors and matrices of specified size.
- `vector_mtx.h`: This is the header file for `vector_mtx.c`.

- `numerov_params.h`: This is the header file for the common data that will remain unchanged.
- `params.h`: This is the header file that collects problem-specific data

- Nuc_261023938_CA_4_Results.dat: Result file from `main_schrodinger.c` that displays the parameter values for mass, r0, Ea, ka, ell, x0, nucA, nucZ, nmax forward, and nmax backward. Mass, energy, and momentum have been converted back to the eV unit.
- input_coulomb.txt: Contains the values for mass, the energy unit eV, the angular momentum ell, NucA, and NucZ.
- input_n_params.txt: Contains the values for nmax forward and nmax backward.


## Usage

Usage is descibed in `Usage.md`.

## Sources

No sources used other than the example code provided by Matthew Heffernan and that of Dr. Sangyong Jeon.
