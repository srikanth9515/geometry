//Code by G V V Sharma
//October 23, 2023
//Revised October 28, 2023
//matrix operations using lists
#include <stdio.h>
#include <stdlib.h>
#include "libs/listgen.h"


int  main()
{
FILE *fp; //file pointer
double val;//for reading file data
avyuh *trans, *temp;//head of the array
sadish *a,*heads;
avyuh *A,*B,*C;//triangle vertices
int m =2, n=3, i, j;
fp = fopen("A.dat","r");
//heads = loadVec(fp,3);
//head = loadList("A.dat", 3, 1);
//a = Vecind(heads,0);
//printf("%lf\n",a->data);
//printList(head,3,1);

//load matrix from file
temp= loadList("vertices.dat", m, n);
//temp= loadList("A.dat", 1, 3);

//Triangle vertices
//A = Listcol(temp,0);
//B = Listcol(temp,1);
//C = Listcol(temp,2);
/*
A = Listcol(temp,m,0);
B = Listcol(temp,m,1);
C = Listcol(temp,m,2);
*/

//Transpose
trans = transposeList(temp,m,n);

//printing
//printList(A);//print vertex C 
///printList(temp,1,3);
//printList(temp);
printList(trans);
//printVec(heads);
//fclose(fp);
    return 0;
}
