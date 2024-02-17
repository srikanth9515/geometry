
//Function declaration
void freeMat(double **matrix, int rows);

double **combineMat(double **a,double **b,int m,int n);//adds the matrix A and matrix B
//End Function declaration

void freeMat(double **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

double **combineMat(double **a,double **b,int m,int n)
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




