#include <stdio.h>
#include <stdlib.h>
//#include "libs/matlist.h"


typedef struct list
{
double data;
struct list *next;
}node;
node *array(char *str, int *n);
void printMat(node *head,int n);

int  main()
{
	node *a;
//	node *head,*temp;
//FILE *fp; //file pointer
	int n=0;
//fp = fopen("A.dat", "r");//open file
//head = (node *)malloc(sizeof(node));
//temp = head;
//while(fscanf(fp,"%lf",temp->data) != EOF)
//fscanf(fp,"%lf",&temp->data); 
//fclose(fp);
//printf("%lf\n",temp->data);
//printf("%d\n",n);
a  = array("A.dat", &n);
//printf("%d\n",n);
printMat(a,n);
    return 0;
}

node *array(char *str, int *n)
{

FILE *fp; //file pointer
double val;//for reading file data
node *head, *temp;//head of the array

fp = fopen(str, "r");//open file
*n=0;
head = (node *)malloc(sizeof(node));
temp = head;

while(fscanf(fp,"%lf",&temp->data) != EOF)
{
temp->next=(node *)malloc(sizeof(node));
temp  = temp->next;
++*n;
}

fclose(fp);
 return head;

}
//End function for reading matrix from file
//Function for printing an array
void printMat(node *head,int n)
{
	node *temp=head;
	while (n !=0)
	{
		printf("%lf\n",temp->data);
		temp= temp->next;
		--n;
	}
}
//End function for printing array
