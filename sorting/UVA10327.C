// SORTING
// This algorithm works by iterating through each list of numbers. For each
// number it looks at all the numbers to the right of it. If a number is
// larger, then they will need to be swapped eventually, thus the count is
// incremented otherwise they won't need to be swapped, and it is skipped.
#include <iostream>
#include <vector>

using namespace std;

// get the minimum number of swaps needed for the
// given list of numbers to be ordered in ascending
// order.
int getMinSwaps(vector<int> & numbers)
{
    int count = 0;
    // look at each number
    for(int i = 0; i < numbers.size(); ++i)
        // look at all the numbers to the right of it
        for(int j = i+1; j < numbers.size(); ++j)
            // if they need to be swapped, increment the count
            if(numbers[i] > numbers[j])
                ++count;
    return count;
}

int main()
{
    vector<int> numbers;
    int num, next;
    // read input until we hit EOF
    while(true)
    {
        // clear the global data.
        numbers.clear();
        cin >> num;
        // break on EOF
        if(!cin)
            break;
        // read in all of the list
        for(int i = 0; i < num; ++i)
        {
            cin >> next;
            numbers.push_back(next);
        }
        // get, and print the minimum number of swaps
        int minSwaps = getMinSwaps(numbers);
        cout << "Minimum exchange operations : " << minSwaps << endl;
    }

    return 0;
}
