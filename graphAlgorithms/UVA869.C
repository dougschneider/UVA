// NONTRIVIAL
// GRAPH ALGORITHMS
// This algorithm works by reading in both airlines flights
// as graphs with directed edges. For each city a list of cities it
// connects to is produced using DFS and the visited cities in that
// search are the connected cities. At the end the resulting sets
// are compared to see if the airlines are equivalent.
#include <iostream>
#include <map>
#include <set>

using namespace std;

// dfs from the starting city, the visted cities are populated.
// These are all the connected cities
void dfs(char current, map<char, set<char> > graph, set<char>& visited)
{
    // if we've already visited this city, don't explore it
    if(visited.find(current) != visited.end())
        return;
    visited.insert(current);

    // look at each neighbour
    set<char>::iterator it = graph[current].begin(),
                        end = graph[current].end();
    for(; it != end; ++it)
    {
        // explore the neighbour
        dfs(*it, graph, visited);
    }
}

// find the cities each city in the graph is connected to.
// this is done using dfs on each city in the graph
void findConnected(map<char, set<char> >& graph,
                   map<char, set<char> >& connected)
{
    map<char, set<char> >::iterator it = graph.begin(), end = graph.end();
    for(; it != end; ++it)
        dfs(it->first, graph, connected[it->first]);
}

// read in a graph from stdin
void readGraph(map<char, set<char> >& graph)
{
    // get the number of edges to read
    int numEdges;
    cin >> numEdges;

    // read each edge and add it to the graph
    char from, to;
    for(int i = 0; i < numEdges; ++i)
    {
        cin >> from >> to;
        graph[from].insert(to);
    }
}

int main()
{
    int numTests;
    cin >> numTests;

    for(int i = 0; i < numTests; ++i)
    {
        // read in the airline graphs
        map<char, set<char> > g1, g2;
        readGraph(g1);
        readGraph(g2);

        // compute the connections from each starting city
        map<char, set<char> > c1, c2;
        findConnected(g1, c1);
        findConnected(g2, c2);

        // check if they are equal
        bool equal = true;
        map<char, set<char> >::iterator it = c1.begin(), end = c1.end();
        for(; it != end; ++it)
        {
            // are there differences, or does a city exist in the
            // first airline that isn't in the second?
            if(c2.find(it->first) == c2.end() ||
                    it->second != c2[it->first])
            {
                equal = false;
                break;
            }
        }

        it = c2.begin(), end = c2.end();
        for(; it != end; ++it)
        {
            // is there a city in the second airline that doesn't
            // exist in the first?
            if(c1.find(it->first) == c1.end())
            {
                equal = false;
                break;
            }
        }

        // print the result
        if(equal)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        // print a blank line between test outputs
        if(i+1 < numTests)
            cout << endl;
    }
    return 0;
}
