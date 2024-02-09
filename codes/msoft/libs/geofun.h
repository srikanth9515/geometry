//Functions created by
// G V V Sharma
// October 27, 2023
// Revised November 13, 2023

//Function declaration

double **createMat(int m,int n);//create m x n matrix array
double **Matmul(double **a, double **b, int m, int n, int p);//multiply matrices a and b
double **transposeMat(double **a,  int m, int n);//transpose of a
double **rotMat(double theta); //rotation matrix
void midpoint(double x1, double y1, double x2, double y2, double *midpoint_x, double *midpoint_y);
double calculateSlope(double x1, double y1, double x2, double y2);
void calculatePerpendicularBisector(double x1, double y1, double x2, double y2, double *slope, double *midpoint_x, double *midpoint_y);
double distance(int x1, int y1, int x2, int y2);
double calculateAngle(double a, double b, double c);
double mid_point(int x1, int x2);
double calculateMedian(double *a, double *b, double *c);
double sqrtApprox(double x);
void freeMat(double **matrix, int rows);
double **tri_sides(double **A, double **B, double **C, double **sides);
double **calculate(double **A, double **B, double **C, double **sides);
double **dir_vec(double **A,double **B,int m,int n);
double **line_intersect(double **m3,double **B,double **m1,double **C, int m,int n);
double **solve(double **p,double **N);
double **block(double **a,double **b,int m,int n);




//End function declaration


//Defining the function for matrix creation
double **createMat(int m,int n)
{
 int i;
 double **a;
 
 //Allocate memory to the pointer
a = (double **)malloc(m * sizeof( *a));
    for (i=0; i<m; i++)
         a[i] = (double *)malloc(n * sizeof( *a[i]));

 return a;
}
//End function for matrix creation


//Rotation matrix

double **rotMat(double theta){
double **temp=createMat(2,2);//creating the matrix
double c = cos(theta), s = sin(theta);
temp[0][0] = c;
temp[0][1] = -s;
temp[1][0] = s;
temp[1][1] = c;

return temp;
}

//Defining the function for product of matrices

double **Matmul(double **a, double **b, int m, int n, int p)
{
int i, j, k;
double **c, temp =0;
c = createMat(m,p);

 for(i=0;i<m;i++)
 {
  for(k=0;k<p;k++)
  {
    for(j=0;j<n;j++)
    {
	temp= temp+a[i][j]*b[j][k];
    }
	c[i][k]=temp;
	temp = 0;
  }
 }
return c;

}
//End function for difference of matrices

//Defining the function for transpose of matrix

double **transposeMat(double **a,  int m, int n)
{
int i, j;
double **c;
//printf("I am here");
c = createMat(n,m);

 for(i=0;i<n;i++)
 {
  for(j=0;j<m;j++)
  {
c[i][j]= a[j][i];
//  printf("%lf ",c[i][j]);
  }
 }
return c;

}
//End function for transpose of matrix

//function to calculate Mid points
void midpoint(double x1, double y1, double x2, double y2, double *midpoint_x, double *midpoint_y) {
    *midpoint_x = (x1 + x2) / 2.0;
    *midpoint_y = (y1 + y2) / 2.0;
}

// Function to calculate the slope of a line
double calculateSlope(double x1, double y1, double x2, double y2) {
    return (y2 - y1) / (x2 - x1);
}

// Function to calculate the perpendicular bisector of a side
void calculatePerpendicularBisector(double x1, double y1, double x2, double y2, double *slope, double *midpoint_x, double *midpoint_y) {
    *slope = -1 / calculateSlope(x1, y1, x2, y2);
    midpoint(x1, y1, x2, y2, midpoint_x, midpoint_y);
}

// Function to find distance between two vertices
double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

//Function to find angle between sides of a triangle
double calculateAngle(double a, double b, double c) {
    return acos((b * b + c * c - a * a) / (2 * b * c));
}
//Function to find midpoints of a triangle
double mid_point(int x1, int x2){
return (x1 + x2)/2;
}
// Function to calculate the median using custom square root approximation
double calculateMedian(double *a, double *b, double *c) {
    double median;
// Calculate the median using the formula: sqrt(2*b^2 + 2*c^2 - a^2) / 2
    median = sqrtApprox(2 * (*b) * (*b) + 2 * (*c) * (*c) - (*a) * (*a)) / 2.0;
    return median;
}

// Function to find square root using Newton's method
double sqrtApprox(double x) {
    double result = x;

    // Use Newton's method for better approximation
    for (int i = 0; i < 10; ++i) {
        result = 0.5 * (result + x / result);
    }

    return result;
}

void freeMat(double **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

double **tri_sides(double **A, double **B, double **C, double **sides)
{
    sides[0][0] = hypot(B[0][0] - C[0][0], B[1][0] - C[1][0]);
    sides[1][0] = hypot(C[0][0] - A[0][0], C[1][0] - A[1][0]);
    sides[2][0] = hypot(A[0][0] - B[0][0], A[1][0] - B[1][0]);
    return sides;
}

double **calculate(double **A, double **B, double **C, double **sides)
{
    double a, b, c, m_val, n_val, p_val,**sol;
    a = sides[2][0];
    b = sides[0][0];
    c = sides[1][0];
    p_val = (a + c - b) / 2;
    m_val = (a + b - c) / 2;
    n_val = (b + c - a) / 2;
    sol = createMat(2,2);
    sol[0][0] = (m_val * A[0][0] + p_val * B[0][0]) / (m_val + p_val);
    sol[0][1] = (p_val * C[0][0] + n_val * A[0][0]) / (p_val + n_val);
    sol[1][0] = (m_val * A[1][0] + p_val * B[1][0]) / (m_val + p_val);
    sol[1][1] = (p_val * C[1][0] + n_val * A[1][0]) / (p_val + n_val);
    return sol;
}

double **dir_vec(double **A,double **B,int m,int n)
{
    int i, j;
    double **c;
    c = createMat(m,n);

    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
    c[i][j]= B[i][j]-A[i][j];
    }
    }
    return c;
}

double **line_intersect(double **m3,double **B,double **m1,double **C, int m,int n)
{
    double **N,**m3_t,**m1_t,**p0,**p1,**p,**P1,**P2,**solution;
    p=createMat(2,1);
    N=transposeMat(block(m3,m1,m,n),m,m);
    m3_t=transposeMat(m3,m,n);
    m1_t=transposeMat(m1,m,n);
    p0=Matmul(m3_t,B,n,m,n);
    p1=Matmul(m1_t,C,n,m,n);
    p[0][0]=p0[0][0];
    p[1][0]=p1[0][0];
    solution=solve(p,N);
    return(solution);
}

double **solve(double **p,double **N)
{
    double **sol;
    sol=createMat(2,1);
    sol[1][0]=(p[0][0]*N[1][0]-N[0][0]*p[1][0])/(N[0][1]*N[1][0]-N[0][0]*N[1][1]);
    sol[0][0]=(p[0][0]*N[1][1]-N[0][1]*p[1][0])/(N[0][0]*N[1][1]-N[0][1]*N[1][0]);
    return sol;

}

double **block(double **a,double **b,int m,int n)
{
    double **l;
    int i,j,k=0;

    l=createMat(m,m);
    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
        l[i][k]=a[i][j];
    }
    }
    k+=1;
        
    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
    l[i][k]=b[i][j];
    }
    }
    k+=1;


    return l;
}
