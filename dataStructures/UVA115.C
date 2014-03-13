// NONTRIVIAL
// DATA STRUCTURES
// This program calculates the relation between to people by first building a
// graph(possibly many trees) from the input. The graph is then traversed in a
// BFS manner based on the input query. A relation is formed as a string of
// '^'s and 'v's to represent the traversal to form the relation. The relation
// is then processed to produce a readable representation.
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <cstdlib>

using namespace std;

// a representation of a node to be used in the graph
struct Node
{
    Node* parent;
    set<Node*> children;
    string name;
};

// a representation of the relations between people
struct Graph
{
public:

    ~Graph()
    {
        // clean up all the leftover nodes
        set<Node*>::iterator it = nodes.begin(),
                             end = nodes.end();
        for(; it != end; ++it)
        {
            delete *it;
        }
        nodes.clear();
    }

    // add a relation to the graph. If either of
    // the nodes does not exist, add them to the
    // graph.
    void addEdge(string parent, string child)
    {
        Node* parentNode;
        Node* childNode;
        // get the parent node
        Node* tmp = getNodeWithName(parent);
        if(tmp == NULL)
            parentNode = addNode(parent);
        else
            parentNode = tmp;
        // get the child node
        tmp = getNodeWithName(child);
        if(tmp == NULL)
            childNode = addNode(child);
        else
            childNode = tmp;
        // add the relation
        parentNode->children.insert(childNode);
        childNode->parent = parentNode;
    }

    // get the human readable relation between the
    // two input people.
    string getRelation(string first, string second)
    {
        set<Node*> visited;
        // if either person doesn't exist, there is no
        // relation
        if(getNodeWithName(first) == NULL)
            return processRelation("-1");
        if(getNodeWithName(second) == NULL)
            return processRelation("-1");
        // get the relation
        return processRelation(getRelationRecursive(getNodeWithName(first),
                                                    getNodeWithName(second),
                                                    visited, ""));
    }

private:

    // find the relation between the first node and the second node by
    // recursing through the children and parent in the tree. The recursion
    // occurs until the relation is found, or there are no new nodes to visit.
    // An output of "-1" means there is no relation.
    string getRelationRecursive(Node* first, Node* second, set<Node*>& visited, string result)
    {
        if(first == NULL)
            return "-1";
        if(first == second)
            return result;
        visited.insert(first);
        
        // recurse the parent
        if(visited.find(first->parent) == visited.end())
        {
            string tmpresult = getRelationRecursive(first->parent, second, visited, result + "^");
            if(tmpresult != "-1")
                return tmpresult;
        }
        // recurse through the children
        set<Node*>::iterator it = first->children.begin(), end = first->children.end();
        for(; it != end; ++it)
        {
            if(visited.find(*it) == visited.end())
            {
                string tmpresult = getRelationRecursive(*it, second, visited, result + "v");
                if(tmpresult != "-1")
                    return tmpresult;
            }
        }

        return "-1";
    }

    // transform the graph traversal string into a
    // human readable string.
    string processRelation(string relation)
    {
        // no relation
        if(relation == "-1")
            return "no relation";

        // count the number of up and down traversals.
        int numUp = 0;
        int numDown = 0;
        string::iterator it = relation.begin(), end = relation.end();
        for(; it != end; ++it)
        {
            if(*it == '^')
                ++numUp;
            else if(*it == 'v')
                ++numDown;
        }

        // relation is child
        if(numDown == 0)
        {
            if(numUp == 1)
            {
                return "child";
            }
            else if(numUp == 2)
            {
                return "grand child";
            }
            else
            {
                string result = "grand child";
                for(int i = 0; i < numUp - 2; ++i)
                    result = "great " + result;
                return result;
            }
        }
        // relation is parent
        else if(numUp == 0)
        {
            if(numDown == 1)
            {
                return "parent";
            }
            else if(numDown == 2)
            {
                return "grand parent";
            }
            else
            {
                string result = "grand parent";
                for(int i = 0; i < numDown - 2; ++i)
                    result = "great " + result;
                return result;
            }
        }
        // relation is cousin or sibling
        else
        {
            int k = min(numUp-1, numDown-1);
            int removed = abs(numUp - numDown);
            if(k == 0 && removed == 0)
                return "sibling";
            ostringstream ss;
            ss << k << " cousin";
            if(removed > 0)
                ss << " removed " << removed;
            return ss.str();
        }
        return relation;
    }

    // add a node with the given name to
    // the graph
    Node* addNode(string name)
    {
        Node* node = new Node();
        node->parent = 0;
        node->name = name;
        nodes.insert(node);
        return node;
    }

    // get the node with the given name from
    // the graph. If one doesn't exist with the
    // given name then NULL is returned instead.
    Node* getNodeWithName(string name)
    {
        set<Node*>::iterator it = nodes.begin(),
                             end = nodes.end();
        for(; it != end; ++it)
        {
            if((*it)->name == name)
                return *it;
        }
        return NULL;
    }

    // the nodes in the graph
    set<Node*> nodes;
};

int main()
{
    string child;
    string parent;
    Graph graph;

    // build graph
    while(true)
    {
        cin >> child >> parent;
        if(child == "no.child")
            break;
        graph.addEdge(parent, child);
    }

    // solve queries
    string first, second;
    while(cin)
    {
        cin >> first >> second;
        if(cin.eof())
            break;
        string relation;
        relation = graph.getRelation(first, second);
        cout << relation << endl;
    }

    return 0;
}
