// NONTRIVIAL
// GRAPH TRAVERSAL
// This algorithm works by building up an adjacency list of the input graph. It
// then traverses the graph updating the location of Theseus and the Minotaur
// along the way. Each kth node is added to a list to represent it being list
// (untraversable). Once there are no traversable neighbours of the minotaurs
// current node, we're done.
#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

char m_loc, t_loc;
int k;
char caught;
vector<char> lit;

// traverse the graph until there are no more neighbours that
// the Minotaur can traverse.
void chase(map<char, vector<char> > adjList)
{
    int sinceCandle = -1;
    char tmp;
    // loop until we have a solution
    while(true)
    {
        // if we need to light a candle, add the room to the list
        if(((++sinceCandle) % k) == 0 && !sinceCandle == 0)
            lit.push_back(t_loc);

        // update Theseus' location
        tmp = t_loc;
        t_loc = m_loc;
        // find the next traversable neighbour
        for(int i = 0; i < adjList[m_loc].size(); ++i)
        {
            // if the room is lit, or Theseus is in it, we can't go there
            if(find(lit.begin(), lit.end(), adjList[m_loc][i]) != lit.end() ||
                    tmp == adjList[m_loc][i])
                continue;

            // set the minotaurs new location, break out
            m_loc = adjList[m_loc][i];
            break;
        }

        // if the Minotaur didn't move, we're done
        if(t_loc == m_loc)
            break;
    }
    // set the location that the Minotaur was caught
    caught = t_loc;
}

int main()
{
    // look at each test case
    while(true)
    {
        // get the first character
        char next;
        cin >> next;
        // are we done?
        if(next == '#')
            break;

        // initialize test
        lit.clear();
        map<char, vector<char> > adjList;

        // read in the graph
        char parent = next;
        cin >> next;
        while(true)
        {
            // start a new parent
            if(next == ':')
            {
                cin >> next;
                continue;
            }
            // get ready for children
            if(next == ';')
            {
                cin >> parent;
                cin >> next;
                continue;
            }
            // we're done the graph
            if(next == '.')
                break;

            // add an entry to the adjacency list
            adjList[parent].push_back(next);

            cin >> next;
        }

        // read in the starting positions, and k
        scanf(" %c %c %d\n", &m_loc, &t_loc, &k);

        // solve the problem
        chase(adjList);

        // print the solution
        for(int i = 0; i < lit.size(); ++i)
            cout << lit[i] << " ";
        cout << "/" << caught << endl;
    }

    return 0;
}
