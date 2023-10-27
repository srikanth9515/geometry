//Code by G V V Sharma
//October 27, 2023
//matrix operations using arrays
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/matfun.h"


int  main()
{
FILE *fp; //file pointer
double **A,**B,**C;//declare vertices
double **m1,**m2,**m3;//declare vertices
double a,b,c; //triangle sides
int m =2, n=3, i, j;
double **mat =createMat(m,n);//vertices matrix 
mat = loadmat("vertices.dat",m, n);//loading matrix from file

//Extracting vertices
A = col(mat,m,0);
B = col(mat,m,1);
C = col(mat,m,2);

//Direction vectors
m1 = linalg_sub(B,A,m,1);
m2 = linalg_sub(C,B,m,1);
m3 = linalg_sub(A,C,m,1);

//Sides
a = linalg_norm(m2,m);
b = linalg_norm(m3,m);
c = linalg_norm(m1,m);

//Printing
printf("%lf\n",a);
printf("%lf\n",b);
printf("%lf\n",c);
/*
printmat(m1,m,1);
printmat(m2,m,1);
printmat(m3,m,1);
*/


    return 0;
}
