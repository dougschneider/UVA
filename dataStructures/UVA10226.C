#include <iostream>
#include <map>
#include <iomanip>

using namespace std;

int main()
{
    int numTests;
    string tree;

    cin >> numTests;
    getline(cin, tree);
    getline(cin, tree);// remove first blank
    for(int i = 0; i < numTests; ++i)
    {
        if(i > 0)
            cout << endl;

        int totalNumTrees = 0;
        map<string, int> treeCounter;
        while(true)
        {
            getline(cin, tree);
            if(tree.size() == 0 || !cin)
                break;

            totalNumTrees++;
            if(treeCounter.find(tree) != treeCounter.end())
                treeCounter[tree] += 1;
            else
                treeCounter[tree] = 1;
        }

        map<string, int>::iterator it = treeCounter.begin();
        for(; it != treeCounter.end(); ++it)
        {
            cout << it->first << " ";
            cout << setprecision(4);
            cout << fixed;
            cout << (double)it->second/totalNumTrees * 100;
            cout << endl;
        }
    }

    return 0;
}
