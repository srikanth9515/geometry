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
int m =2, n=3, i, j;
//head = loadList("A.dat", 2, 1);
//printList(head,2,1);
head = loadList("vertices.dat", m, n);
printList(head,m,n);
    return 0;
}
