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
sadish *Vecind(sadish *a,int n);
void printVec(sadish *head);
//void printVec(sadish *head,int n);
sadish *loadVec(FILE *fp, int n);
avyuh *createList(int m,int n);//create m x n matrix array
void printList(avyuh *p);//print matrix
//void printList(avyuh *p,int m,int n);//print matrix
avyuh *loadList(char *str,int m,int n);//load matrix from file
//avyuh *Listcol(avyuh *a,int m, int n);//extract nth column of matrix
avyuh *Listcol(avyuh *a, int n);//extract nth column of matrix
avyuh *transposeList(avyuh *a,  int m, int n);//transpose of a
//End function declaration

//Matrix transpose 
avyuh *transposeList(avyuh *a,  int m, int n){
	int i;//dummy integer
	avyuh *b = createList(n,1);//create empty n x m matrix 
	avyuh *head = b, *alist=a, *blist=b, *temp;

//extract column vector
	for (i = 0; i < n; i++){
		temp = Listcol(a,i);
		//temp = Listcol(a,m,i);
		blist->vector = temp->vector;
		blist= blist->next;
	}
return head;

}

//create vector
sadish *createVec( int n)
{

int i =0;//dummy integer
sadish *head,*temp;//head of the array
head = (sadish *)malloc(sizeof(sadish));
head->next = NULL;
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
a->next = NULL;
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

//Extract column from matrix
//avyuh *Listcol(avyuh *a,int m, int n){
avyuh *Listcol(avyuh *a, int n){
	int i = 0,j = 0;//dummy integers
	int m = 2;
	avyuh *b = createList(1,m);//create empty column vector of length m 
	avyuh *head= b, *alist=a;
	sadish *temp,*btemp=head->vector ;
//printList(a);
//extract column vector
	for (i = 0; i < m; i++){
//	while(alist != NULL){
		temp = Vecind(alist->vector,n);//getting address of the nth column
//		printf("%lf %d\n",temp->data, i);
		btemp->data = temp->data;
		//printf("%lf %d\n",btemp->data, i);
		alist= alist->next;
		btemp= btemp->next;
		//i++;
	}
//	printf("I am here");
return head;
}
//
/*
//avyuh *Listcol(avyuh *a,int m, int n){
avyuh *Listcol(avyuh *a, int n){
	int i = 0,j = 0;//dummy integers
	int m = 2;
//	avyuh *b = createList(1,m);//create empty column vector of length m 
	avyuh *head= (avyuh *)malloc(sizeof(avyuh)), *alist=a;
	sadish *temp,*btemp;
head->next = NULL;
head->vector = createVec(n);
btemp=head->vector;
//printList(a);
//extract column vector
	for (i = 0; i < m; i++){
//	while(alist != NULL){
		temp = Vecind(alist->vector,n);//getting address of the nth column
		printf("%lf %d\n",temp->data, i);
		btemp->data = temp->data;
		//printf("%lf %d\n",btemp->data, i);
		alist= alist->next;
		btemp= btemp->next;
		//i++;
	}
	printf("I am here");
return head;
}
//load matrix from file

*/
avyuh *loadList(char *str, int m, int n){
	avyuh *head, *temp;//matrix head
	int i=0;//dummy integer
	FILE *fp;
fp = fopen(str, "r");//open file
head = (avyuh *)malloc(sizeof(avyuh));
head->next = NULL;
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
void printVec(sadish *head)
{
	sadish *temp=head;
	while(temp !=NULL){
		printf("%lf ",temp->data);
		temp= temp->next;
	}
}
/*
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
		printf("%lf ",temp->data);
		temp= temp->next;
		--n;
	}
}
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
		printVec(temp->vector);
		//printVec(temp->vector,n);
		printf("\n");
	temp= temp->next;
    }
}
*/

void printList(avyuh *head)
{
	avyuh *temp=head;
	while(temp !=NULL){
		printVec(temp->vector);
		//printVec(temp->vector,n);
		printf("\n");
	temp= temp->next;
    }
}
