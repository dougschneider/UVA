// NONTRIVIAL
// DYNAMIC PROGRAMMING
// This algorithm works by counting the change based on sub problems with the
// following sub problems. The number of ways to count change using a different
// coin, and the number of different ways to count change-this coin, continuing
// to use this coin.
#include <iostream>
#include <set>
#include <map>

using namespace std;

// the DP table
long long int table[30001][5];

// the types of coins
int coins[] = {1, 5, 10, 25, 50};

long long int solve(int change, int coin)
{
    // if we're out of bounds, the result is 0
    if(change < 0 || coin < 0)
        return 0;

    // if we have the result already, use it
    if(table[change][coin] != -1)
        return table[change][coin];

    // find the result for the two recurrence relations
    long long int result = 0;
    result += solve(change-coins[coin], coin);
    result += solve(change, coin-1);

    // cache the result in the DP table
    table[change][coin] = result;

    return result;
}

int main()
{
    // initialize the dp table
    for(int i = 0; i < 30001; ++i)
        for(int j = 0; j < 5; ++j)
            table[i][j] = i == 0 ? 1 : -1;

    int change;
    // read all test cases
    while(true)
    {
        cin >> change;
        if(!cin)
            break;

        // get the result
        long long int result = solve(change, 4);
        // print the plural specific part
        if(result == 1)
            cout << "There is only " << result << " way ";
        else
            cout << "There are " << result << " ways ";
        // print the end
        cout << "to produce " << change << " cents change." << endl;
    }

    return 0;
}
