// NONTRIVIAL
// GEOMETRY
// This algorithm works by taking the set of input trees.  It then tries
// removing each possible combination of trees and computing the perimeter of
// the convex hull. If the cut down trees provide enough fence for the convex
// hull, it is stored. The minimum value is also stored upon a successful
// configuration. Configurations that have a higher value than the minimum
// stored so far are skipped (we don't compute the convex hull for them).
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <set>
#include <vector>
#include <map>
#include <numeric>
#include <iomanip>

using namespace std;

// epsilon used in floating point comparison
#define EPSILON 1E-10

// representation of a Tree
struct Point
{
    double x, y, v, l;
};

// set of trees, cleared of use in each test case
vector<Point> trees;

// Accumulation Functor used to add up the values of a set of trees
struct SumValue
{
    double operator()(int first, int second)
    {
        return first + trees[second].v;
    }
};

// Accumulation Functor used to add up the lengths of fence
// provided be a set of trees
struct SumLength
{
    double operator()(int first, int second)
    {
        return first + trees[second].l;
    }
};

// Comparison Functor used to order Trees lexicographically first on
// value, second on number of trees.
struct ValComp
{
    bool operator()(const set<int>& first, const set<int>& second)
    {
        // get the value of the first set of trees
        int firstVal = accumulate(first.begin(), first.end(), 0, SumValue());
        // get the value of the second set of trees
        int secondVal = accumulate(second.begin(), second.end(), 0, SumValue());
        if(firstVal != secondVal)
            return firstVal < secondVal;
        return first.size() < second.size();
    }
};

/* The following (up to END CITATION) is taken from:
 * http://webdocs.cs.ualberta.ca/~contest/code/2D_Geometry/convex_hull.c
 */
Point *P0;

enum {CCW, CW, CL};

int cross_prod(Point *p1, Point *p2, Point *p0)
{
    double res, x1, x2, y1, y2;

    x1 = p1->x - p0->x;
    x2 = p2->x - p0->x;
    y1 = p1->y - p0->y;
    y2 = p2->y - p0->y;

    res = x1*y2 - x2*y1;

    if (fabs(res) < EPSILON)
        return CL;
    else if (res > 0.0)
        return CW;
    else
        return CCW;
}

int polar_cmp(Point *p1, Point *p2)
{
    int res;
    double d, x1, x2, y1, y2;

    res = cross_prod(p1, p2, P0);

    if (res == CW)
        return -1;
    else if (res == CCW)
        return 1;
    else {
        x1 = p1->x - P0->x;
        x2 = p2->x - P0->x;
        y1 = p1->y - P0->y;
        y2 = p2->y - P0->y;

        d = ((x1*x1) + (y1*y1)) - ((x2*x2) + (y2*y2));

        if (fabs(d) < EPSILON)
            return 0;
        else if (d < 0.0)
            return -1;
        else
            return 1;
    }
}

int convex_hull(Point *poly, int n, Point *hull)
{
    int i, min, h;

    if (n < 1)
        return 0;

    min = 0;
    P0 = &hull[0];
    *P0 = poly[0];

    for (i = 1; i < n; i++) {
        if ((poly[i].y < P0->y) || 
                ((poly[i].y == P0->y) && (poly[i].x < P0->x))) {
            min = i;
            *P0 = poly[i];
        }
    }

    poly[min] = poly[0];
    poly[0] = *P0;
    h = 1;

    if (n == 1)
        return h;

    qsort(poly+1, n-1, sizeof(poly[1]),
            (int (*)(const void *, const void *))polar_cmp);

    for (i = 1; i < n; i++) {
        if ((fabs(poly[i].x - hull[0].x) > EPSILON) ||   
                (fabs(poly[i].y - hull[0].y) > EPSILON))  {
            break;
        }
    }

    if (i == n)
        return h;

    hull[h++] = poly[i++];

    for ( ; i < n; i++) {
        while ((h > 1) &&
                (cross_prod(&poly[i], &hull[h-1], &hull[h-2]) != CCW)) {
            h--;
        }

        hull[h++] = poly[i];
    }

    return h;
}
/* END CITATION */

// get the length of required fence for the given hull of
// the given size in points.
double getRequiredFence(Point *hull, int size)
{
    // find the perimeter of the convex hull
    double result = 0;
    for(int i = 0; i < size; ++i)
    {
        Point first = hull[(i-1+size) % size];
        Point second = hull[i];
        // add distance between first and second
        result += pow(pow(first.x - second.x, 2) +
                      pow(first.y - second.y, 2), 0.5);
    }
    return result;
}

// return true if the given set of removed trees is a valid
// set. Here valid is defined as having enough available wood to
// build a fence around the remaining trees.
bool isValid(set<int>& removed, map<set<int>, double>& leftover)
{
    // create the set of points that are being used
    Point used[trees.size()];
    int current = 0;
    for(int i = 0; i < trees.size(); ++i)
        if(removed.find(i) == removed.end())
            used[current++] = trees[i];

    // find the convex hull of the trees
    Point hull[current];
    int size = convex_hull(used, current, hull);

    // get the required amount of fence
    double requiredFence = getRequiredFence(hull, size);
    // get the available fence
    double availableFence = accumulate(removed.begin(), removed.end(),
                                        0, SumLength());

    // store the leftover wood and return true if this is a useable
    // configuration, otherwise false.
    leftover[removed] = availableFence - requiredFence;
    return (availableFence - requiredFence > EPSILON);
}

// Find the minimal hull with the current set of trees.
// The optimal removed set of tree indices is returned, and
// the amount of leftover wood is returned through the
// leftoverWood variable.
set<int> find_minimal_hull(double& leftoverWood)
{
    // create a queue of tree sets
    priority_queue<set<int>, vector<set<int> >, ValComp> q;
    // initialize it with each tree
    for(int i = 0; i < trees.size(); ++i)
    {
        set<int> s;
        s.insert(i);
        q.push(s);
    }

    int minVal = 1000000;
    set<set<int>, ValComp> useable;
    set<set<int> > searched;
    map<set<int>, double> leftover;
    // iterate until we find the solution
    while(q.size() > 0)
    {
        // get the next set of removed trees
        set<int> next = q.top();
        q.pop();

        // if the value of these trees is too large, or
        // we've already visited it, skip it
        int currentValue = accumulate(next.begin(), next.end(), 0, SumValue());
        if(searched.find(next) != searched.end() ||
                currentValue > minVal)
            continue;
        searched.insert(next);

        // if this is a valid set of removed trees, try it
        if(isValid(next, leftover))
        {
            // use the minimum
            minVal = min(minVal, currentValue);
            // store it in the result set in case it is better
            // than the minimum
            useable.insert(next);
        }

        // add this set with each other possible tree added to it to the
        // queue
        for(int i = 0; i < trees.size(); ++i)
        {
            // if it's already used, skip it
            if(next.find(i) != next.end())
                continue;

            // create and add the new set to the queue
            set<int> s(next);
            s.insert(i);
            q.push(s);
        }
    }

    // store the leftover wood
    leftoverWood = leftover[*useable.begin()];
    // return the optimal result
    return *useable.begin();
}

int main()
{
    int numTrees;
    int count = 0;
    while(true)
    {
        // read in the number of trees
        cin >> numTrees;
        if(numTrees == 0)
            break;
        ++count;

        trees.clear();
        // read in all the trees
        for(int i = 0; i < numTrees; ++i)
        {
            Point t;
            cin >> t.x >> t.y >> t.v >> t.l;
            trees.push_back(t);
        }

        // print new lines between test cases
        if(count > 1)
            cout << endl;

        // print the current forrest
        cout << "Forest " << count << endl;
        double leftoverWood;
        set<int> cut = find_minimal_hull(leftoverWood);
        set<int>::iterator it = cut.begin(), end = cut.end();

        // print out the cut down trees
        cout << "Cut these trees: ";
        for(; it != end; ++it)
        {
            if(it != cut.begin())
                cout << " ";
            cout << *it+1;
        }
        cout << endl;

        // print out the extra wood
        cout << "Extra wood: ";
        cout << fixed;
        cout << setprecision(2);
        cout << leftoverWood << endl;
    }

    return 0;
}
