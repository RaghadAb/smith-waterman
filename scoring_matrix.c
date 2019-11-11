#include "scoring_matrix.h"

#include <stdio.h>
#include <string.h>

// method to set the [i,j] location to the value passed
void setIJ(scoring_matrix *matrix, int i, int j, int value)
{
    matrix->data[i * matrix->width + j] = value;
}

// method to get [i,j] values
int getIJ(scoring_matrix *matrix, int i, int j)
{
    return matrix->data[i * matrix->width + j];
} //gets the member data from the struct matrix is pointing to

// method to calculate S(a,b)
int S(char a, char b, int match_score)
{
    return a == b ? match_score : -match_score;
}

// method to get the maximum of four values
int getMax(int a, int b, int c, int d)
{
    // the array to store 4 values
    int arr[4];
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    // get the maximum
    int maximum = arr[0];
    int i;
    for (i = 1; i < 4; i++)
    {
        if (arr[i] > maximum)
            maximum = arr[i];
    }

    // print max
    // printf("max : %d\n",maximum);

    // return the maximum
    return maximum;
}

scoring_matrix create_matrix(const char *a, const char *b, int match_score, int gap_cost)
{
    // the number of rows of the matrix is the length of the string a
    unsigned long num_rows = strlen(a) + 1;
    // the number of columns is the length of the string a plus b
    unsigned long num_cols = strlen(b) + 1;

    // the scoring matrix to be created
    scoring_matrix matrix;
    // set the values in the matrix
    matrix.height = num_rows;
    matrix.width = num_cols;

    // allocate memory to the data
    matrix.data = (int *)malloc(sizeof(int) * (num_cols * num_rows));

    int i, j;
    // set the first column to 0
    for (i = 0; i < num_rows; i++)
        setIJ(&matrix, i, 0, 0);

    // set the first row to 0
    for (j = 0; j < num_cols; j++)
        setIJ(&matrix, 0, j, 0);

    // fill the matrix row by row
    for (i = 1; i < num_rows; i++)
    {
        for (j = 1; j < num_cols; j++)
        {
            // fill the matrix

            // get the value of a
            int v1 = getIJ(&matrix, i - 1, j - 1) + S(a[i - 1], b[j - 1], match_score);
            int v2 = getIJ(&matrix, i - 1, j) - gap_cost;
            int v3 = getIJ(&matrix, i, j - 1) - gap_cost;
            int v4 = 0;

            // set the value in the matrix
            setIJ(&matrix, i, j, getMax(v1, v2, v3, v4));
        }
    }

    // fill matrix
    return matrix;
}

void free_matrix(scoring_matrix matrix)
{
    // free the matrix
    free(matrix.data);
}

scoring_matrix_view matrix_as_view(scoring_matrix matrix)
{
    scoring_matrix_view view;

    // set the matrix for the view
    view.matrix = matrix;
    view.height = matrix.height;
    view.width = matrix.width;

    // set view
    return view;
}

void print_matrix(scoring_matrix_view view)
{
    size_t i, j;
    // print the matrix
    for (i = 0; i < view.height; i++)
    {
        for (j = 0; j < view.width; j++)
        {
            // fill the matrix

            // get the value
            int v = view.matrix.data[i * view.width + j];
            // print this
            printf("%d ", v);
        }
        // change line
        printf("\n");
    }
}
