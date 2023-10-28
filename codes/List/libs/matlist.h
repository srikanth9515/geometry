//Functions created by
// G V V Sharma
// October 27, 2023

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

//Function declaration
//vriksh *loadList(char *str, int m, int n);
node *array(char *str, int *n);
//void printList(vriksh *head,int m, int n);
void printVec(node *head,int n);
node *loadVec(FILE *fp, int n);
vriksh *createList(int m,int n);//create m x n matrix array
void readList(vriksh *p, int m,int n);//read matrix into array
void printList(vriksh *p,int m,int n);//print matrix
vriksh *loadList(char *str,int m,int n);//load matrix from file
double Listnorm(vriksh *a, int m);//norm of a vector
double Listdot(vriksh *a, vriksh * b, int m);//inner product
vriksh *Listsub(vriksh *a, vriksh *b, int m, int n);//subtract two matrices
vriksh *Listadd(vriksh *a, vriksh *b, int m, int n);//add two matrices
vriksh *Listscale(vriksh *a, int m, int n, double k);//scale matrix
vriksh *Listinv(vriksh *mat, int m);//invert an m  x m matrix, m <=3
vriksh *Listmul(vriksh *a, vriksh *b, int m, int n, int p);//multiply matrices a and b
vriksh *transposeList(vriksh *a,  int m, int n);//transpose of a
vriksh *rotList(double theta); //rotation matrix
vriksh *normVec(vriksh *a); //normal vector
void circulantList(vriksh *c, int m);
vriksh *Listsec(vriksh *a, vriksh * b, int m, double k);//section formula
//End function declaration

 
//load matrix

vriksh *loadList(char *str, int m, int n){
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
void printList(vriksh *head,int m, int n)
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

