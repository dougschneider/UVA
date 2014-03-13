// NONTRIVIAL
// COMBINATORICS
// This algorithm works by recursively exploring the input set of numbers.
// it starts by looking at the first possible element at each depth of
// the recursion and shuffling the numbers over for all possibilities at
// the deepest level and moves up a level when out of possibilities. This
// is done at all levels. By sorting the list before this process begins
// we are guaranteed the output being sorted appropriately.
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

const int K = 6;

using namespace std;

// recursively explore the input numbers and print out all ordered combinations
// numbers printed out are in order that they appear in the input list. And combinations
// are printed in lexicographic order. Assuming the input list is sorted.
//
// Position must be 0 initially, selected must be an empty list
void explore(const vector<int>& nums, int position, list<int>& selected)
{
    // if we've reached capacity, print the chosen numbers and return
    if(selected.size() == K)
    {
        list<int>::iterator it = selected.begin(), end = selected.end();
        bool first = true;
        // print the numbers with spaces in between
        for(; it != end; ++it)
        {
            if(!first)
                cout << " ";
            first = false;
            cout << *it;
        }
        cout << endl;
        return;
    }

    // look at each position between the first and the last this index
    // can take. e.g on |S| = 7, position = 0. i is in [0,1]
    int current;
    for(int i = position; i <= nums.size()-K+selected.size(); ++i)
    {
        current = nums[i];
        // add the number to selected
        selected.push_back(current);
        // recursively explore
        explore(nums, i+1, selected);
        // remove the number from selected
        selected.pop_back();
    }
}

int main()
{
    int length, num;
    bool first = true;
    // for each input
    while(true)
    {
        vector<int> numbers;
        cin >> length;
        // if the length is zero we're done
        if(length == 0)
            break;

        // read in each number
        for(int i = 0; i < length; ++i)
        {
            cin >> num;
            numbers.push_back(num);
        }
        // sort the numbers
        sort(numbers.begin(), numbers.end());

        // if we're between test cases print a new line
        if(!first)
            cout << endl;
        first = false;

        // explore the numbers for all combinations
        list<int> selected;
        explore(numbers, 0, selected);
    }
    return 0;
}
