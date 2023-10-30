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
sadish *loadVec(FILE *fp, int n);
avyuh *createList(int m,int n);//create m x n matrix array
void printList(avyuh *p);//print matrix
avyuh *loadList(char *str,int m,int n);//load matrix from file
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
avyuh *Listcol(avyuh *a, int n){
	int i = 0,j = 0;//dummy integers
	int m = 2;
	avyuh *head= (avyuh *)malloc(sizeof(avyuh)), *alist=a;
	sadish *btemp=(sadish *)malloc(sizeof(sadish)),*temp;
	head->vector= btemp;
	btemp->next= NULL;
	head->next= NULL;
	while(alist != NULL){
		temp = Vecind(alist->vector,n);//getting address of the nth column
		btemp->data = temp->data;
		alist= alist->next;
	if(alist!=NULL){
		btemp->next = (sadish *)malloc(sizeof(sadish));
		btemp->next->next=NULL;
		btemp= btemp->next;
	}
	}
return head;
}
//load matrix from file

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
head->next = NULL;
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
	for (sadish *temp=head; temp !=NULL; temp= temp->next){
		printf("%lf ",temp->data);
	}
}

void printList(avyuh *head)
{
	for (avyuh *temp=head; temp !=NULL; temp= temp->next){
		printVec(temp->vector);
	printf("\n");
    }
}
