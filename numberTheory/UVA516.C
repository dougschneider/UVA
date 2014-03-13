// NONTRIVIAL
// NUMBER THEORY
// This algorithm works by reading in the factors of the number and calculating
// it. Then one is subtracted and the resulting number is factorized into prime
// numbers.
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>

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

    // add the primes to the list and return them
    vector<int> primes;
    for(int i = 2; i <= N; ++i)
        if(isPrime[i])
            primes.push_back(i);
    return primes;
}

// factorize the givem number and put the result in factorization
// as a map of numbers to their powers
void factorize(int num, map<int, int>& factorization, vector<int> primes)
{
    int i = 0;
    int current;
    while(true)
    {
        current = primes[i];
        // if this number is a factor
        if(num/current >= 1 && num % current == 0)
        {
            // increment it's power in the map
            if(factorization.find(current) == factorization.end())
                factorization[current] = 0;
            factorization[current] += 1;
            num /= current;
        }
        else// otherwise move onto the next possible factor
            ++i;

        // once we get to 1, we're done
        if(num == 1)
            break;
    }
}

int main()
{
    vector<int> primes = generatePrimes(40000);

    while(true)
    {
        string line;
        getline(cin, line);
        if(line == "0")
            break;
        stringstream ss;
        ss << line;

        // get the number to factorize
        int base, power;
        int number = 1;
        while(true)
        {
            ss >> base >> power;
            if(!ss)
                break;
            number *= pow(base, power);
        }
        --number;

        // factorize the number
        map<int, int> factorization;
        factorize(number, factorization, primes);

        // print the prime factorization
        map<int, int>::reverse_iterator it = factorization.rbegin(),
                                        end = factorization.rend();
        bool first = true;
        for(; it != end; ++it)
        {
            if(!first)
                cout << " ";
            first = false;
            cout << it->first << " " << it->second;
        }
        cout << endl;
    }
}
