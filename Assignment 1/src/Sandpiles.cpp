/* File: Sandpiles.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
using namespace std;

void dropSandOn(Grid<int>& world, int row, int col) {
    /* TODO: Delete this line and the three after it, then implement this function. */
    if (!world.inBounds(row, col)) {
        return;
    }

    world[row][col]++;

    if (world[row][col] >= 4) {
        world[row][col] -= 4;

        dropSandOn(world, row - 1, col);
        dropSandOn(world, row + 1, col);
        dropSandOn(world, row , col - 1);
        dropSandOn(world, row, col + 1);
    }

    return;
}






/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

STUDENT_TEST("Topple on a corner.") {
    // 沙子在角落 (0,0) 坍塌，只会影响两个邻居。
    Grid<int> before = {
        { 3, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 1, 0, 0 },
        { 0, 0, 0 }
    };

    dropSandOn(before, 0, 0);
    EXPECT_EQUAL(before, after);
}

STUDENT_TEST("Topple on an edge (not a corner).") {
    // 沙子在边缘 (1,0) 坍塌，只会影响三个邻居。
    Grid<int> before = {
        { 0, 0, 0 },
        { 3, 0, 0 },
        { 0, 0, 0 }
    };
    Grid<int> after = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 1, 0, 0 }
    };

    dropSandOn(before, 1, 0);
    EXPECT_EQUAL(before, after);
}

STUDENT_TEST("Topple in a 1x1 grid.") {
    // 在 1x1 的网格里，沙子无处可去。
    Grid<int> before = { {3} };
    Grid<int> after = { {0} };

    dropSandOn(before, 0, 0);
    EXPECT_EQUAL(before, after);
}

STUDENT_TEST("Chain reaction in a 1x5 grid (long and thin).") {
    Grid<int> before = {
        { 3, 3, 3, 0, 0 }
    };
    // 滴在 (0,0) -> {4,3,3,0,0} -> {0,4,3,0,0} -> {1,0,4,0,0} -> {1,1,0,1,0}
    Grid<int> after = {
        { 1, 1, 0, 1, 0 }
    };

    dropSandOn(before, 0, 0);
    EXPECT_EQUAL(before, after);
}

STUDENT_TEST("All cells are 3, drop in center.") {
    // 极端情况：所有格子都是 3
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 3, 3 },
        { 3, 3, 3 }
    };
    // 这会引发复杂的连锁反应
    dropSandOn(before, 1, 1);

    // 验证没有格子 >= 4
    for (int r = 0; r < before.numRows(); r++) {
        for (int c = 0; c < before.numCols(); c++) {
            EXPECT(before[r][c] < 4);
        }
    }
}

STUDENT_TEST("Drop on cell that's already at 3.") {
    Grid<int> before = {
        { 0, 0, 0 },
        { 0, 3, 0 },
        { 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 1, 0, 1 },
        { 0, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after);
}

STUDENT_TEST("Rectangular grid (non-square).") {
    Grid<int> before = {
        { 3, 3 },
        { 0, 0 },
        { 0, 0 }
    };

    dropSandOn(before, 0, 0);

    // 验证结果合理
    for (int r = 0; r < before.numRows(); r++) {
        for (int c = 0; c < before.numCols(); c++) {
            EXPECT(before[r][c] >= 0 && before[r][c] < 4);
        }
    }
}


/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */










