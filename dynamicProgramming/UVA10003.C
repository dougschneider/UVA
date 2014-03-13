// DYNAMIC PROGRAMMING
// This algorithm solves the problem by using the minimum value for the choice
// of cut on each level of recursion. The range of possible cuts is kept track
// of using indices l and r into the list of possible cuts. Each time the
// problem is split, it is split on an index i into two subproblems of indices
// l to i-1 and i+1 to r. The DP table is indexed with l and r on each step.
#include <iostream>
#include <vector>

using namespace std;

// the dp table
int table[100][100];

int calc(int length, int l, int r, vector<int>& cuts)
{
    // we're out of cuts to make
    if(l > r)
        return 0;

    // find the minimum cost for this cut
    int min = -1;
    for(int i = l; i <= r; ++i)
    {
        int cost;
        // if we already have the value cached, use it
        if(table[l][r] != -1)
        {
            cost = table[l][r];
        }
        else
        {
            // solve the problem for each side if using this cut
            cost = calc(cuts[i]-cuts[l-1], l, i-1, cuts) + 
                   calc(cuts[r+1]-cuts[i], i+1, r, cuts) +
                   length;
        }

        // replace the minimum when necessary
        if(min == -1 || cost < min)
            min = cost;
    }
    // cache the result
    table[l][r] = min;

    return min;
}

int main()
{
    int length, numCuts;
    // for each test case
    while(true)
    {
        // get the length of the stick
        cin >> length;
        if(length == 0)
            break;

        // initialize the dp table
        for(int i = 0; i < 100; ++i)
            for(int j = 0; j < 100; ++j)
                table[i][j] = -1;

        // read in the number of cuts
        cin >> numCuts;

        // initialize the cuts
        vector<int> cuts(numCuts + 2);
        cuts[0] = 0;
        cuts[numCuts + 1] = length;
        int cut;
        // read in the given cuts
        for(int i = 0; i < numCuts; ++i)
        {
            cin >> cut;
            cuts[i+1] = cut;
        }

        // print the result
        cout << "The minimum cutting is " <<
            calc(length, 1, numCuts, cuts) << "." << endl;
    }
    return 0;
}
