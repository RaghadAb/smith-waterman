#include "traceback.h"

#include <string.h>
#include <stdio.h>

// method to get view data
//int getViewDataIJ(scoring_matrix_view * view, int i, int j)
//{
//    return
//}

// method to find the index of the maximum value
void findMaxValueIndex(scoring_matrix_view *view, int *indexI, int *indexJ)
{
    int i, j;
    // the maximum value
    int maximum = 0;
    // set the coordinates of the maximum value to the top left corner
    *indexI = 0;
    *indexJ = 0;

    // print the matrix
    for (i = 0; i < view->height; i++)
    {
        for (j = 0; j < view->width; j++)
        {
            // if this value is greater than the maximum
            if (view->matrix.data[i * view->matrix.width + j] > maximum)
            {
                // update the maximum
                maximum = view->matrix.data[i * view->matrix.width + j];
                *indexI = i;
                *indexJ = j;
            }
            // value
            // printf("value : %d\n",view->matrix.data[ i*view->width + j]);
        }
    }
    // printf("max : %d\n",maximum);
    // printf("width : %ld\n",view->width);
    // printf("height : %ld\n",view->height);
}

// computes the traceback throught the scoring matrix
// it returns the substring of a and the aligned and
// modified string of b
//
// The pseudo code (in a Python-like syntax)
// for this function looks like:
//
// def traceback(view, a, b, b_='', old_i=0):
//     i, j = find_last_index_of_max_value(view)
//
//     if (view[i][j] == 0):
//         a_ = a[j:j+len(b_)]
//         return a_, b_
//     if (old_i - i > 1):
//         b_ = b[j - 1] + b_
//     else:
//         b_ = b[j - 1] + '-' + b_
//     return traceback(view[0:i][0:j], a, b, b_, i)

traceback_result *traceback_helper(scoring_matrix_view view, const char *a, const char *b, char *b_, int oldI)
{
    int maxI = 0;
    int maxJ = 0;
    findMaxValueIndex(&view, &maxI, &maxJ);

    if (view.matrix.data[maxI * view.matrix.width + maxJ] == 0)
    {
        // create a result
        traceback_result *result = (traceback_result *)malloc(sizeof(traceback_result));
        // give memory to a and b
        result->a_ = (char *)malloc(sizeof(char) * (strlen(a) + 2));
        result->b_ = (char *)malloc(sizeof(char) * (strlen(b_) + 2));

        // copy b_
        strcpy(result->b_, b_);

        // the index
        int index = 0;
        // set a
        int j;
        for (j = maxJ; j < maxJ + strlen(result->b_); j++)
            result->a_[index++] = a[j];
        result->a_[index] = '\0';
        return result;
    }

    if (oldI - maxI > 1)
    {
        // shift all the characters of b to right by one place
        int len = (int)strlen(b_);
        int i;
        for (i = len; i > 0; i--)
            b_[i] = b_[i - 1];

        // add b[j-1] to the start of the string
        b_[0] = b[maxJ - 1];
        b_[len + 1] = '\0';
    }
    else
    {
        int len = (int)strlen(b_);
        int i;
        for (i = len; i > 0; i--)
            b_[i] = b_[i - 1];
        // add '-' to the start of the string
        b_[0] = '-';
        // append null terminating character
        b_[len + 1] = '\0';

        // append
        len = (int)strlen(b_);
        for (i = len; i > 0; i--)
            b_[i] = b_[i - 1];
        b_[0] = b[maxJ - 1];
        b_[len + 1] = '\0';
    }

    // change the width of the view
    view.width = maxJ;
    view.height = maxI;
    return traceback_helper(view, a, b, b_, maxI);
}

traceback_result *traceback(scoring_matrix_view view, const char *a, const char *b)
{
    // give memory to a_ and b_
    char *b_ = (char *)malloc(sizeof(char) * (strlen(b) + 4));
    // set b to blank
    b_[0] = '\0';
    return traceback_helper(view, a, b, b_, 0);
}

void freeResult(traceback_result *result)
{
    if (result)
    {
        free(result->a_);
        free(result->b_);
        free(result);
    }
}
