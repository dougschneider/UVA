// NONTRIVIAL
// ARITHMETIC
// This algorithm works by first working out the depth, i.e. how many levels of
// non worker cats there are. It does this by starting at depth one and working
// its way up.  It has found the depth when:
// <depth> root(height) - 1 == <depth> root(workers)
// Once we have the depth we solve for the branching factor:
// branching = <depth> root(workers).
// With the depth and branching factor it finds the number of non workers by
// adding up the number of workers at each level of depth. Finally, it does
// the same for finding the total height but multiplies by the height and
// adds that up instead.
#include <cmath>
#include <iostream>

#define EPS 1e-9

using namespace std;

// get the depth i.e. iterations of cats being in hats given
// the initial height and number of workers
int getDepth(int height, int workers)
{
    // if height is 1 we're done
    if(height == 1)
        return 1;

    // recurse until this equality holds:
    // <depth> root(height) - 1 == <depth> root(workers)
    int depth = 1;
    while(true)
    {
        if(fabs((pow(height, 1.0/depth) - 1) - pow(workers, 1.0/depth)) < EPS)
            return depth; // we've found the correct depth
        ++depth;
    }
}

// get the nuber of workers givien the initial height, depth, and
// branching factor. This is done by recursing the 'tree' and
// counting up the number of cats at each level (excluding leaves).
int getNumNonWorkers(int height, int depth, int branching)
{
    // once we get to height 1, we're out of non-workers
    if(height == 1)
        return 0;

    return pow(branching, depth) +
        getNumNonWorkers(height/(branching + 1.0), depth+1, branching);
}

// get the total height by recursing, and multiplying the number of
// cats at each level by their height.
int getTotalHeight(int height, int depth, int branching)
{
    // anything less than height 1 doesn't exist
    if(height == 0)
        return 0;

    return pow(branching, depth) * height +
        getTotalHeight(height/(branching + 1.0), depth+1, branching);
}

int main()
{
    int height, workers;
    while(true)
    {
        cin >> height >> workers;
        if(height == 0 && workers == 0)
            break;
        int depth = getDepth(height, workers);
        int branching = pow(workers, 1.0/depth) + 0.5;
        cout << getNumNonWorkers(height, 0, branching) << " ";
        cout << getTotalHeight(height, 0, branching) << endl;
    }
    return 0;
}
