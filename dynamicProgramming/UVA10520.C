// DYNAMIC PROGRAMMING
// This algorithm uses standard bottom down DP to
// solve the given equation for the input N and A_n,1.
#include <iostream>

using namespace std;

typedef long long int lli;

int N, AN1;

// the table used for DP
lli table[100][100];

lli solve(int i, int j)
{
    // base case
    if(i == N && j == 1)
        return AN1;

    // return the cached value if we have it
    if(table[i][j] != -1)
        return table[i][j];

    // follow the given formula and recursively solve
    lli result = 0;
    if(i < j)
    {
        lli cur = 0;
        for(int k = i; k < j; ++k)
            cur = max(cur, solve(i, k) + solve(k+1, j));
        result = cur;
    }
    else
    {
        if(i < N)
        {
            lli cur = 0;
            for(int k = i+1; k <= N; ++k)
                cur = max(cur, solve(k, 1) + solve(k, j));
            result += cur;
        }
        if(j > 0)
        {
            lli cur = 0;
            for(int k = 1; k < j; ++k)
                cur = max(cur, solve(i, k) + solve(N, k));
            result += cur;
        }
    }

    // cache and resturn the result
    table[i][j] = result;
    return result;
}

int main()
{
    while(true)
    {
        cin >> N >> AN1;
        if(!cin)
            break;

        // initialize the DP table
        for(int i = 0; i < 100; ++i)
            for(int j = 0; j < 100; ++j)
                table[i][j] = -1;

        // print the solution
        cout << solve(1, N) << endl;
    }

    return 0;
}
