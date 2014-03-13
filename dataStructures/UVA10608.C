// DATA STRUCTURES
// This solution works by first building a graph from the input.
// The graph is stored as a mapping of people to a set of their
// direct friends. After building the graph BFS is performed
// iteratively to find all of the connected components. The
// size of the largest connected component is then used
// as the answer to the problem.
#include <iostream>
#include <map>
#include <set>
#include <queue>

using namespace std;

// given a start node return all the visited nodes
// from performing a BFS from that node on the given graph
set<int> BFS(map<int, set<int> > graph, int start)
{
    queue<int> toVisit;
    set<int> visited;
    toVisit.push(start);
    // search until we're out of new nodes
    while(!toVisit.empty())
    {
        int next = toVisit.front();
        visited.insert(next);
        toVisit.pop();

        // visit the neighbours
        set<int>::iterator it = graph[next].begin(),
                           end = graph[next].end();
        for(; it != end; ++it)
        {
            if(visited.find(*it) == visited.end())
                toVisit.push(*it);
        }
    }

    return visited;
}

// get the size of the largest connected component in the
// input graph
int getSizeOfLargestConnectedComponent(map<int, set<int> > graph)
{
    size_t largest = 0;
    // while there are still nodes
    while(graph.size() > 0)
    {
        // search for another connected component
        int current = graph.begin()->first;
        set<int> connectedComponent = BFS(graph, current);
        if(connectedComponent.size() > largest)
            largest = connectedComponent.size();

        // remove the visited edges so we don't consider them
        // anymore
        set<int>::iterator it = connectedComponent.begin(),
                           end = connectedComponent.end();
        for(; it != end; ++it)
        {
            graph.erase(*it);
        }
    }
    return largest;
}

// add the edge between first and second to the given graph
void addRelationToGraph(map<int, set<int> > & graph, int first, int second)
{
    // make sure the set is initialized
    if(graph.find(first) == graph.end())
    {
        graph[first] = set<int>();
    }

    // add the edge
    graph[first].insert(second);
}

int main()
{
    map<int, set<int> > graph;
    int numTests, N, M, first, second;
    cin >> numTests;
    // for each test case
    for(int i = 0; i < numTests; ++i)
    {
        cin >> N >> M;
        // for each relation
        for(int j = 0; j < M; ++j)
        {
            cin >> first >> second;
            // add the bidirectional relation to the graph
            addRelationToGraph(graph, first, second);
            addRelationToGraph(graph, second, first);
        }
        cout << getSizeOfLargestConnectedComponent(graph) << endl;
        graph.clear();
    }

    return 0;
}
