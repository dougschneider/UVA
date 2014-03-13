// NONTRIVIAL
// GRAPH ALGORITHM
// This algorithm essentially works like
// Prims algorithm. It reads in all of the freckles.
// It starts the graph with a single freckle. It then
// adds the freckle with the shortest distance to the graph
// and this repeats until completion.
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// a point to represent a freckle
struct Point
{
    double x, y;

    // compute the distance between this point and another
    double dist(const Point& other) const
    {
        return pow(pow(x-other.x, 2) + pow(y-other.y, 2), 1.0/2);
    }
};

// build a minimum spanning tree for the set of freckles. The
// edges added aren't actually kept track of, just the total length.
double buildGraph(vector<Point>& freckles)
{
    // get the first freckle, update the graphs
    vector<Point> removed;
    removed.push_back(*(freckles.begin()));
    freckles.erase(freckles.begin());
    double totalDist = 0;

    // while there are still freckles not added
    while(freckles.size() > 0)
    {
        vector<Point>::iterator it = freckles.begin(), end = freckles.end();
        double minDist = -1;
        double dist;
        vector<Point>::iterator closest;
        // look at each possible freckle to be added
        for(; it != end; ++it)
        {
            // look at each freckle currently in the graph
            vector<Point>::iterator it2 = removed.begin(), end2 = removed.end();
            for(; it2 != end2; ++it2)
            {
                dist = it2->dist(*it);
                // if the distance is less than the minimum, use this edge
                if(minDist == -1 || dist < minDist)
                {
                    minDist = dist;
                    closest = it;
                }
            }
        }

        // update the graphs and total distance
        removed.push_back(*closest);
        freckles.erase(closest);
        totalDist += minDist;
    }

    // return the result
    return totalDist;
}

int main()
{
    // read in the number of tests
    int numTests;
    cin >> numTests;

    int numFreckles;
    // look at each test case
    for(int i = 0; i < numTests; ++i)
    {
        cin >> numFreckles;

        // read in all of the freckles
        vector<Point> freckles(numFreckles);
        for(int j = 0; j < numFreckles; ++j)
            cin >> freckles[j].x >> freckles[j].y;

        // output the result
        cout << fixed;
        cout << setprecision(2);
        cout << buildGraph(freckles) << endl;

        // print a blank line between test cases
        if(i+1 < numTests)
            cout << endl;
    }

    return 0;
}
