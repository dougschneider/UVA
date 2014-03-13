// NUMBER THEORY
// This algorithm computes the max n-p*x s.t. p*x <= n < (p+1)*x
// for the given n. It takes advantage of the fact that any prime
// x < n/2+1 is inferior to a higher prime and skips all primes below. And
// the fact that p == 1 will produce the highest answer since it reduces the
// subtraction.
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

// generate the primes in [1,N) using
// the Sieve of Eratosthenes
vector<int> generatePrimes(int N)
{
    // use Eratosthenes Sieve
    vector<bool> isPrime(N+1, true);
    int max = pow(N, 1.0/2);
    for(int i = 2; i <= max; ++i)
        if(isPrime[i])
            for(int j = pow(i, 2); j <= N; j += i)
                isPrime[j] = false;

    // add the primes to the list and resturn them
    vector<int> primes;
    for(int i = 1; i <= N; ++i)
        if(isPrime[i])
            primes.push_back(i);
    return primes;
}


int main()
{
    // generate the needed primes
    vector<int> primes = generatePrimes(10000);

    int numTests, N;
    cin >> numTests;
    // consider each test case
    for(int i = 0; i < numTests; ++i)
    {
        // read in n
        cin >> N;

        int best = -1;
        int bestx;
        // look at each prime
        for(int j = 0; primes[j] < N; ++j)
        {
            int x = primes[j];
            // any prime < N/2 is inferior to a higher prime, so skip it
            if(x < N/2 + 1)
                continue;

            // let p = 1, minimize subtraction from best
            int p = 1;
            if((p+1)*x > N && N-(p*x) > best)
            {
                // store the best result
                best = N-(p*x);
                bestx = x;
            }
        }

        // output the best result
        cout << bestx << endl;
    }
}
