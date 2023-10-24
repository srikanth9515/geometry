typedef struct list
{
double data;
struct list *next;
}node;
node *array(char *str, int *n);
void printMat(node *head,int n);
 
//read matrix from file
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
    if(temp==NULL)
    {
    return;
    }
	while (n !=0)
	{
		printf("%lf\n",temp->data);
		temp= temp->next;
		--n;
	}
}
//End function for printing array
