// NONTRIVIAL
// COMBINATORICS
// This algorithm simply computes pascals triangle.
// Only half of the triangle is computed to save space
// and computation. BigInt's are required to prevent
// overflow.
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// BigInteger class. Only capable of
// addition.
struct BigInt
{
    // Make a BigInt of 0
    BigInt()
    {
        digits.push_back(0);
    }

    BigInt(const BigInt& rhs) :
        digits(rhs.digits)
    {
    }

    // get the number of digits in this number
    int size() const
    {
        return digits.size();
    }

    // return true if this numbers is larger
    // than 10^60
    bool isOverLimit() const
    {
        return digits.size() > 60;
    }

    // add the given BigInt to this one
    void add(const BigInt& other)
    {
        int remainder = 0;
        // for each digit
        for(int i = 0; i < max(this->size(), other.size()); ++i)
        {
            // if we're over this numbers limit
            // add a new digit
            if(i >= this->size())
                digits.push_back(0);
            // get the next digit to use in addition
            int num = i < other.size() ? other.digits[i] : 0;
            num += digits[i];
            num += remainder;
            // set the digit and the new remainder
            digits[i] = num % 10;
            remainder = num/10;
        }
        // if there's still a remainder add it to the front
        if(remainder > 0)
            digits.push_back(remainder);
    }

    // print this number, no new line on the end
    void print() const
    {
        for(int i = digits.size()-1; i >= 0; --i)
            cout << digits[i];
    }

    vector<int> digits;
};

void computePascalsTriangle()
{
    BigInt coefficients[300][300];
    // set the base numbers
    BigInt one;
    one.digits[0] = 1;
    coefficients[0][0] = one;
    coefficients[1][0] = one;
    cout << "1" << endl;
    cout << "1 1" << endl;

    // for each layer of the triangle
    int layer = 2;
    while(true)
    {
        assert(layer < 300);
        // get the midpoint, we only need to compute half
        double mid = ((layer+1)/2.0 + 0.5);
        // the first column is always one
        coefficients[layer][0] = one;

        bool overlimit;
        // for each element in the row (up to the middle)
        for(int j = 1; j < (int)mid; ++j)
        {
            // get the dependent numbers
            BigInt& first = coefficients[layer-1][j-1];
            BigInt& second = coefficients[layer-1][j];
            if(j+1 == mid)
                second = coefficients[layer-1][j-1];
            // make the new number
            BigInt next(first);
            next.add(second);
            overlimit |= next.isOverLimit();
            coefficients[layer][j] = next;
        }

        // print the row of numbers (first half)
        for(int i = 0; i < (int)mid; ++i)
        {
            coefficients[layer][i].print();
            cout << " ";
        }
        // print the row of numbers (second half)
        int i = mid != ((double)((int)mid)) ? mid-1 : mid-2;
        for(; i >= 0; --i)
        {
            coefficients[layer][i].print();
            if(i-1 >= 0)
                cout << " ";
        }
        cout << endl;

        // if we've reached the limit we're done
        if(overlimit)
            break;
        ++layer;
    }
}

int main()
{
    computePascalsTriangle();

    return 0;
}
