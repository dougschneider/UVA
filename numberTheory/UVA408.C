// NONTRIVIAL
// NUMBER THEORY
// This algorithm works by reading in the step and mod. If the GCD of the two
// numbers is 1, then they are CoPrimes and they can compute all values in
// [0,mod-1].
#include <cstdio>
#include <iostream>

using namespace std;

// return the GCD for the two inputs
// Taken from Competitive Programming 3
int inline gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int step, mod;
    while(true)
    {
        cin >> step >> mod;
        // stop when we hit EOF
        if(!cin)
            break;
        printf("%10d %9d", step, mod);
        // if they step and mod are CoPrimes, its a good choice
        if(gcd(step, mod) == 1)
            printf("    Good Choice\n");
        // otherwise it's a bad choice
        else
            printf("    Bad Choice\n");
        printf("\n");
    }
}
