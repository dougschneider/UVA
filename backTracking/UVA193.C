// NONTRIVIAL
// BACKTRACKING
// This algorithm works by first representing the graph as an adjacency list.
// It steps through each node in order.  If it is possible for the node to be
// colored black (no black neighbors) then it makes a recursive call where the
// node is colored black. In addition a recursive call is made where the node
// remains white. The recursive call always deals with the next node, until
// we're out of nodes, and thus have found a solution.
#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int> numbers;
int numNodes;

void dfs(int current, const vector<set<int> >& adjList, bool color[100])
{
    // if we're done looking at all nodes
    if(current == adjList.size())
    {
        // count the number of black nodes
        int count = 0;
        for(int i = 0; i < numNodes; ++i)
            if(color[i])
                ++count;

        // if there are more black nodes than the best, store the result
        if(count > numbers.size())
        {
            numbers.clear();
            // add each node
            for(int i = 0; i < numNodes; ++i)
            {
                if(color[i])
                    numbers.insert(i);
            }
        }
        // we've reached the end so snip this branch
        return;
    }

    // check if it is possible to color this node black
    bool possible = true;
    set<int>::iterator it = adjList[current].begin(), end = adjList[current].end();
    for(; it != end; ++it)
        if(color[*it])
            possible = false;

    // if it's possible to color this node black, try it in a
    // recursive call
    if(possible)
    {
        color[current] = true;
        dfs(current+1, adjList, color);
        color[current] = false;
    }

    // check for a solution where this node remains white
    dfs(current+1, adjList, color);
}

int main()
{
    int numGraphs, numEdges, from, to;

    cin >> numGraphs;

    // start each nodes color as white
    bool color[100];
    for(int i = 0; i < 100; ++i)
        color[i] = false;

    // look at each test case
    for(int i = 0; i < numGraphs; ++i)
    {
        numbers.clear();
        cin >> numNodes >> numEdges;

        // initialize the adjacency list
        vector<set<int> > adjList;
        for(int j = 0; j < numNodes; ++j)
            adjList.push_back(set<int>());

        // add each edge to the adjacency list
        for(int j = 0; j < numEdges; ++j)
        {
            cin >> from >> to;
            adjList[from-1].insert(to-1);
            adjList[to-1].insert(from-1);
        }

        // perform the search
        dfs(0, adjList, color);

        // print the number of black nodes
        cout << numbers.size() << endl;
        set<int>::iterator it = numbers.begin(), end = numbers.end();
        // print each black node
        for(; it != end; ++it)
        {
            if(it != numbers.begin())
                cout << " ";
            cout << *it+1;
        }
        cout << endl;
    }
    return 0;
}
