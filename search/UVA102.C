// SEARCH
// This algorithm tries all permutations of bins to find the one that requires
// the lowest number of movements of glass between all bins. The results are
// stored in a map of sets so the minimum result can easily be access via the
// first element of the map, and the first element of the respective set.
#include <iostream>
#include <map>
#include <set>

using namespace std;

// a representation for a recycling bin
struct Bin
{
    int B, G, C;
};

// get the number of movements required when the given
// bins are used to hold, brown, green, and clear glass
// respectively
int getMovements(Bin& B, Bin& G, Bin& C)
{
    int cost = 0;
    cost += B.G + B.C;
    cost += G.B + G.C;
    cost += C.B + C.G;
    return cost;
}

int main()
{
    Bin first, second, third;
    while(true)
    {
        // read in the bins
        cin >> first.B >> first.G >> first.C;
        cin >> second.B >> second.G >> second.C;
        cin >> third.B >> third.G >> third.C;
        
        // stop at EOF
        if(!cin)
            break;

        map<int, set<string> > movements;

        // find the number of movements required for each permutation
        movements[getMovements(first, second, third)].insert("BGC");
        movements[getMovements(first, third, second)].insert("BCG");
        movements[getMovements(third, second, first)].insert("CGB");
        movements[getMovements(third, first, second)].insert("GCB");
        movements[getMovements(second, first, third)].insert("GBC");
        movements[getMovements(second, third, first)].insert("CBG");

        // print the minimum result
        cout << *(movements.begin()->second.begin()) << " " <<
            movements.begin()->first << endl;
    }
    return 0;
}
