// NONTRIVIAL
// COMBINATORICS
// This algorithm works by reading in the pairs of shoes and storing them in
// order. Then we look at the pairs of shoes and for each pair that is
// unmatched we follow its permutation cycle incrementing the number of swaps
// by 1 for each element in the cycle until we get back to where we started
#include <iostream>
#include <map>

using namespace std;

int main()
{
    int numTests;
    cin >> numTests;

    int numPairs;
    for(int i = 0; i < numTests; ++i)
    {
        cin >> numPairs;
        map<int, int> pairs;
        int current, next;
        // read in all the pairs of shoes
        for(int j = 0; j < numPairs; ++j)
        {
            cin >> current >> next;
            pairs[current] = next;
        }

        // look at each pair
        int swaps = 0;
        map<int, int>::iterator it = pairs.begin(), end = pairs.end();
        for(; it != end; ++it)
        {
            // if they match, skip it
            if(it->first == it->second)
                continue;
            current = pairs[it->first];
            int first = current;
            // follow the permutation cycle until we
            // get back to where we started
            while(true)
            {
                int tmp = pairs[current];
                pairs[current] = current;
                current = tmp;
                // we're back at the start so we're done
                if(current == first)
                    break;
                ++swaps;
            }
        }
        cout << swaps << endl;
    }
}
