//Functions created by
// G V V Sharma
// October 29, 2023
// Revised October 31, 2023
// Revised November 1, 2023
// Revised November 21, 2023

//Function declaration
double Listnorm(avyuh *a);//norm of a vector
double Listdot(avyuh *a, avyuh * b);//inner product
double ListVecdot(sadish *a, sadish * b);//inner product
avyuh *Listsub(avyuh *a, avyuh *b);//subtract two matrices
avyuh *Listadd(avyuh *a, avyuh *b);//add two matrices
sadish *ListVecadd(sadish *a, sadish *b);//add two matrices
sadish *ListVecShift(sadish *a);//circulalry right shift vector
sadish *ListVecsub(sadish *a, sadish *b);//subtract two vectors
avyuh *Listscale(avyuh *a, double k);//scale matrix
sadish *Listvecscale(sadish *a, double k);//scale vector
avyuh *Listinv(avyuh *mat, int m);//invert an m  x m matrix, m <=3
avyuh *Listmul(avyuh *a, avyuh *b);//multiply matrices a and b
avyuh *rotList(double theta); //rotation matrix
avyuh *normVec(avyuh *a); //normal vector
avyuh *circulantList(avyuh *c);//circulant matrix
avyuh *Listsec(avyuh *a, avyuh * b,double k);//section formula
//End function declaration


//add two matrices
avyuh *Listadd(avyuh *a, avyuh *b){
	avyuh *c= (avyuh *)malloc(sizeof(avyuh)), *tempb = b, *head; 
	c->next = NULL;
	head = c;
	 for(avyuh *tempa=a;tempa!=NULL;tempa=tempa->next){
                c->vector = ListVecadd(tempa->vector,tempb->vector);
                tempb = tempb->next;
	if(tempa->next!=NULL){
		c->next = (avyuh *)malloc(sizeof(avyuh));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}
//Sum of vectors
sadish *ListVecadd(sadish *a, sadish *b){
	sadish *head = (sadish *)malloc(sizeof(sadish)), *c, *tempa=a, *tempb=b;
	c = head; 
	head->next = NULL;
	for(sadish *tempa=a;tempa!=NULL;tempa=tempa->next){
                c->data = tempa->data+tempb->data;
                //tempa = tempa->next;
                tempb = tempb->next;
	if(tempa->next!=NULL){
		c->next = (sadish *)malloc(sizeof(sadish));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}
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
	sadish *head = (sadish *)malloc(sizeof(sadish)), *c, *tempb=b;
	c = head; 
	head->next = NULL;
	for(sadish *tempa=a;tempa!=NULL;tempa=tempa->next){
		c->data = tempa->data-tempb->data;
		tempb = tempb->next;
	if(tempa->next!=NULL){
		c->next = (sadish *)malloc(sizeof(sadish));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}

//subtract two matrices
avyuh *Listsub(avyuh *a, avyuh *b){
	avyuh *c= (avyuh *)malloc(sizeof(avyuh)),  *tempb = b, *head; 
	c->next = NULL;
	head = c;
	for(avyuh *tempa=a;tempa!=NULL;tempa=tempa->next){
		c->vector = ListVecsub(tempa->vector,tempb->vector);
		tempb = tempb->next;
	if(tempa->next!=NULL){
		c->next = (avyuh *)malloc(sizeof(avyuh));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}

//norm of a vector
double Listnorm(avyuh *a){
	return sqrt(Listdot(a,a));
}

//rotation matrix
avyuh *rotList(double theta){ 
avyuh *head = createList(2,2), *temp;//create empty 2 x 2 matrix 
sadish *row1, *row2;
double c = cos(theta), s = sin(theta);

row1 = head->vector;
row2 = head->next->vector;
row1->data = c;
row1->next->data = -s;
row2->data = s;
row2->next->data = c;
return head;

}

//Matrix multiplication
avyuh *Listmul(avyuh *a, avyuh *b){
	avyuh *c=(avyuh *)malloc(sizeof(avyuh)),*atemp, *btemp;
	avyuh *head = c;
	sadish *cvec=(sadish *)malloc(sizeof(sadish));
	head->next = NULL;
	for(atemp=a; atemp !=NULL; atemp=atemp->next){
		cvec=(sadish *)malloc(sizeof(sadish));
		cvec->next = NULL;
		c->vector = cvec;  
		for(btemp=b; btemp !=NULL; btemp=btemp->next){
			cvec->data=ListVecdot(atemp->vector, btemp->vector);//inner product
		if(btemp->next!=NULL){
			cvec->next = (sadish *)malloc(sizeof(sadish));
			cvec->next->next=NULL;
			cvec= cvec->next;
		}
		}

		if(atemp->next!=NULL){
			c->next = (avyuh *)malloc(sizeof(avyuh));
			c->next->next=NULL;
			c= c->next;
		}
	}
return head;
}
//scale vector
sadish *Listvecscale(sadish *a, double k){
	sadish *head = (sadish *)malloc(sizeof(sadish)), *c;
	c = head; 
	head->next = NULL;
	for(sadish *tempa=a;tempa!=NULL;tempa=tempa->next){
		c->data = k*tempa->data;
	if(tempa->next!=NULL){
		c->next = (sadish *)malloc(sizeof(sadish));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}
//scale matrix
avyuh *Listscale(avyuh *a, double k){
	avyuh *head = (avyuh *)malloc(sizeof(avyuh)), *c;
	c = head; 
	head->next = NULL;
	for(avyuh *tempa=a;tempa!=NULL;tempa=tempa->next){
		c->vector = Listvecscale(a->vector, k);
	if(tempa->next!=NULL){
		c->next = (avyuh *)malloc(sizeof(avyuh));
		c->next->next=NULL;
		c= c->next;
	}
	}
	return head;
}
//section formula
avyuh *Listsec(avyuh *a, avyuh * b,double k){
	avyuh *head = (avyuh *)malloc(sizeof(avyuh)), *c;
	sadish *tempc =(sadish *)malloc(sizeof(sadish)), *tempb=b->vector;
	c = head; 
	head->next = NULL;
	tempc->next = NULL;
	c->vector = tempc;
	for(sadish *tempa=a->vector;tempa!=NULL;tempa=tempa->next){
		tempc->data= (k*tempb->data+tempa->data)/(k+1);
		tempb=tempb->next;
	if(tempa->next!=NULL){
		tempc->next = (sadish *)malloc(sizeof(sadish));
		tempc->next->next=NULL;
		tempc= tempc->next;
	}
	}
	return head;
}
//circulalry right shift vector
sadish *ListVecShift(sadish *a){
	sadish *tempa, *temp;
	sadish *head = ListVecopy(a);
	for(temp=head;temp->next->next!=NULL;temp=temp->next);
temp->next->next = head;
tempa = temp->next;
temp->next = NULL;
return tempa;
}
//circulant matrix
avyuh *circulantList(avyuh *a){
	avyuh *c=(avyuh *)malloc(sizeof(avyuh));
	avyuh *head = c;
	sadish *ctemp;
	ctemp=a->vector;
	head->vector=a->vector;
	for(sadish *temp=a->vector;temp->next!=NULL;temp=temp->next){
			c->next = (avyuh *)malloc(sizeof(avyuh));
			c->next->next=NULL;
			c= c->next;
		c->vector = ListVecShift(ctemp);
		ctemp=c->vector;
	}
	return head;
}
