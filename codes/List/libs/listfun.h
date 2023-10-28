//Functions created by
// G V V Sharma
// October 27, 2023

//vector data structure
typedef struct list
{
double data;
struct list *next;
}sadish;

//matrix data structure
typedef struct tree
{	
sadish *vector;
struct tree *next;
}avyuh;

//Function declaration
//avyuh *loadList(char *str, int m, int n);
sadish *array(char *str, int *n);
//void printList(avyuh *head,int m, int n);
void printVec(sadish *head,int n);
sadish *loadVec(FILE *fp, int n);
avyuh *createList(int m,int n);//create m x n matrix array
void readList(avyuh *p, int m,int n);//read matrix into array
void printList(avyuh *p,int m,int n);//print matrix
avyuh *loadList(char *str,int m,int n);//load matrix from file
double Listnorm(avyuh *a, int m);//norm of a vector
double Listdot(avyuh *a, avyuh * b, int m);//inner product
avyuh *Listsub(avyuh *a, avyuh *b, int m, int n);//subtract two matrices
avyuh *Listadd(avyuh *a, avyuh *b, int m, int n);//add two matrices
avyuh *Listscale(avyuh *a, int m, int n, double k);//scale matrix
avyuh *Listinv(avyuh *mat, int m);//invert an m  x m matrix, m <=3
avyuh *Listmul(avyuh *a, avyuh *b, int m, int n, int p);//multiply matrices a and b
avyuh *transposeList(avyuh *a,  int m, int n);//transpose of a
avyuh *rotList(double theta); //rotation matrix
avyuh *normVec(avyuh *a); //normal vector
void circulantList(avyuh *c, int m);
avyuh *Listsec(avyuh *a, avyuh * b, int m, double k);//section formula
//End function declaration

//create vector
sadish *createVec( int n)
{

int i =0;//dummy integer
sadish *head,*temp;//head of the array
head = (sadish *)malloc(sizeof(sadish));
temp  = head;
for (i=0; i < n; i++)
{
	if (i< n-1){
temp->next = (sadish *)malloc(sizeof(sadish));
temp->next->next= NULL;
temp  = temp->next;
	}
}

 return head;

}

//create matrix
avyuh *createList(int m,int n)
{
	avyuh *a, *temp;//matrix head
	int i=0;//dummy integer
a = (avyuh *)malloc(sizeof(avyuh));
temp  = a;
for (i = 0; i < m; i++)
{
	temp->vector = createVec(n);
	if (i< m-1){
	temp->next = (avyuh *)malloc(sizeof(avyuh));
	temp->next->next = NULL; 
	temp = temp->next; 
	}
}
 
 return a;
}

//Extract address from vector
sadish *Vecind(sadish *a,int n){
	sadish *temp=a;
	int i=0;//dummy integer
	for (i=0; i < n; i++){
		temp = temp->next;
	}
	return temp;
}
/*
//Extract column from matrix
//
avyuh *Listcol(avyuh *a,int m, int n){
	int i = 0,j = 0;//dummy integers
	avyuh *b = createList(1,m);//create empty vector of length m 
	avyuh *head = b;
	sadish *temp=b->vector,*subs;

//extract column vector
	for (i = 0; i < m; i++){
		subs = a->vector;
		for (j = 0; j < n-1; i++){
			temp->data = a->vector->data;
		b->vector = b->vector->next;
		a->vector = a->vector->next;
	}
return head;
}
*/
//load matrix from file

avyuh *loadList(char *str, int m, int n){
	avyuh *head, *temp;//matrix head
	int i=0;//dummy integer
	FILE *fp;
fp = fopen(str, "r");//open file
head = (avyuh *)malloc(sizeof(avyuh));
temp  = head;
for (i = 0; i < m; i++)
{
	temp->vector = loadVec(fp, n);
	if (i< m-1){
	temp->next = (avyuh *)malloc(sizeof(avyuh));
	temp->next->next = NULL; 
	temp = temp->next; 
	}
}
fclose(fp);
return head;
}

//load vector from file
sadish *loadVec(FILE *fp, int n)
{

int i =0;//dummy integer
double val;//for reading file data
sadish *head,*temp;//head of the array
head = (sadish *)malloc(sizeof(sadish));
temp  = head;
for (i=0; i < n; i++)
{
fscanf(fp,"%lf",&temp->data);
	if (i< n-1){
temp->next = (sadish *)malloc(sizeof(sadish));
temp->next->next= NULL;
temp  = temp->next;
	}
}

 return head;

}
//Function for printing an array
void printVec(sadish *head,int n)
{
	sadish *temp=head;
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
void printList(avyuh *head,int m, int n)
{
	avyuh *temp=head;
	int i = 0;
    if(temp==NULL)
    {
    return;
    }
    for (i = 0; i < m; i++){
		printVec(temp->vector,n);
	temp= temp->next;
    }
}
//End function for printing a matrix

