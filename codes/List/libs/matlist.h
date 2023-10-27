//vector data structure
typedef struct list
{
double data;
struct list *next;
}node;

//matrix data structure
typedef struct tree
{	
node *sadish;
struct tree *next;
}vriksh;

//function declarations
vriksh *loadMat(char *str, int m, int n);
node *array(char *str, int *n);
void printMat(vriksh *head,int m, int n);
void printVec(node *head,int n);
node *loadVec(FILE *fp, int n);
 
//load matrix

vriksh *loadMat(char *str, int m, int n){
	vriksh *head, *temp;//matrix head
	int i=0;//dummy integer
	FILE *fp;
fp = fopen(str, "r");//open file
head = (vriksh *)malloc(sizeof(vriksh));
temp  = head;
for (i = 0; i < m; i++)
{
	temp->sadish = loadVec(fp, n);
	if (i< m-1){
	temp->next = (vriksh *)malloc(sizeof(vriksh));
	temp->next->next = NULL; 
	temp = temp->next; 
	}
}
fclose(fp);
return head;
}

//read row vector
node *loadVec(FILE *fp, int n)
{

int i =0;//dummy integer
double val;//for reading file data
node *head,*temp;//head of the array
head = (node *)malloc(sizeof(node));
temp  = head;
for (i=0; i < n; i++)
{
fscanf(fp,"%lf",&temp->data);
	if (i< n-1){
temp->next = (node *)malloc(sizeof(node));
temp->next->next= NULL;
temp  = temp->next;
	}
}

 return head;

}
//Function for printing an array
void printVec(node *head,int n)
{
	node *temp=head;
    if(temp==NULL)
    {
	printf("NULL encountered ");
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

//Function for printing a matrix
void printMat(vriksh *head,int m, int n)
{
	vriksh *temp=head;
	int i = 0;
    if(temp==NULL)
    {
    return;
    }
    for (i = 0; i < m; i++){
		printVec(temp->sadish,n);
	temp= temp->next;
    }
}
//End function for printing a matrix

