//Code by G V V Sharma
//October 23, 2023
//Revised October 28, 2023
//matrix operations using lists
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/listgen.h"
#include "libs/listfun.h"


int  main()
{
FILE *fp; //file pointer
double val;//for reading file data
avyuh *trans, *temp;//head of the array
avyuh *prod;
avyuh *mat;//head of the array
//sadish *a,*heads;
avyuh *A,*B,*C;//triangle vertices
avyuh *D,*E,*F;//triangle mid points
avyuh *m1,*m2,*m3;//direction vectors of the sides
avyuh *n1,*n2,*n3;//direction vectors of the sides
double a, b, c;//sides
int m =2, n=3, i, j;
//fp = fopen("A.dat","r");
//heads = loadVec(fp,3);
//head = loadList("A.dat", 3, 1);
//a = Vecind(heads,0);
//printf("%lf\n",a->data);
//printList(head,3,1);

//load matrix from file
temp= loadList("vertices.dat", m, n);
//temp= loadList("A.dat", 1, 3);

//Triangle vertices
A = Listcol(temp,0);
B = Listcol(temp,1);
C = Listcol(temp,2);

//Mid points
//F= Listadd(A, B);
F = Listsec(A,B,1);
D= Listsec(B, C,1);
E= Listsec(C, A,1);

//Direction vectors
m1 = Listsub(A, B);
m2 = Listsub(B, C);
m3 = Listsub(C, A);

//Triangle sides;
c = Listnorm(m1);
a = Listnorm(m2);
b = Listnorm(m3);


//Rotation matrix
mat = rotList(M_PI/2);

//Normal vectors
n1 = Listmul(mat,m1);
n2 = Listmul(mat,m2);
n3 = Listmul(mat,m3);

//Transpose
trans = transposeList(temp);

//Product
//prod = Listmul(temp,temp);

//printing
//printList(prod);
/*
printList(m1);
printList(m2);
printList(m3);
printList(n1);
printList(n2);
printList(n3);
//printList(temp);
//printList(trans);
//printList(Listmul(trans,temp));
//printf("I am here");
//printList(Listmul(temp, temp));
//printList(Listmul(trans, trans));
printf("%lf\n",c);
printf("%lf\n",a);
printf("%lf\n",b);
printList(temp);
//printList(mat);

printList(m1);
printList(m2);
printList(m3);
//printf("I am here");
//printList(A);

///printList(temp,1,3);
//printVec(heads);
//fclose(fp);
printList(A);//print vertex C 
printList(B);//print vertex C 
printList(C);//print vertex C 
printList(D);//print vertex C 
printList(E);//print vertex C 
printList(F);//print vertex C 
//printList(Listquad(1,-1,-2));
*/
printList(D);//print vertex C 
printList(B);//print vertex C 
printList(C);//print vertex C 
    return 0;
}
