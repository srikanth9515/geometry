//Code by G V V Sharma
//October 23, 2023
//matrix operations using lists
#include <stdio.h>
#include <stdlib.h>
#include "libs/matlist.h"


int  main()
{
FILE *fp; //file pointer
double val;//for reading file data
vriksh *head, *temp;//head of the array
node *a;
int m =3, n=3, i, j;
//head = loadMat("B.dat", m, n);
head = loadMat("A.dat", 2, 1);
//printMat(head,m,n);
printMat(head,2,1);
    return 0;
}
