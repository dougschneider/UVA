// NONTRIVIAL
// GRAPH ALGORITHM
// This algorithm reads in the graph and adds edges for the enemies, which are
// symmetric. It then looks at each starting node and performs node coloring on
// them (2 colors). If the graph is not bipartite, no guests can be invited.
// Otherwise, we want to invite the most guests with the same color. The
// bipartite coloring is started at each node to make sure we search all
// connected components. But if a node has already been visited, the coloring
// is stopped right away.
#include <iostream>
#include <vector>
#include <set>

using namespace std;

// colors
static const char BLACK = 'B';
static const char WHITE = 'W';

// number of each colored guest for each connected
// component in the graph
vector<int> black, white;

void r_dfs(int current, vector<set<int> >& adjList, set<int>& visited, char color, int& w, int& b, char* marked, bool& fail)
{
    // set the fail bit if invalid graph
    if(color == WHITE && marked[current] == BLACK)
        fail = true;
    if(color == BLACK && marked[current] == WHITE)
        fail = true;

    // if we've visited this node, stop the search
    if(visited.find(current) != visited.end())
        return;
    visited.insert(current);

    // color this node and count it
    if(color == WHITE)
    {
        ++w;
        marked[current] = WHITE;
        color = BLACK;
    }
    else if(color == BLACK)
    {
        ++b;
        marked[current] = BLACK;
        color = WHITE;
    }

    // search this nodes neighbours
    set<int>::iterator it = adjList[current].begin(),
                       end = adjList[current].end();
    for(; it != end; ++it)
    {
        r_dfs(*it, adjList, visited, color, w, b, marked, fail);
    }
}

// perform a dfs bipartite coloring on each connected component
// in the graph represented by the adjacency list
bool dfs(int current, vector<set<int> >& adjList, set<int>& visited, char color)
{
    int w, b;
    char marked[adjList.size()];
    // look at each node
    for(int i = 0; i < adjList.size(); ++i)
    {
        // mark all nodes as uncolored
        for(int j = 0; j < adjList.size(); ++j)
            marked[j] = 0;

        // perform the coloring on this connected component
        bool fail = false;
        w = b = 0;
        r_dfs(i, adjList, visited, BLACK, w, b, marked, fail);

        // if the component is not bipartite, the number of guests
        // that can be invited in it is 0.
        if(fail)
            w = b = 0;

        // add the number of guests for both colors
        white.push_back(w);
        black.push_back(b);
    }
    return true;
}

int main()
{
    int numTests;
    cin >> numTests;

    int numPeople, numEnemies, enemy;
    // look at each test case
    for(int i = 0; i < numTests; ++i)
    {
        // clear the list of black and white colored nodes
        black.clear();
        white.clear();

        cin >> numPeople;
        vector<set<int> > adjList(numPeople);
        // read in the graph
        for(int j = 0; j < numPeople; ++j)
        {
            cin >> numEnemies;
            for(int k = 0; k < numEnemies; ++k)
            {
                cin >> enemy;
                // we ignore enemies that are outside the given range
                if(enemy <= numPeople)
                {
                    // add a relationship in both directions (symmetry)
                    adjList[j].insert(enemy-1);
                    adjList[enemy-1].insert(j);
                }
            }
        }

        set<int> visited;
        int result = 0;
        // if the dfs succeeds, count up the max of black
        // and white colored nodes for each connected component
        if(dfs(0, adjList, visited, BLACK))
            for(int j = 0; j < white.size(); ++j)
                result += max(white[j], black[j]);

        // print the result
        cout << result << endl;
    }

    return 0;
}
