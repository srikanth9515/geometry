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
double **m1,**m2,**m3;//direction vectors
double **n1,**n2,**n3;//normal vectors
double **temp;//temporary array
double **lam;//eigenvalue vector
double **unit;//unit vector
double c1,c2,c3;//direction vectors
double a,b,c; //triangle sides
int m =2, n=3, i, j;
double **mat =createMat(m,n);//vertices matrix 
mat = loadMat("vertices.dat",m, n);//loading matrix from file
//temp= loadMat("circ.dat",4, 1);//loading matrix from file
temp= loadMat("matex.dat",2, 2);//loading matrix from file

//Extracting vertices
A = Matcol(mat,m,0);
B = Matcol(mat,m,1);
C = Matcol(mat,m,2);

//Direction vectors
m1 = Matsub(B,A,m,1);
m2 = Matsub(C,B,m,1);
m3 = Matsub(A,C,m,1);

//Line Parameters
//Normal vectors
n1 = normVec(m1);
n2 = normVec(m2);
n3 = normVec(m3);
//Line constants
c1 = Matdot(n1,A,2);


//Sides
a = Matnorm(m2,m);
b = Matnorm(m3,m);
c = Matnorm(m1,m);

//Normal vectors

//Printing
//Print vertices 
/*
printMat(A,2,1);
printMat(B,2,1);
printMat(n1,2,1);//normal vector
printf("%lf\n",c1);//AB line coefficient

//Triangle sides
printf("%lf\n",a);
printf("%lf\n",b);
printf("%lf\n",c);

//Rotation matrix
//printMat(rotMat(M_PI/2),2,2);

//Normal vectors
/*
printMat(n1,2,1);
printMat(n2,2,1);
printMat(n3,2,1);
*/
//Direction vectors
/*
printMat(m1,m,1);
printMat(m2,m,1);
printMat(m3,m,1);

//Circulant matrix
circulantMat(temp, 4);
printMat(temp,4,4);

//Matrix inversion
//printMat(Matinv(temp, 2),2,2);
//Median
//temp= Matsec(A,B,2,1);
printMat(temp,2,1);
*/
//printMat(temp,2,2);
lam = Mateigval(temp);
//printMat(Matrow(temp,0,2),2,1);
//lam = Matquad(1,1,-30);
unit = Matrow(temp,0,2);
unit = Matunit(unit,2);
//printMat(unit,2,1);
//printMat(lam,2,1);
Mateigvec(temp, lam);
//eigenvalues of a 2x2 matrix
    return 0;
}
