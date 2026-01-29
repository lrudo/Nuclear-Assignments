# ReadMe for deriv_test

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca


## Project Overview

This portion of the project covers how to calculate the first and second derivative for an arbitrary function, f(x).

Once compiled, and the `deriv_test` executable run from the terminal, the resulting values for x, f(x), f'(x), and f"(x) are saved to `261023938_CA_2_Deriv_Test.dat` for the function f(x) = sin(x).

Compiler: gcc 11.2.0

## Physics Background

This project was created in order to numerically calculate the first and second derivative for the function f(x).

Analytical solutions for derivatives are often available, however sometimes the analytic derivatives are too complicated to calculate or are not available. In order to circumvent this issue we can employ a numerical method to calculate the derivative.

In this project we calculate the first and second derivative for the function $`f(x) = \sin(x)`$.


# First and Second Derivative

Using the Taylor expansion on the function f(x), we obtain the expression:

$$f(x+h) = f(x) + hf'(x) + \frac{h^{2}}{2} f"(x) + \frac{h^{3}}{6} f"'(x) + O(h^{4})$$

From here we can obtain an expression for f'(x):

$$f'(x) = \frac{f(x+h) - f(x-h)}{2h} + O(h^{2})$$

And using that expression as well as the one for f(x+h), we can obtain an expression for f"(x):

$$f"(x) = \frac{f(x+h) + f(x-h) - 2f(x)}{h^{2}} + O(h^{3})$$

In calculus, the limit as $`h->0`$ would be taken, however we set h to a small value: $`h = x*1E-5`$, for all $x$, so long as $`x!= 0`$. The reason $`h = x *1E-5`$ is chosen is that this value is best for achieving double precision in our results.

## Description of Files

- `main_deriv.c`: This is the main executable that performs the desired calculations and specifies what function f(x) we are using, as well as the values for the variables, ie. the range of x values and the number of steps we use. This file also creates the .dat file and writes our results to it.
- `derivatives.c`:  This defines all of the functions we will be using for this part of the project, as well as functions that we will be using for the second part.
- `derivatives.h`: This is the header file for `main_deriv.c`.
- Nuc_261023938_CA_2_Deriv_Test.dat: Result file from `main_deriv.c` that has been saved and the name has been modified so that when the main executable is run the file is not written over.
- plotted_outputs_for_deriv_test.png: The data from Nuc_261023938_CA_2_Deriv_Test.dat, f(x), f'(x), and f"(x) for sin(x)  plotted together.

## Usage

Usage is descibed in `Usage.md`.

## Sources

No sources used other than the example code provided by Matthew Heffernan and that of Dr. Sangyong Jeon.
