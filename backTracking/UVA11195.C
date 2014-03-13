// NONTRIVIAL
// BACKTRACKING
// This algorithm works by iterating through each column
// of the chessboard and attempting to place a queen on each
// of the rows. A queens placement is skipped when one of the following
// conditions is violated:
//    - board[row][col] == '*'
//    - the row has been used by another queen
//    - one of the two diagonals that run through (row, col) have
//      been taken by another queen.
// The rows and diagonals taken are kept track of using bitmasks for efficiency.
#include <cstdio>

typedef unsigned long long uint_32;

int n, solution;
char board[16][16];

void solve(int current, uint_32 takenRows, uint_32 takenDiagonalsDown, uint_32 takenDiagonalsUp)
{
    // if we get to n, we've placed all queens
    if(current == n)
    {
        ++solution;
        return;
    }

    // iterate through all the rows
    for(int i = 0; i < n; ++i)
    {
        // if this place violates the conditions of the problem, skip it
        if(board[i][current] == '*' || takenRows & (1<<i) ||
                (takenDiagonalsDown & (1 << (i + n-current-1))) ||
                (takenDiagonalsUp & (1 << (i + current))))
            continue;

        // move to the next queen, update the bit masks.
        solve(current+1,
              takenRows | (1 << i),
              takenDiagonalsDown | (1 << (i + n-current-1)),
              takenDiagonalsUp | (1 << (i + current)));
    }
}

int main()
{
    int current = 1;

    uint_32 takenRows, takenDiagonalsDown, takenDiagonalsUp;
    takenRows = takenDiagonalsDown = takenDiagonalsUp = 0;

    char c;
    int dummy = scanf("%d", &n);
    // process each test case
    while(n)
    {
        // populate the board
        int i, j;
        for(i = 0; i < n; ++i)
        {
            for(j = 0; j < n; ++j)
            {
                dummy = scanf("%c", &c);
                board[i][j] = c == '.' ? '.' : '*';
                if(c == '\n')
                    j--;
            }
        }

        // get a solution
        solution = 0;
        solve(0, takenRows, takenDiagonalsDown, takenDiagonalsUp);
        // print the solution
        printf("Case %d: %d\n", current, solution);
        ++current;
        dummy = scanf("%d", &n);
    }

    return 0;
}
