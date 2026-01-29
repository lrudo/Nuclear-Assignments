# ReadMe for Woods-Saxon

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca

## Project Overview

This project allows us to solve the Schrodinger equation via the Shooting method while using the Woods-Saxon potential.

In an attempt to organize the files and data, this folder contains two subfolders: ell_0 and ell_1. These subfolders specify the value of the angular momentum, ell, being used.

Instructions for running the programs as well as changing the values for Et_min and Et_max to find the first 3-4 energy levels are included below under Usage, as well as in the `Usage.md` file.

In order to run the program, the current directory must be changed to `/Woods_Saxon/ell_0` or `Woods_Saxon/ell_1`, and then compiled. Once compiled, and the `./schrodinger input_nuc.txt input_n_params.txt` executable run from the terminal, the resulting parameter values that were used are saved to 261023938_CA_5_Woods_ell_X_schrodinger_params.dat. As well, the data for the bound state error, the values of Et and Eb for the given energy range, and the forwards and backwards wavefunctions are saved to 261023938_CA_5_Woods_ell_X_bound_state_err.dat, 261023938_CA_5_Woods_ell_X_schrodinger_data.dat, 261023938_CA_5_Woods_ell_X_yf.dat, and 261023938_CA_5_Woods_ell_X_yb.dat respectively, where X represents either 0 or 1 for the possible angular momentum values.

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


###### First and Second Derivative

Using the Taylor expansion on the function f(x), we obtain the expression:

f(x+h) = f(x) + hf'(x) + h^2/2 f"(x) + h^3/6 f"'(x) + O(h^4)

From here we can obtain an expression for f'(x):

f'(x) = [f(x+h) - f(x-h)]/2h + O(h^2)

And using that expression as well as the one for f(x+h), we can obtain an expression for f"(x):

f"(x) = [f(x+h) + f(x-h) - 2f(x)]/(h^2) + O(h^3).

In calculus the limit as h->0 would be taken, however we set h to a small value: h = x*1E-5, for all x, so long as x!= 0. The reason h = x *1E-5 is chosen is that this value is best for achieving double precision in our results.


###### Numerov Method

The Numerov method enables us to solve equations that take the form of d^2y/dx^2 = F(x)y(x). By only knowing y_0 and y_1, we are able to solve for y_(n+1) for n >= 2.

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


###### Newton's Method

In Newton's Method we use the approximate definition of the derivative:

f'(x_n) = [f(x_(n+1)) - f(x_n)] / (x_(n+1) - x_n),

rearrange it, and let f(x_(n+1)) = nu, in order to achieve the expression:

x_(n+1) = x_n + (nu - f(x_n))/ f'(x_n).

Unlike the Bisect Search Method that was used in the previous computing assignment, we do not specify a range, instead we specify a starting point value for x, x_0.


###### Bisect Search Method

In the Bisect Search Method we evaluate f(x) - nu between the range x_min and x_max in order to find f_min and f_max. As well, we calculate the average value of x, x_mid, to find f_mid. Once these are known, we compare them to one another.

If f_min*f_mid < 0 then we set a new value for x_max, x_mid, and then repeat the process.

However, if f_mid*f_max < 0 then we set a new value for x_min, x_max, and once again repeat the process.

We continue doing this until |f_mid/nu| < epsilon, where epsilon is a sufficiently small enough number that implies that our method solves our problem to enough accuracy. Once this criteria is met, it implies that the value of x_mid at that time is the solution to our problem.


###### Woods-Saxon potential

The Woods-Saxon potential can be described as follows:

V(r) = - Vo / [1 + exp((r-R)/a)]

Where a represents the surface thickness of the nucleus, R is the nuclear radius r_0 * A^(1/3), and V_0 is the potential well depth. In this project we let a=0.7, V_0=50/hbarc, and r_0 be given by r0 in `params.h`.



## Description of Files
- `ell_0`: The subfolder that houses the files to solve the Schrodinger equation using the Woods-Saxon potential when the angular momentum, ell, is 0.
- `ell_1`: The subfolder that houses the files to solve the Schrodinger equation using the Woods-Saxon potential when the angular momentum, ell, is 1.


## Usage

Usage is descibed in `Usage.md`. However, instructions for calculating the first 3 or 4 energy levels are included below as well.

###### Calculating the first 4 energy levels for Woods_ell_0

The initial values for Et_min and Et_max are 0.1 and 0.9999. In order to calculate the values for Et and Eb for the first 4 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_nuc.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.918, and change line 7 to 0.919
2nd Energy Level-> Change line 6 to 0.709, and change line 7 to 0.710
3rd Energy Level-> Change line 6 to 0.421, and change line 7 to 0.422
4th Energy Level-> Change line 6 to 0.112, and change line 7 to 0.113

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Woods_ell_0_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Woods_ell_0_schrodinger_data.dat`.


###### Calculating the first 3 energy levels for Woods_ell_1

The initial values for Et_min and Et_max are 0.1 and 0.9999.
  * Note: If the values for Et_min and Et_max are kept as 0.1 and 0.9999, and the file is run, the program will only produce `261023938_CA_5_Woods_ell_1_bound_state_err.dat` before declaring that the derivative is too small and then exiting. In order to avoid this the values for Et_min and Et_max must be immediately changed to one of the ranges specified below.

In order to calculate the values for Et and Eb for the first 3 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_nuc.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.82, and change line 7 to 0.85
2nd Energy Level-> Change line 6 to 0.56, and change line 7 to 0.60
3rd Energy Level-> Change line 6 to 0.25, and change line 7 to 0.29

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Woods_ell_1_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Woods_ell_1_schrodinger_data.dat`.


## Sources

No sources used other than the example code provided by Matthew Heffernan and that of Dr. Sangyong Jeon.
