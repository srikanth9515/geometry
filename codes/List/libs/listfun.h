//Functions created by
// G V V Sharma
// October 29, 2023

//Function declaration
double Listnorm(avyuh *a, int m);//norm of a vector
double Listdot(avyuh *a, avyuh * b);//inner product
double ListVecdot(sadish *a, sadish * b);//inner product
avyuh *Listsub(avyuh *a, avyuh *b);//subtract two matrices
avyuh *Listadd(avyuh *a, avyuh *b, int m, int n);//add two matrices
avyuh *Listscale(avyuh *a, int m, int n, double k);//scale matrix
avyuh *Listinv(avyuh *mat, int m);//invert an m  x m matrix, m <=3
avyuh *Listmul(avyuh *a, avyuh *b, int m, int n, int p);//multiply matrices a and b
avyuh *rotList(double theta); //rotation matrix
avyuh *normVec(avyuh *a); //normal vector
void circulantList(avyuh *c, int m);
avyuh *Listsec(avyuh *a, avyuh * b, int m, double k);//section formula
//End function declaration


//inner product
double ListVecdot(sadish *a, sadish *b){
	double val = 0;
	sadish *tempa=a, *tempb=b;
	while(tempa !=NULL){
		val += tempa->data*tempb->data;
		tempa = tempa->next;
		tempb = tempb->next;
	}
	return val;
}
double Listdot(avyuh *a, avyuh *b){
	return ListVecdot(a->vector, b->vector);
}
sadish *ListVecsub(sadish *a, sadish *b){
	sadish *head = (sadish *)malloc(sizeof(sadish)), *c, *tempa=a, *tempb=b;
	c = head; 
	head->next = NULL;
	while(tempa !=NULL){
		c->data = tempa->data-tempb->data;
		tempa = tempa->next;
		tempb = tempb->next;
	if(tempa!=NULL){
		c->next = (sadish *)malloc(sizeof(sadish));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}

//subtract two matrices
avyuh *Listsub(avyuh *a, avyuh *b){
	avyuh *c= (avyuh *)malloc(sizeof(avyuh)), *tempa = a, *tempb = b, *head; 
	c->next = NULL;
	head = c;
	while(tempa !=NULL){
		c->vector = ListVecsub(tempa->vector,tempb->vector);
		tempa = tempa->next;
		tempb = tempb->next;
	if(tempa!=NULL){
		c->next = (avyuh *)malloc(sizeof(avyuh));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}

