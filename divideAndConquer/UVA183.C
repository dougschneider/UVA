// NONTRIVIAL
// DIVIDE AND CONQUER
// This algorithm uses recursion in reading the D type bitmaps by splitting the
// problem into four parts with different bounds and solving them each
// separately. It uses recursion in writing the D part by dividing the problem
// into four parts on each write and dealing with each write separately.
#include <iostream>

using namespace std;

int outCount = 0;

// read in a bitmap in the B format with the given
// number of rows and columns
bool** readB(int numRows, int numCols)
{
    // allocate the rows
    bool** bitmap = new bool*[numRows];

    for(int i = 0; i < numRows; ++i)
    {
        // allocate the columns
        bitmap[i] = new bool[numCols];

        // read in and assign each bit
        for(int j = 0; j < numCols; ++j)
        {
            char c;
            cin >> c;
            bitmap[i][j] = (c == '1')? true : false;
        }
    }

    return bitmap;
}

// output the given bitmap in the B format with the given
// number of rows and columns
void outputB(bool** bitmap, int numRows, int numCols)
{
    // iterate through each row
    for(int i = 0; i < numRows; ++i)
    {
        // iterate through each column
        for(int j = 0; j < numCols; ++j)
        {
            outCount++;
            // output new lines every 50 places
            if(outCount > 50)
            {
                cout << endl;
                outCount = 1;
            }
            // output this value
            cout << bitmap[i][j] ? "1" : "0";
        }
    }
    // end with a new line
    cout << endl;
}

// unallocate the given bitmap with the given number of rows
void deleteB(bool** bitmap, int numRows)
{
    // delete each row
    for(int i = 0; i < numRows; ++i)
        delete [] bitmap[i];

    // delete the collection of rows
    delete [] bitmap;
    bitmap = 0;
}

// get the value of the given section of the given bitmap.
char getValue(bool **bitmap, int top, int left, int bottom, int right)
{
    // get the first value
    char val = (bitmap[top][left] ? '1' : '0');

    // if any value is different than the first, return D
    for(int i = top; i < bottom; ++i)
        for(int j = left; j < right; ++j)
            if((bitmap[i][j] ? '1' : '0') != val)
                return 'D';

    // otherwise return the originally read value
    return val;
}

// output the given bitmap in the B format with the given
// number of rows and columns
void outputD(bool **bitmap, int top, int left, int bottom, int right)
{
    // break out when we get to an invalid case
    if(top >= bottom || left >= right)
        return;

    // get the value of this section
    char val = getValue(bitmap, top, left, bottom, right);

    // keep track of the number of output characters
    outCount++;
    // print a new line after 50 characters
    if(outCount > 50)
    {
        cout << endl;
        outCount = 1;
    }
    // output this value
    cout << val;

    // if the value is a D, output its quadrants
    if(val == 'D')
    {
        int rmid = (top + bottom)/2.0 + 0.5;
        int cmid = (left + right)/2.0 + 0.5;
        outputD(bitmap, top, left, rmid, cmid);
        outputD(bitmap, top, cmid, rmid, right);
        outputD(bitmap, rmid, left, bottom, cmid);
        outputD(bitmap, rmid, cmid, bottom, right);
    }
}

void readD_r(bool** bitmap, int top, int left, int bottom, int right)
{
    // break out when we get to an invalid case
    if(top >= bottom || left >= right)
        return;

    // read the next character
    char c;
    cin >> c;
    if(c == 'D')
    {
        // read in each of the quadrants
        int rmid = (top + bottom)/2.0 + 0.5;
        int cmid = (left + right)/2.0 + 0.5;
        readD_r(bitmap, top, left, rmid, cmid);
        readD_r(bitmap, top, cmid, rmid, right);
        readD_r(bitmap, rmid, left, bottom, cmid);
        readD_r(bitmap, rmid, cmid, bottom, right);
    }
    else
    {
        // assign the read value to all elements in this
        // quadrant
        bool val = c == '1' ? true : false;
        for(int i = top; i < bottom; ++i)
            for(int j = left; j < right; ++j)
                bitmap[i][j] = val;
    }
}

// read in a bitmap in the D format with the given
// number of rows and columns
bool** readD(int numRows, int numCols)
{
    // allocate the memory
    bool** bitmap = new bool*[numRows];
    for(int i = 0; i < numRows; ++i)
        bitmap[i] = new bool[numCols];

    // read the bitmap
    readD_r(bitmap, 0, 0, numRows, numCols);

    return bitmap;
}

int main()
{
    char type;
    int numRows, numCols;
    // consider each test case
    while(true)
    {
        outCount = 0;
        cin >> type >> numRows >> numCols;
        // break out when done
        if(type == '#')
            break;
        else if(type == 'B')
        {
            // read the bitmap in
            bool** bitmap = readB(numRows, numCols);

            // output the result in D format
            cout << "D";
            cout.width(4);
            cout << numRows;
            cout.width(4);
            cout << numCols << endl;
            outputD(bitmap, 0, 0, numRows, numCols);
            cout << endl;
            deleteB(bitmap, numRows);
        }
        else if(type == 'D')
        {
            // read the bitmap in
            bool** bitmap = readD(numRows, numCols);

            // output the result in B format
            cout << "B";
            cout.width(4);
            cout << numRows;
            cout.width(4);
            cout << numCols << endl;
            outputB(bitmap, numRows, numCols);
            deleteB(bitmap, numRows);
        }
    }
}
