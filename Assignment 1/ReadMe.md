# ReadMe for solve_test

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca


## Project Overview

This project covers two different methods to solve for $`f(x) = \nu`$: the Bisect Search  Method and Newton's Method.

Once compiled, and the `solve_test` executable run from the terminal, the resulting count number and solution are displayed for both methods in their attempt to solve $`\sin(x) = 0`$.

Compiler: gcc 11.2.0

## Physics Background

This project was born out of the need to find a numerical solution for the radial portion of the Schrodinger equation for an arbitrary potential V(r).

As analytic solutions to these problems are not always available, we need a numerical method that will find the minimum of a function. In other words, we need to find a way to solve $`f(x) = 0`$.

In this project we use both the Bisect Search Method and Newton's Method to solve for $`\sin(x) = 0`$.

# Bisect Search Method

In the Bisect Search Method we evaluate $`f(x) - \nu`$ between the range $x_{min}$ and $x_{max}$ in order to find $f_{min}$ and $f_{max}$. As well, we calculate the average value of $x$, $x_{mid}$, to find $f_{mid}$. Once these are known, we compare them to one another.

If $`f_{min}*f_{mid} < 0 `$then we set a new value for $x_{max}$, $x_{mid}$, and then repeat the process.

However, if $`f_{mid}*f_{max} < 0 `$then we set a new value for $x_{min}$, $x_{max}$, and once again repeat the process.

We continue doing this until $`|f_{mid}/\nu| < \epsilon,`$ where $\epsilon$ is a sufficiently small enough number that implies that our method solves our problem to enough accuracy. Once this criteria is met, it implies that the value of $x_{mid}$ at that time is the solution to our problem.


# Newton's Method

In Newton's Method we take a different approach where we use the approximate definition of the derivative:

$$f'(x_{n}) = \frac{[f(x_{n+1}) - f(x_{n})]}{(x_{n+1} - x_{n})}$$

rearrange it, and let $`f(x_{n+1}) = \nu`$, in order to achieve the expression:

$$x_{n+1} = x_{n} + \frac{\nu - f(x_{n})}{f'(x_{n})}$$

Unlike the Bisect Search Method, we do not specify a range, instead we specify a starting point value for $x$, $x_{0}$.


Both of these methods have different strengths, which is why we are looking at both of them in order to solve the problem of $`\sin(x)=0`$.

## Description of Files

- `main_solve.c`: This is the main executable that performs the desired calculations and specifies what function f(x) we are using, as well as the values for the variables, ie. the range for x, as well as the value of nu.
- `solve.c`:  This defines all of the functions we will be using for this project, as well as functions that we may wish to use for future projects.
- `solve.h`: This is the header file for `main_solve.c`.

## Usage

Usage is descibed in `Usage.md`.

## Sources

No sources used other than the example code provided by Matthew Heffernan and that of Dr. Sangyong Jeon.
