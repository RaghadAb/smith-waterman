#include "Smith-Waterman.h"

#include "scoring_matrix.h"
#include "traceback.h"

#include <stdio.h>
#include <string.h>

void print_smith_waterman(const char *a, const char *b)
{
    fprintf(stderr, "print_smith_waterman(\"%s\", \"%s\")\n", a, b);
    int match_score = 3;
    int gap_cost = 2;
    // create_matrix
    scoring_matrix matrix = create_matrix(a, b, match_score, gap_cost);
    // get view
    scoring_matrix_view view = matrix_as_view(matrix);
    // print_matrix(view);
    // traceback
    traceback_result *result = traceback(view, a, b);
    // print A from traceback result
    // print B from traceback result
    printf("%s\n", result->a_);
    printf("%s\n", result->b_);

    // free
    // free_matrix(matrix);
    // freeResult(result);
}
