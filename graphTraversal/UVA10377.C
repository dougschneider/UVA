// NONTRIVIAL
// GRAPH TRAVERSAL
// This algorithm works by building up a maze in a 2d array from the input. The
// robot is then maintained as a set of global variables. The actions are read
// in and applied to the global variables until the quit action. At which point
// the final state of the robot is printed out.
#include <iostream>

using namespace std;

// directions
static const int NORTH = 0;
static const int EAST = 1;
static const int SOUTH = 2;
static const int WEST = 3;

// commands
static const char CW = 'R';
static const char CCW = 'L';
static const char FORWARD = 'F';
static const char QUIT = 'Q';

static const char WALL = '*';

char maze[60][60];
int currentRow, currentCol, orientation;

// read a maze from stdin with the specified number of
// rows and columns.
void readMaze(int numRows, int numCols)
{
    char next;

    // read in each row
    for(int i = 0; i < numRows; ++i)
    {
        // read in each column
        for(int j = 0; j < numCols; ++j)
        {
            cin >> noskipws >> next;
            maze[i][j] = next;
        }
        // read the newline char
        cin >> noskipws >> next;
    }
}

// move the robot forward in its currently
// facing direction. If forward leaves to a wall
// the robot is not moved.
void moveForward()
{
    // start with the current position
    int nextRow = currentRow;
    int nextCol = currentCol;

    // update the col/row after the move
    if(orientation == NORTH)
        nextRow -= 1;
    else if(orientation == EAST)
        nextCol += 1;
    else if(orientation == SOUTH)
        nextRow += 1;
    else if(orientation == WEST)
        nextCol -= 1;

    // if it's a wall, do nothing
    if(maze[nextRow][nextCol] == WALL)
        return;

    // update the position
    currentRow = nextRow;
    currentCol = nextCol;
}

// read in all of the commands and move the robot
// based on them
void travel()
{
    char next;

    // while we still have commands
    while(true)
    {
        cin >> skipws >> next;

        // rotate right
        if(next == CW)
            orientation = (orientation + 1) % 4;
        // rotate left
        else if(next == CCW)
            orientation = (orientation - 1 + 4) % 4;
        // we're done
        else if(next == QUIT)
            return;
        // move forward
        else if(next == FORWARD)
            moveForward();
    }
}

int main()
{
    int numTests, numRows, numCols;
    cin >> numTests;

    // look at each test case
    for(int t = 0; t < numTests; ++t)
    {
        cin >> numRows >> numCols;

        // initialize the maze
        char c;
        cin >> noskipws >> c;
        readMaze(numRows, numCols);

        // initialize the robots state
        cin >> skipws >> currentRow >> currentCol;
        --currentRow;
        --currentCol;
        orientation = 0;

        // move the robot according to the commands
        travel();

        // print the resulting tile
        cout << currentRow+1 << " " << currentCol+1 << " ";

        // print the facing direction
        if(orientation == NORTH)
            cout << "N";
        else if(orientation == EAST)
            cout << "E";
        else if(orientation == SOUTH)
            cout << "S";
        else if(orientation == WEST)
            cout << "W";
        cout << endl;

        // print a blank line between test case outputs
        if(t + 1 < numTests)
            cout << endl;
    }

    return 0;
}
