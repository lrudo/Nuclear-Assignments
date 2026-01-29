# Usage Woods-Saxon ell_0 

## Compilation for Woods-Saxon Potential, for ell=0

Change the directory to `/Woods_Saxon/ell_0`. From there, `make` or `make schrodinger` will generate an executable `schrodinger` from the source files.


## Running

Once compiled, the `schrodinger` executable can be run directly from terminal: `./schrodinger input_nuc.txt input_n_params.txt`

This produces the following:
- 261023938_CA_5_Woods_ell_0_bound_state_err.dat: Produces the bound state error for ell_0 when Et_min=0.1 and Et_max=0.9999
- 261023938_CA_5_Woods_ell_0_schrodinger_data.dat: Shows the value of Et and Eb produced from E_min and E_max
- 261023938_CA_5_Woods_ell_0_yb.dat: The data for the backwards wave function
- 261023938_CA_5_Woods_ell_0_yf.dat: The data for the forwards wave function
- 261023938_CA_5_Woods_ell_0_schrodinger_params.dat: Result file from `main_schrodinger.c` that displays the parameter values used.

## Calculating the first 4 energy levels

The initial values for Et_min and Et_max are 0.1 and 0.9999. In order to calculate the values for Et and Eb for the first 4 energy levels, the values of Et_min and Et_max must be changed. In order to do so, the values of the 6th and 7th lines (which are also the second-to-last and the last lines) of `input_nuc.txt` must be changed. The changes are as follows:

1st Energy Level-> Change line 6 to 0.918, and change line 7 to 0.919
2nd Energy Level-> Change line 6 to 0.709, and change line 7 to 0.710
3rd Energy Level-> Change line 6 to 0.421, and change line 7 to 0.422
4th Energy Level-> Change line 6 to 0.112, and change line 7 to 0.113

Once the values are changed, save the file and run the program as specified above. Keep repeating this process for the rest of the energy levels. The results will be saved in the `261023938_CA_5_Woods_ell_0_schrodinger_data.dat` file.
  * Note: Every time the program is run this file will be over-written. In order to view all of the Et and Eb values with their corresponding Et_min and Et_max values please see `Nuc_261023938_CA_5_Woods_ell_0_schrodinger_data.dat`.

## Cleaning

To safely remove the `schrodinger` executable, run `make clean` in terminal.
