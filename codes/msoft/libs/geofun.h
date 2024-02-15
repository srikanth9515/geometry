//Function declaration
void freeMat(double **matrix, int rows);
//End Function declaration

void freeMat(double **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

