#### Usage numerov_test ####

## Compilation

In the `C-or-Cpp` directory `make` or `make numerov_test` will generate an executable `numerov_test` from the source files.

## Running

Once compiled, the `numerov_test` executable can be run directly from terminal: `./numerov_test input_data.txt`

This produces the following:
- 261023938_CA_3_Results.dat : Contains the values of xn and y[n] where n is an integer ranging from 0 to nmax, xn = x_i + n*h, and the function y is evaluated at n.
- Params.dat : States the parameters that were used for x_i, x_f, y_0, y_1, nmax, and h.

## Cleaning

To safely remove the `numerov_test` executable, run `make clean` in terminal.
