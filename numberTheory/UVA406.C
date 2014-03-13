// NONTRIVIAL
// NUMBER THEORY
// This algorithm works by generating a list of primes using the Sieve of
// Eratosthenes.  Then it gets the center index of the list and prints the
// values of the center primes based on the input C.
#include <vector>
#include <iostream>
#include <cmath>

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
    int N, C;
    bool first = true;
    while(true)
    {
        cin >> N >> C;
        if(!cin)
            break;
        // print a new line before each output but the first
        if(!first)
            cout << endl;
        first = false;

        // generate the list of primes
        vector<int> primes = generatePrimes(N);

        // get the center value
        int num;
        if(primes.size() % 2 == 0)
            num = C*2;
        else
            num = C*2 - 1;

        // get the starting place and ending place
        int start = primes.size()/2 - num/2;
        start = start < 0 ? 0 : start;
        double end = primes.size()/2 + num/2.0;
        end = end > primes.size() ? primes.size() : end;

        // output the solution
        cout << N << " " << C << ":";
        for(int i = start; i < end; ++i)
            cout << " " << primes[i];
        cout << endl;
    }
    // last new line
    cout << endl;
    return 0;
}
