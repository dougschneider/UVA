// NONTRIVIAL
// SORTING
// This algorithm works by reading in each string
// and counting the number of inversions. Each string
// is then added to a list in an index mapped based on the
// number of inversions. To list them in order the index is
// iterated, followed by the list of strings in each index.
//
// The inversions are counted by looking at each character,
// and counting the number of characters to the right of it
// that it is greater than.
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<int, vector<string>> index;

// count the number of inversions in the given input of
// given length
int countInversions(const string& input, int length)
{
    int count = 0;
    // look at each character
    for(int i = 0; i < length; ++i)
    {
        // look at the characters to the right of it
        for(int j = i+1; j < length; ++j)
        {
            // increment the count for each one that is greater
            if(input[i] > input[j])
                ++count;
        }
    }
    return count;
}

// categorize the given input with the given length based
// on it's number of inversions
void categorizeString(const string& input, int length)
{
    int numInversions = countInversions(input, length);
    // if the index doesn't exist yet, create it
    if(index.find(numInversions) == index.end())
        index[numInversions] = vector<string>();
    // add it to the correct index
    index[numInversions].push_back(input);
}

void printResults()
{
    map<int, vector<string>>::iterator it = index.begin(), end = index.end();
    // look at each index
    for(; it != end; ++it)
        // look at each element in the index
        for(int i = 0; i < it->second.size(); ++i)
            // print each element
            cout << it->second[i] << endl;
}

int main()
{
    int numTests, length, numStrings;
    string next;
    cin >> numTests;
    // for each test case
    for(int i = 0; i < numTests; ++i)
    {
        index.clear();
        cin >> length >> numStrings;

        // categorize each string
        for(int j = 0; j < numStrings; ++j)
        {
            cin >> next;
            categorizeString(next, length);
        }
        printResults();

        // print line between test case outputs
        if(i+1 < numTests)
            cout << endl;
    }
}
