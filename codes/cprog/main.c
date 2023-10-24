//Code by G V V Sharma
//October 23, 2023
//matrix operations using lists
#include <stdio.h>
#include <stdlib.h>
#include "libs/matlist.h"

//matrix data structure
typedef struct tree
{
double data;
struct tree *row;
struct tree *col;
}vriksh;

//declare matrix function 
vriksh *matrix(char *str, int m, int n);

int  main()
{
FILE *fp; //file pointer
double val;//for reading file data
vriksh *head, *temp;//head of the array
int m =2, n=2, i, j;
/*
a  = array("B.dat", &n);
printMat(a,n);
*/

fp = fopen("B.dat", "r");//open file
head = (vriksh *)malloc(sizeof(vriksh));
temp = head;
//row loop
for (i = 0; i < m, i++)
{
	//column loop
	for (j = 0; j < m, j++)
	{
		fscanf(fp,"%lf",&temp->data);
		temp = temp->col;
		if (i == m)
		{
			temp  = NULL;
			break;
		}
		else
			temp= (vriksh *)malloc(sizeof(vriksh));
	if(i==0)
		temp  = head->row;
}
fclose(fp);
    return 0;
}

