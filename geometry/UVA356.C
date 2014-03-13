// NONTRIVIAL
// GEOMETRY
// This algorithm works by finding the number of squares partially and fully
// covered by the top right corner of a circle with the input radius.  The
// answer is then multiplied by 4 to get the solution.
//
// We check if a square is fully covered by checking if its outer corner's
// squared euclidean distance from the origin is less than the radius squared.
// If it is, it's fully covered.  Other wise we check if it's inner corners
// squared euclidean distance is less than the radius squared. If it is, the
// square is partially covered. Otherwise it isn't covered at all.
#include <iostream>

using namespace std;

int N, fullyCovered, partiallyCovered;

// keep the raidus^2 to prevent square rooting
double radius2;

// a 2d point, uses ints to prevent inprecision
struct Point
{
    int x, y;

    Point()
    {
        x = y = 0;
    }

    Point(int x, int y) :
        x(x), y(y)
    {
    }

    // compute the squared distance between this and
    // the given point
    int dist2(const Point & other) const
    {
        return ((x-other.x)*(x-other.x)) +
               ((y-other.y)*(y-other.y));
    }
};

Point origin = Point();

// return true if the square with the given point is
// fully covered. Otherwise false.
bool isFullyCovered(const Point& point)
{
    return point.dist2(origin) <= radius2;
}

// return true if the square with the given point is
// partially covered. Otherwise false.
bool isPartiallyCovered(const Point& point)
{
    // get the inner point
    Point innerPoint(point.x-1, point.y-1);
    // check if the inner point is covered
    return isFullyCovered(innerPoint);
}

void countSquares()
{
    // look at the top right corner of the board
    for(int i = 1; i <= N; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            // if fully covered
            if(isFullyCovered(Point(i, j)))
                ++fullyCovered;// increment fully covered
            // if partially covered
            else if(isPartiallyCovered(Point(i, j)))
                ++partiallyCovered;// increment partially covered
        }
    }

    // multiply answer by 4
    fullyCovered<<=2;
    partiallyCovered<<=2;
}

int main()
{
    int first = true;
    // iterate until end of file
    while(true)
    {
        cin >> N;
        fullyCovered = partiallyCovered = 0;
        // get radius^2
        radius2 = (2*N - 1)/2.0;
        radius2 = radius2*radius2;
        // if end of file we're done
        if(!cin)
            break;
        // if not the first input, add a blank line between answers
        if(!first)
            cout << endl;
        // count the number of partially, and fully occupied squares
        countSquares();
        // print the result
        cout << "In the case n = " << N << ", " << partiallyCovered <<
                " cells contain segments of the circle." << endl;
        cout << "There are " << fullyCovered << " cells completely " <<
                "contained in the circle." << endl;
        first = false;
    }
}
