// NUMBER THEORY
// This algorithm works by first generating primes using Eratosthenes Sieve. It
// then computes the sum of possible irrational fractions for each possible
// denominator using Euler's Phi function. It then uses a binary search on the
// list of sums to find the denominator that the Kth number will have. Finally
// we iterate through the remaining part of K to get the numerator.
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

typedef unsigned long long ull;

// Generate a list of the first N primes using
// Eratosthenes Sieve.
vector<ull> generatePrimes(ull N)
{
    vector<bool> isPrime(N+1, true);
    ull max = pow(N, 1.0/2);
    // look at each potential prime for the given N
    for(ull i = 2; i <= max; ++i)
    {
        if(isPrime[i])
        {
            // cross off every multiple of this prime
            for(ull j = pow(i, 2); j <= N; j += i)
                isPrime[j] = false;
        }
    }

    // Add all of the primes to a list
    vector<ull> primes;
    for(ull i = 2; i <= N; ++i)
        if(isPrime[i])
            primes.push_back(i);
    return primes;
}

// Calculate Euler's Phi function value for
// given N.
// Taken from Competitive Programming 3
ull phi(ull N, const vector<ull>& primes)
{
    ull PF_idx = 0, PF = primes[PF_idx], ans = N;
    while(PF*PF <= N)
    {
        if(N % PF == 0)
            ans -= ans/PF;
        while(N % PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    if(N != 1) ans -= ans/N;
    return ans;
}

// return the GCD for the two inputs
// Taken from Competitive Programming 3
ull inline gcd(ull a, ull b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    ull K;
    // generate primes up to 200001
    vector<ull> primes = generatePrimes(200001);
    vector<ull> sum;
    sum.push_back(0);
    sum.push_back(1);
    // compute the sum of phis for denominators
    // up to 200000
    for(ull i = 2; i < 200001; ++i)
        sum.push_back(phi(i, primes) + sum[i-1]);

    // answer all test cases
    while(true)
    {
        cin >> K;
        // if K == 0, we're done
        if(K == 0)
            break;

        // handle two base cases
        if(K == 1)
        {
            cout << "0/1" << endl;
            continue;
        }
        else if(K == 2)
        {
            cout << "1/1" << endl;
            continue;
        }
        K -= 2;

        // binary search for the largest value we can
        // subtract from K
        ull mid, r, l;
        l = 0;
        r = sum.size()-1;
        ull last;
        while(l<r)
        {
            mid = (l+r)/2;
            if(sum[mid] > K)
                r = mid;
            else if(sum[mid] < K)
            {
                last = mid;
                l = mid+1;
            }
            else
            {
                last = mid;
                break;
            }
        }
        K -= sum[last];

        // find the numerator for the given denominator
        ull count = 0;
        for(ull j = 0; j <= last+1; ++j)
        {
            if(gcd(j, last+1) == 1)
                ++count;
            // once count is K+1 we've found the Kth
            // fraction
            if(count == K+1)
            {
                cout << j << "/" << last+1 << endl;
                break;
            }
        }
    }
}
