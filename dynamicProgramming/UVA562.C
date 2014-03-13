// NONTRIVIAL
// DYNAMIC PROGRAMMING
// This algorithm works by breaking the problem down into the two sub problems.
// Whats the best solution with n-1 coins if I give the nth coin to person one,
// and the same giving the nth coin to person two. The solutions are stored in
// a table used for DP based on the current difference between the amount of
// coins assigned to each person, and the index into the list of the coin we're
// currently considering. The index in the list is incremented by one on each
// level of recursion (starting at 0). This algorithm is performed at each
// level of recursion.
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// the table used for DP, stores the possible differences, and the coin
// indexes
int table[50001][100];

int solve(int first, int second, int current, vector<int>& coins)
{
    // get the current difference
    int diff = abs(first-second);

    // if we already have the result stored, return it
    if(table[diff][current] != -1)
        return table[diff][current];

    if(current == coins.size())
        return diff;

    int cur = coins[current];

    // we can give this coin to the first person
    int f = solve(first + cur, second, current+1, coins);

    // or to the second person
    int s = solve(first, second + cur, current+1, coins);

    // get the best result, cache it, and return it
    int result = min(f, s);
    table[diff][current] = result;
    return result;
}

int main()
{
    // read in the number of tests
    int numTests, numCoins;
    cin >> numTests;

    // look at each test case
    for(int i = 0; i < numTests; ++i)
    {
        // initialize the DP table
        for(int i = 0; i < 50001; ++i)
            for(int j = 0; j < 100; ++j)
                table[i][j] = -1;

        // read in the coins
        cin >> numCoins;
        vector<int> coins(numCoins);
        for(int j = 0; j < numCoins; ++j)
            cin >> coins[j];

        // print the solution
        cout << abs(solve(0, 0, 0, coins)) << endl;
    }
    return 0;
}
