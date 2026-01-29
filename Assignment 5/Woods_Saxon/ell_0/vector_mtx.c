#include <stdio.h>
#include <stdlib.h>
#include "vector_mtx.h"

// Vectors and Matrices

double *vector_malloc(int nmax)
{
 double *pt;
 int n;

 pt = (double *)malloc(sizeof(double)*nmax);

 for(n=0; n<nmax; n++) pt[n] = 0.0; 
 
 return pt;
}// vector_malloc


double **mtx_malloc(int mmax, int nmax)
{
 double **pt;
 int m, n;

 pt = (double **)malloc(sizeof(double *)*mmax);

 for(m=0; m<mmax; m++)
  {
   pt[m] = (double *)malloc(sizeof(double)*nmax);
  }// m-loop

 for(m=0; m<mmax; m++)
  {
   for(n=0; n<nmax; n++) {pt[m][n] = 0.0;}
  }// n-loop
 
 return pt;
}// mtx_malloc

void mtx_free(double **mtx, int mmax)
{
 int m;

 for(m=0; m<mmax; m++) { free(mtx[m]); }
 free(mtx);
 
 return;
}// mtx_free

