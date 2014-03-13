// DYNAMIC PROGRAMMING
// This algorithm works by using Dynamic Programming. It solves
// the larger problem based on two sub problems:
//      numWaysToMakeChange(change-coinValue[coin], coin)
//      numWaysToMakeChange(change, coin-1)
// i.e. the number of ways to make change using that coin, and
// the number of ways to make change not using that coin.
#include <iostream>

using namespace std;

// values of coins
int coinValues[] = {1, 5, 10, 25, 50};

// DP table
int table[5][8000];

// return the number of different ways to make the given change
// starting with the given coin and using only coins below it
int numWaysToMakeChange(int change, int coin)
{
    // if either change or coin is less than zero, we can't do
    // this, so return 0
    if(change < 0 || coin < 0)
        return 0;

    // if we have the result already, return it
    if(table[coin][change] != -1)
        return table[coin][change];

    int result = 0;
    int val;

    // if we can, use this type of coin, and solve for the lower amount
    // of change
    if(change-coinValues[coin] >= 0)
    {
        val = numWaysToMakeChange(change-coinValues[coin], coin);

        // save the result
        table[coin][change-coinValues[coin]] = val;
        result += val;
    }

    // if we can, try using only lower valued coins
    if(coin-1 >= 0)
    {
        val = numWaysToMakeChange(change, coin-1);

        // save the result
        table[coin-1][change] = val;
        result += val;
    }

    return result;
}

int main()
{
    // initilize the DP table
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 8000; ++j)
        {
            if(j == 0)
                table[i][j] = 1;
            else
                table[i][j] = -1;
        }
    }

    int change;
    // consider each test case
    while(true)
    {
        // read in the change quantity
        cin >> change;
        if(!cin)
            break;

        // calculate and print the result
        cout << numWaysToMakeChange(change, 4) << endl;
    }

    return 0;
}
