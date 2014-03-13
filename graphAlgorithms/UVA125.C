// NONTRIVIAL
// GRAPH ALGORITHMS
// This algorithm finds the number of paths between all intersections using a
// modified Floyd-Warshalls algorithm. It does this by multiplying the path
// between nodes i and k by the number of paths between k and j for all k, i,
// and j. After this is done, it adds paths of infinity to nodes affected by
// nodes having paths to themselves.
#include <iostream>
#include <set>

using namespace std;

int size;

void build(int adjMatrix[30][30])
{
    // find the number of paths between all intersections
    for(int k = 0; k < size; ++k)
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
                adjMatrix[i][j] += adjMatrix[i][k] * adjMatrix[k][j];

    // for intersections that have paths to themselves
    // add infinite paths
    for(int k = 0; k < size; ++k)
        if(adjMatrix[k][k] > 0)
            for(int i = 0; i < size; ++i)
                for(int j = 0; j < size; ++j)
                    if(adjMatrix[i][k] != 0 && adjMatrix[k][j] != 0)
                        adjMatrix[i][j] = -1;
}

int main()
{
    int adjMatrix[30][30];

    int count = -1;
    int numStreets;
    // read in each test case
    while(true)
    {
        // break out at EOF
        cin >> numStreets;
        if(!cin)
            break;

        ++count;
        // initialize the adjacency matrix
        for(int i = 0; i < 30; ++i)
            for(int j = 0; j < 30; ++j)
                adjMatrix[i][j] = 0;
        size = 0;

        // read in the intersection connections
        int from, to;
        for(int i = 0; i < numStreets; ++i)
        {
            cin >> from >> to;
            adjMatrix[from][to] = 1;
            // keep track of the number of intersections
            size = max(size, max(from, to));
        }
        size += 1;

        // build the matrix of number of paths
        build(adjMatrix);

        // print the result
        cout << "matrix for city " << count << endl;
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                cout << adjMatrix[i][j];
                if(j + 1 < size)
                    cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
