# ReadMe for extremum_test

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca


## Project Overview

This project covers the method for solving f'(x) = 0 for x, relying on calculating the first derivative of the function f(x) and using Newton's method to solve for f'(x) = 0.

Once compiled, and the `extremum_test` executable run from the terminal, 261023938_CA_2_Results.dat is created that displays the results for the extremum (x_extremum), the function evaluated at x_extremum, and the value of the curvature (which is just f"(x_extremum)).

There are three different test functions in `main_extremum.c` that can be chosen, however Test 1 is the default.


Compiler: gcc 11.2.0

## Physics Background

This project was created in order to calculate the minimum or maximum of a given function f(x). In order to accomplish this the first derivative of this function was taken, set to 0, and then Newton's Method was employed to solve for x, returning the value of the extremum.

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

- `main_extremum.c`: This is the main executable that calculates the value of the extremum, the function evaluated at the extremum, and the curvature for three different test functions. As well, this is where the initial value of x is specified and which test function we want to use. Lastly, this is where the .dat file is created and the results are written to.
- `extremum.c`: Defines the Extremum_GetExtremum function, which calculates the first derivative of a function, finds the value of the extremum, and calculates the curvature (the second derivative of the function evaluated at the extremum).
- `derivatives.c`: Defines functions that calculate the first and second derivative for an arbitrary function.
- `solve.c`:  This defines the bisect method as well as Newton's method, the latter which will be used for this project.
- `extremum.h`: This is the header file for `main_extremum.c`.
- `derivatives.h`: This is the header file for `derivatives.c`.
- `solve.h`: This is the header file for `solve.c`.
- Nuc_261023938_CA_2_Results.dat: Result file from `main_extremum.c` that has been saved and the name has been modified so that when the main executable is run the file is not written over.

## Usage

Usage is descibed in `Usage.md`.

## Sources

No sources used other than the example code provided by Matthew Heffernan and that of Dr. Sangyong Jeon.
