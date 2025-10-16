#include "HumanPyramids.h"
#include "error.h"
#include "grid.h"

using namespace std;

double weightOnBackOfRec(int row, int col, Grid<double> &memo);

double weightOnBackOf(int row, int col, int pyramidHeight) {

    if (row < 0 || col < 0
        || row > pyramidHeight - 1 || col > pyramidHeight - 1
        || col > row) {
        error("coordinate is out of bounds!");
    }

    Grid<double> memo(pyramidHeight, pyramidHeight, -1.0);
    return weightOnBackOfRec(row, col, memo);

}


double weightOnBackOfRec(int row, int col, Grid<double> &memo) {
    if (memo[row][col] != -1.0) {
        return memo[row][col];
    }

    if (row == 0) {
        memo[row][col] = 0.0;
        return 0.0;
    }

    double result;
    if (col == 0) {
        result = 80.0 + weightOnBackOfRec(row - 1, col, memo) / 2;
    }
    else if (col == row) {
        result = 80.0 + weightOnBackOfRec(row - 1, col - 1, memo) / 2;
    }
    else {
        result = 160.0 + weightOnBackOfRec(row - 1, col - 1, memo) / 2
                + weightOnBackOfRec(row - 1, col, memo) / 2;
    }

    memo[row][col] = result;
    return result;
}




/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

STUDENT_TEST("Test top of pyramid (row 0, col 0)") {
    EXPECT_EQUAL(weightOnBackOf(0, 0, 1), 0);
    EXPECT_EQUAL(weightOnBackOf(0, 0, 10), 0);
}

STUDENT_TEST("Test second row (row 1)") {
    EXPECT_EQUAL(weightOnBackOf(1, 0, 2), 80);
    EXPECT_EQUAL(weightOnBackOf(1, 1, 2), 80);
}

STUDENT_TEST("Test a person in the middle of a row") {
    // This is Person E from the handout, already a provided test, but good for confirmation.
    EXPECT_EQUAL(weightOnBackOf(2, 1, 3), 240);
}

STUDENT_TEST("Test people on the edges of the pyramid") {
    // Left edge, person at (2,0)
    EXPECT_EQUAL(weightOnBackOf(2, 0, 3), 120);
    // Right edge, person at (2,2)
    EXPECT_EQUAL(weightOnBackOf(2, 2, 3), 120);
    // Left edge, person at (3,0)
    EXPECT_EQUAL(weightOnBackOf(3, 0, 4), 140);
    // Right edge, person at (3,3)
    EXPECT_EQUAL(weightOnBackOf(3, 3, 4), 140);
}

STUDENT_TEST("Test a slightly larger pyramid") {
    EXPECT_EQUAL(weightOnBackOf(3, 1, 4), 340);
    EXPECT_EQUAL(weightOnBackOf(3, 2, 4), 340);
}

STUDENT_TEST("Test more invalid cases") {
    // Negative column
    EXPECT_ERROR(weightOnBackOf(2, -1, 5));
    // Column greater than row
    EXPECT_ERROR(weightOnBackOf(2, 3, 5));
    // Zero or negative pyramid height
    EXPECT_ERROR(weightOnBackOf(0, 0, 0));
    EXPECT_ERROR(weightOnBackOf(0, 0, -5));
}

STUDENT_TEST("Test with minimum valid pyramid height (height 1)") {
    EXPECT_EQUAL(weightOnBackOf(0, 0, 1), 0);
    // Any other person is out of bounds
    EXPECT_ERROR(weightOnBackOf(1, 0, 1));
    EXPECT_ERROR(weightOnBackOf(1, 1, 1));
}


/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
