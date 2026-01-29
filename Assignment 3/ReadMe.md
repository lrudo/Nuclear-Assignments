# ReadMe for numerov_test

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca


## Project Overview

This project covers how to use the Numerov method in order to solve the equation of form
d^2y / dx^2 = F(x)y(x).

Once compiled, and the `numerov_test input_data.txt` executable run from the terminal, the resulting values for x_n, x_n = x_i + n*h, and the function y evaluated at n, y[n], are saved to 261023938_CA_3_Results.dat for the integer n ranging from 0 to nmax. As well, the values for the parameters are saved to the params.dat file.

Compiler: gcc 11.2.0

## Physics Background

This project was created in order to numerically solve functions akin to that of the radial equation: d^2y/dx^2 = F(x)y(x). One method of doing so is known as the Numerov method, where by knowing y_0 and y_1, one is able to solve for y_(n+1) for n >= 2.

In order to do this, we use the general equation d^2y/dx^2 = F(x)y(x). Letting the initial point be x_0, we can declare the final point to be x_f, where x_f = x_0 + N_max*h and h is the step size. The step size h can be calculated from h = (x_f - x_0) / N_max.

Letting x_n = x_0 + n*h (where n in an integer ranging from 0 to N_max), y_n = y(x_n), and F_n = F(x_n), one can use Taylor expansion to show:

y_(n+1) + y_(n-1) - 2y_n  =  h^2 d^2y/dx^2|(x=x_n) + h^4/12 d^4y/dx^4|(x=x_n) + O(h^6),

which applies for any function y(x). Using d^2y/dx^2 = F(x)y(x), we can obtain

y_(n+1) + y_(n-1) - 2y_n  = h^2 F_n*y_n + h^4/12 d^2/dx^2 F(x)y(x)|(x=x_n) + O(h^6).

Using the fact that:

d^2/dx^2 F(x)y(x)|(x=x_n)  =  [(Fy)__(n+1) + (Fy)_(n-1) -2(Fy)_n]/ h^2 + O(h^2),

we can obtain an expression for y_(n+1):

y_(n+1)  =  [2(1 + (5h^2/12)F_n)y_n  -  (1 - (h^2/12)F_(n-1))y_(n-1)] / (1 - (h^2/12)F_(n+1))  +  O(h^6).

Therefore, by only knowing y_0 and y_1, one is able to solve for y_n, where n >= 2.


## Description of Files

- `main_numerov.c`: This is the main executable that performs the desired calculations and specifies what function f(x) we are using. This file also creates the .dat files where our results and parameter values are written to.
- `numerov.c`:  This defines all of the functions we will be using for this part of the project.
- `vector_mtx.c`: This file defines vectors and matrices of specified size.
- `numerov.h`: This is the header file for `main_numerov.c`.
- `numerov_params.h`: This is the header file for the common data that will remain unchanged.
- `params.h`: This is the header file that collects problem-specific data
- `vector_mtx.h`: This is the header file for `vector_mtx.c`.
- Nuc_261023938_CA_3_Results_F(x)_-1.dat: Result file from `main_numerov.c` for the function F(x) = -1 that has been saved and the name has been modified so that when the main executable is run the file is not written over.
- Nuc_261023938_CA_3_Results_F(x)_-x.dat: Result file from `main_numerov.c` for the function F(x) = -x that has been saved and the name has been modified so that when the main executable is run the file is not written over.
- Nuc_params.dat : Parameters used in `main_numerov.c` that have been saved and the name has been modified so that when the main executable is run the file is not written over.
- F(x)__-1.png: Plot of data from Nuc_261023938_CA_3_Results_F(x)_-1.dat, for the function F(x) = -1.
- F(x)__-x.png: Plot of data from Nuc_261023938_CA_3_Results_F(x)_-x.dat, for the function F(x) = -x.
- input_data.txt: Contains the values for x_i, x_f, y_0, y_1, and nmax


## Usage

Usage is descibed in `Usage.md`.

## Sources

No sources used other than the example code provided by Matthew Heffernan and that of Dr. Sangyong Jeon.
