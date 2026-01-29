# Usage Coulomb

For this project there are two different potentials that are being used: the Coulomb, and the Woods-Saxon potential. This folder houses the files for the Coulomb potential. Within this folder there are two different folders for two different values of angular momentum: 0 and 1.

All of the info below describes how to run the files within the different folders and describes what their output is as well as how to change the values for Et_min and Et_max to find the value of the first 3-4 energy levels.


# Usage Coulomb ell_0

## Compilation for Coulomb Potential, for ell=0

Change the directory to `/Coulomb/ell_0`. From there, `make` or `make schrodinger` will generate an executable `schrodinger` from the source files.

## Running

Once compiled, the `schrodinger` executable can be run directly from terminal: `./schrodinger input_coulomb.txt input_n_params.txt`

This produces the following:
- 261023938_CA_5_Coulomb_ell_0_bound_state_err.dat: Results from calculating the bound state error for ell_1 when Et_min=0.01 and Et_max=1.1
- 261023938_CA_5_Coulomb_ell_0_schrodinger_data.dat: Contains the resulting Et and Eb values for the given Et range.
- 261023938_CA_5_Coulomb_ell_0_yb.dat: The data for the backwards wave function
- 261023938_CA_5_Coulomb_ell_0_yf.dat: The data for the forwards wave function
- 261023938_CA_5_Coulomb_ell_0_schrodinger_params.dat: Result file from `main_schrodinger.c` that displays the parameter values used.

## Calculating the first 4 energy levels

The initial values for Et_min and Et_max are 0.01 and 1.1. In order to calculate the values for Et and Eb for the first 4 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_coulomb.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.9, and change line 7 to 1.1
2nd Energy Level-> Change line 6 to 0.24, and change line 7 to 0.26
3rd Energy Level-> Change line 6 to 0.1, and change line 7 to 0.15
4th Energy Level-> Change line 6 to 0.06, and change line 7 to 0.07

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Coulomb_ell_0_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Coulomb_ell_0_schrodinger_data.dat`.

## Cleaning

To safely remove the `schrodinger` executable, run `make clean` in terminal.


# Usage Coulomb ell_1

## Compilation for Coulomb Potential, for ell=1

Change the directory to `/Coulomb/ell_1`. From there, `make` or `make schrodinger` will generate an executable `schrodinger` from the source files.


## Running

Once compiled, the `schrodinger` executable can be run directly from terminal: `./schrodinger input_coulomb.txt input_n_params.txt`

This produces the following:
- 261023938_CA_5_Coulomb_ell_1_bound_state_err.dat: Results from calculating the bound state error for ell_1 when Et_min=0.01 and Et_max=1.1
- 261023938_CA_5_Coulomb_ell_1_schrodinger_data.dat: Contains the resulting Et and Eb values for the given Et range.
- 261023938_CA_5_Coulomb_ell_1_yb.dat: The data for the backwards wave function
- 261023938_CA_5_Coulomb_ell_1_yf.dat: The data for the forwards wave function
- 261023938_CA_5_Coulomb_ell_1_schrodinger_params.dat: Result file from `main_schrodinger.c` that displays the parameter values used.

## Calculating the first 3 energy levels

The initial values for Et_min and Et_max are 0.01 and 1.1.
  * Note: If the values for Et_min and Et_max are kept as 0.01 and 1.1, and the file is run, the program will only produce `261023938_CA_5_Coulomb_ell_1_bound_state_err.dat` before declaring that the derivative is too small and then exiting. In order to avoid this the values for Et_min and Et_max must be immediately changed to one of the ranges specified below.

In order to calculate the values for Et and Eb for the first 3 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_coulomb.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.23, and change line 7 to 0.27
2nd Energy Level-> Change line 6 to 0.107, and change line 7 to 0.117
3rd Energy Level-> Change line 6 to 0.06, and change line 7 to 0.065

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Coulomb_ell_1_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Coulomb_ell_1_schrodinger_data.dat`.

## Cleaning

To safely remove the `schrodinger` executable, run `make clean` in terminal.
