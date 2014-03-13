// NONTRIVIAL
// SIMULATION
// This algorithm works by considering the cycle length of each number in the
// given range. On each iteration it either performs n = 3n + 1 or n = n/2 if n
// is odd or even respectively.
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

typedef long long int lli;

// find the cycle length for the given n
int getCycleLength(lli n)
{
    int result = 0;
    while(n != 1)
    {
        ++result;
        if(n & 1)// if n is odd
            n = 3*n + 1;
        else
            n >>= 1;// divide by 2
    }
    return result+1;
}

int main()
{
    int f, s, low, high;
    // consider each test case
    while(true)
    {
        // read the boundaries
        cin >> f >> s;
        if(!cin)
            break;

        // get the low and high boundaries
        low = min(f, s);
        high = max(f, s);

        // consider each possible length
        lli length;
        lli maxLength = -1;
        for(int i = low; i <= high; ++i)
        {
            // get the cycle length
            length = getCycleLength(i);
            // if it's a new max, use it
            if(maxLength == -1 || length > maxLength)
                maxLength = length;
        }

        // print the result
        cout << f << " " << s << " " << maxLength << endl;
    }
    return 0;
}
