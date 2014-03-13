// GRAPH TRAVERSAL
// This algorithm works by performing a DFS on the graph.
// When it gets to a leaf it goes back up a level. It looks
// at the subtree and sees how many marbles are going to have
// to cross that edge. This number is added to the total. This is
// done recursively until we get back to the root.
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>

using namespace std;

int numExchanges;

// a structure used to represent a node in the
// given graph
struct Node
{
    int numMarbles;
    set<Node*> children;
    set<Node*> parents;
    int sum;
    int id;
    int dist;
};

void solve(Node& node, int& numMarbles, int& numNodes)
{
    // start with the stats for this node
    int totalMarbles = node.numMarbles;
    int totalNodes = 1;

    // look at the children
    set<Node*>::iterator it = node.children.begin(), end = node.children.end();
    for(; it != end; ++it)
    {
        // get the solution for the subtree
        int numMarbles, numNodes;
        numMarbles = numNodes = 0;
        solve(**it, numMarbles, numNodes);

        // add the result for the child
        totalMarbles += numMarbles;
        totalNodes += numNodes;

        // increment the number of exchanges
        numExchanges += abs(numMarbles-numNodes);
    }

    // set the solution for this subtree for the parent call
    numMarbles = totalMarbles;
    numNodes = totalNodes;
}

int main()
{
    int numNodes, node, numMarbles, numChildren;
    // read in each case
    while(true)
    {
        cin >> numNodes;
        // break out at the end
        if(numNodes == 0)
            break;

        numExchanges = 0;
        // read in each of the nodes
        vector<Node> nodes(numNodes);
        for(int i = 0; i < numNodes; ++i)
        {
            // initialize the node
            cin >> node >> numMarbles >> numChildren;
            nodes[node-1].id = node-1;
            nodes[node-1].numMarbles = numMarbles;

            // read in all the children and add the edges
            int child;
            for(int j = 0; j < numChildren; ++j)
            {
                cin >> child;
                nodes[node-1].children.insert(&(nodes[child-1]));
                nodes[child-1].parents.insert(&(nodes[node-1]));
            }
        }

        // find the root node
        int root;
        for(int i = 0; i < numNodes; ++i)
        {
            if(nodes[i].parents.size() == 0)
            {
                root = i;
                break;
            }
        }

        // get the solution and print it
        int a, b;
        a = b = 0;
        solve(nodes[root], a, b);
        cout << numExchanges << endl;
    }

    return 0;
}
