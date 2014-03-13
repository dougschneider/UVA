// ARITHMETIC
// This algorithm works by computing pascals triangle. It
// then prints out each expanded equation using the computed
// binomial coefficients.
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

// global set of binomial coefficients
long long coefficients[51][51];
int current = 2;

// compute the binomial coefficients up to the given number. The coefficients
// are cached in the global set.
void computeCoefficients(int num)
{
    // if we've already gone past the input, we're done
    if(num <= current)
        return;

    // set the base coefficients
    coefficients[0][0] = 1;
    coefficients[1][0] = 1;

    // for each layer of the pyramid
    for(int i = current; i < num; ++i)
    {
        // get the midpoint, we only need to compute half
        double mid = ((i+1)/2.0 + 0.5);
        coefficients[i][0] = 1;

        // for each element in the row (up to the middle)
        for(int j = 1; j < (int)mid; ++j)
        {
            // compute this coefficient
            // from the two above it
            long long first = coefficients[i-1][j-1];
            long long second = coefficients[i-1][j];
            // if we're the middle element we need to look
            // back an element instead of up.
            if(j+1 == mid)
                second = coefficients[i-1][j-1];
            coefficients[i][j] = first + second;
        }
    }
    current = num;
}

// get the coefficient for N choose K
long long getCoefficient(int K, int N)
{
    return coefficients[N][min(K, N-K)];
}

int main()
{
    int numTests;
    int N;
    string next;
    string first;
    string second;
    cin >> numTests;
    // for each test
    for(int i = 0; i < numTests; ++i)
    {
        cin >> next;
        // get N
        int powerPos = next.find("^");
        string num = next.substr(powerPos+1, next.length()-powerPos-1);
        stringstream ss;
        ss << num;
        ss >> N;

        // get the variable names
        int plusPos = next.find("+");
        int brackPos = next.find(")");
        first = next.substr(1, plusPos-1);
        second = next.substr(plusPos+1, brackPos-plusPos-1);

        // compute the binomial coefficients needed
        computeCoefficients(N+1);

        // print out the result
        cout << "Case " << i+1 << ": ";
        for(int j = 0; j <= N; ++j)
        {
            long long coefficient = getCoefficient(j, N);
            // print coefficient
            if(coefficient > 1)
                cout << coefficient;
            int firstExponent = N-j;
            // print first variable
            if(firstExponent > 0)
            {
                // print coefficient multiplication
                if(coefficient > 1)
                    cout << "*";
                cout << first;
            }
            // print first exponent
            if(firstExponent > 1)
                cout << "^" << firstExponent;
            int secondExponent = j;
            // print second variable
            if(secondExponent > 0)
            {
                // print variable multiplication
                if(firstExponent > 0)
                    cout << "*";
                cout << second;
            }
            // print second exponent
            if(secondExponent > 1)
                cout << "^" << secondExponent;
            // add the plus sign if there are more elements
            if(j + 1 <= N)
                cout << "+";
        }
        cout << endl;
    }
}
