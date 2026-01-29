# ReadMe Main

Author: Lisa Rudolph

Email address: lisa.rudolph@mail.mcgill.ca


## Project Overview

This project allows us to solve the Schrodinger equation via the Shooting method for either the Coulomb or Woods-Saxon potential while using different values of angular momentum, ell.

In an attempt to organize the files and data, this project is broken up into two sections with two subsequent subsections. The first two folders differentiate the type of potential that is being used, and the two subfolders for each of these folders specifies the value for the angular momentum, ell.

Information about running the program can be found in the `Usage.md` file, and information on how to change the values for Et_min and Et_max to find the value of the first 3-4 energy levels can be found there as well, or below under Usage.

Compiler: gcc 11.2.0

## Physics Background


This project was created in order to numerically the Schrodinger equation:

$$ ( -d^{2}/dx^{2} + l(l+1)/x^{2} + \tilde{V}(x) + \tilde{E}_{nl} ) \tilde{u}_{nl}(x) = 0 $$

where $\mu$ is the effective mass, the momentum $` ka = \sqrt{s* \mu *Ea} `$, and $` x = ka*r `$. $` \tilde{V}(x) `$ and $` \tilde{E}_{nl} `$ can be written in terms of:

$$\tilde{V}(x) = V(x/ka)/Ea $$ 
  
  and  

$$\tilde{E}_{nl} = -|E_{nl}|/Ea $$

We can define the energy scale $Ea$ as the minimum value of the potential $`V_{eff} = 1/(2* \mu *r^{2}) + V(r)`$. Here we let $`l(l+1)->1`$ and assume that V(r) is no more singular than $`1/r`$ as $`r->0`$. In order to obtain the minimum point we need to solve the equation

 $$ V'_{eff}(r) = -1/(\mu * r^{3}) + V'(r) = 0 $$

This can be done by using the first derivative of the function to calculate the extremum.

Following this, the goal is to numerically solve the Schrodinger equation with the following boundary conditions:

$$ \lim_{x\to 0} \tilde{u}_{nl}(x) = 0 $$

    
$$ \lim_{x\to\infty} \tilde{u}_{nl}(x) = 0 $$

The process for solving the differential equation can be broken into two parts were the equation is solved for two different conditions, and then they are matched at $x_{c}$:

1.) $` 0 < x <= x_{c} : \tilde{u}_{1}(x) `$


2.) $` x_{c} <= x < x_{f} : \tilde{u}_{11}(x) \text{  with  }  x_{f} >> 1 `$

The boundary condition at $`x = 0`$ is $`\tilde{u}_{1}(0) = 0`$.

We can then implement the Shooting method, which begins with choosing a value for $`\tilde{E}_{nl}`$, calculates $`\tilde{u}_{1}(x)`$ and $`\tilde{u}_{11}(x)`$, and then adjusts the value for $`\tilde{E}_{nl}`$ until $`\tilde{u}_{1}'(x)/\tilde{u}_{1}(x) `$ and $`\tilde{u}_{11}'(x)/\tilde{u}_{11}(x)`$ match at $x_{c}$.

In order to calculate $x_{c}$ we can use the classical turning point which is defined as the point where


 $$l(l+1) + x_{c}^{2} * (\tilde{V}_{x_{c}} + \tilde{E}_{nl}) = 0$$


This equation can be solved via Newton's Method, described below.

This project sets up the preparation for the Shooting method, which will be implemented in the next assignment.


###### First and Second Derivative

Using the Taylor expansion on the function f(x), we obtain the expression:

$$f(x+h) = f(x) + hf'(x) + h^{2}/2 f"(x) + h^{3}/6 f"'(x) + O(h^{4})$$

From here we can obtain an expression for f'(x):

$$f'(x) = \frac{[f(x+h) - f(x-h)]}{2h} + O(h^{2})$$

And using that expression as well as the one for f(x+h), we can obtain an expression for f"(x):


$$f"(x) = \frac{[f(x+h) + f(x-h) - 2f(x)]}{h^{2}} + O(h^{3})$$


In calculus, the limit as $`h->0`$ would be taken, however we set h to a small value: $`h = x * 1E-5`$, for all $x$, so long as $`x!= 0.`$ The reason $`h = x * 1E-5`$ is chosen is that this value is best for achieving double precision in our results.

###### Numerov Method

The Numerov method enables us to solve equations that take the form of $`d^{2}y/dx^{2} = F(x)y(x)`$. By only knowing $y_{0}$ and $y_{1}$, we are able to solve for $`y_{n+1}`$ for $`n >= 2`$.

In order to do this, we use the general equation $`d^{2}y/dx^{2} = F(x)y(x)`$. Letting the initial point be $x_{0}$, we can declare the final point to be $x_{f}$, where $`x_{f} = x_{0} + N_{max}\times h`$ and $h$ is the step size. The step size $h$ can be calculated from $`h = (x_{f} - x_{0}) / N_{max}`$.

Letting $`x_{n} = x_{0} + n* h`$ (where $n$ in an integer ranging from 0 to $N_{max}$), $`y_{n} = y(x_{n})`$, and $`F_{n} = F(x_{n})`$, one can use Taylor expansion to show:

$$y_{n+1} + y_{n-1} - 2y_{n}  =  h^{2} \frac{d^{2}y}{dx^{2}}|(x=x_{n}) + \frac{h^{4}}{12} \frac{d^{4}y}{dx^{4}}|(x=x_{n}) + O(h^{6})$$

which applies for any function y(x). Using $`d^{2}y/dx^{2} = F(x)y(x)`$, we can obtain

$$y_{n+1} + y_{n-1} - 2y_{n}  = h^{2} F_{n}*y_{n} + \frac{h^{4}}{12} \frac{d^{2}}{dx^{2}} F(x)y(x)|(x=x_{n}) + O(h^{6})$$

Using the fact that:

$$\frac{d^{2}}{dx^{2}} F(x)y(x)|(x=x_{n})  =  \frac{(Fy)_{n+1} + (Fy)_{n-1} -2(Fy)_{n}}{h^{2}} + O(h^{2})$$

we can obtain an expression for $y_{n+1}$:

$$y_{n+1}  =  \frac{\bigg[2\bigg(1 + \frac{5h^{2}}{12}F_{n}\bigg)y_{n}  -  \bigg(1 - \frac{h^{2}}{12}F_{n-1}\bigg)y_{n-1}\bigg]}{\bigg(1 - \frac{h^{2}}{12}F_{n+1}\bigg)}  +  O(h^{6})$$


Therefore, by only knowing $y_{0}$ and $y_{1}$, one is able to solve for $y_{n}$, where $`n >= 2`$.

###### Newton's Method

In Newton's Method we use the approximate definition of the derivative:

$$f'(x_{n}) = \frac{f(x_{n+1}) - f(x_{n})} / {x_{n+1} - x_{n}}$$

rearrange it, and let $`f(x_{n+1}) = \nu`$, in order to achieve the expression:

$$x_{n+1} = x_{n} + (\nu - f(x_{n}))/ f'(x_{n})$$

Unlike the Bisect Search Method that was used in the previous computing assignment, we do not specify a range, instead we specify a starting point value for $x$, $x_{0}$.


###### Bisect Search Method

In the Bisect Search Method we evaluate $`f(x) - \nu`$ between the range $x_{min}$ and $x_{max}$ in order to find $f_{min}$ and $f_{max}$. As well, we calculate the average value of $x$, $x_{mid}$, to find $f_{mid}$. Once these are known, we compare them to one another.

If $`f_{min}*f_{mid} < 0 `$then we set a new value for $x_{max}$, $x_{mid}$, and then repeat the process.

However, if $`f_{mid}*f_{max} < 0 `$then we set a new value for $x_{min}$, $x_{max}$, and once again repeat the process.

We continue doing this until $`|f_{mid}/\nu| < \epsilon,`$ where $\epsilon$ is a sufficiently small enough number that implies that our method solves our problem to enough accuracy. Once this criteria is met, it implies that the value of $x_{mid}$ at that time is the solution to our problem.

###### Woods-Saxon potential


The Woods-Saxon potential can be described as follows:

$$V(r) = \frac{- V_{0}}{[1 + exp((r-R)/a)]}$$

Where $a$ represents the surface thickness of the nucleus, $R$ is the nuclear radius $`r_{0} * A^{1/3}`$, and $V_{0}$ is the potential well depth. In this project we let $a$=0.7, $`V_{0}=50/\hbar c`$, and $r_{0}$ be given by $r0$ in `params.h`.

###### Coulomb Potential

The Coulomb potential is described by

$$ V(r) = \frac{- Q}{4*\pi*\epsilon_{0}*r}$$

which can be written as

$$V(r) = \frac{- \alpha_{EM}}{r} $$

where $`\alpha_{EM}= 1/137`$.



## Description of Files
- `Coulomb`: The subfolder that houses the files to solve the Schrodinger equation using the Coulomb potential for angular momentum, ell, 0 and 1.
- `Woods_Saxon`: The subfolder that houses the files to solve the Schrodinger equation using the Woods-Saxon potential for angular momentum, ell, 0 and 1.


## Usage

Usage is described in `Usage.md`. However, instructions for calculating the first 3 or 4 energy levels for each potential are included below as well.

###### Calculating the first 4 energy levels for Coulomb_ell_0

The initial values for Et_min and Et_max are 0.01 and 1.1. In order to calculate the values for Et and Eb for the first 4 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_coulomb.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.9, and change line 7 to 1.1
2nd Energy Level-> Change line 6 to 0.24, and change line 7 to 0.26
3rd Energy Level-> Change line 6 to 0.1, and change line 7 to 0.15
4th Energy Level-> Change line 6 to 0.06, and change line 7 to 0.07

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Coulomb_ell_0_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Coulomb_ell_0_schrodinger_data.dat`.


###### Calculating the first 3 energy levels for Coulomb_ell_1

The initial values for Et_min and Et_max are 0.01 and 1.1.
  * Note: If the values for Et_min and Et_max are kept as 0.01 and 1.1, and the file is run, the program will only produce `261023938_CA_5_Coulomb_ell_1_bound_state_err.dat` before declaring that the derivative is too small and then exiting. In order to avoid this the values for Et_min and Et_max must be immediately changed to one of the ranges specified below.

In order to calculate the values for Et and Eb for the first 3 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_coulomb.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.23, and change line 7 to 0.27
2nd Energy Level-> Change line 6 to 0.107, and change line 7 to 0.117
3rd Energy Level-> Change line 6 to 0.06, and change line 7 to 0.065

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Coulomb_ell_1_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Coulomb_ell_1_schrodinger_data.dat`.


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
