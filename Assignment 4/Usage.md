#### Usage schrodinger ####

## Compilation

In the `C-or-Cpp` directory `make` or `make schrodinger` will generate an executable `schrodinger` from the source files.

## Running

Once compiled, the `schrodinger` executable can be run directly from terminal: `./schrodinger input_coulomb.txt input_n_params.txt`

This produces the following:
- 261023938_CA_4_Results.dat: Result file from `main_schrodinger.c` that displays the parameter values for mass, r0, Ea, ka, ell, x0, nucA, nucZ, nmax forward, and nmax backward. Mass, energy, and momentum have been converted back to the eV unit.

## Cleaning

To safely remove the `schrodinger` executable, run `make clean` in terminal.
