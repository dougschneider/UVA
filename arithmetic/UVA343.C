// NONTRIVIAL
// ARITHMETIC
// This algorithm works by first calculating the minimum
// base that can represent each input number. It than calculates
// the value for that base. If one of the numbers is greater than
// the other, we increment the base for the smaller number. Doing
// this will make that number larger on the next iteration. We proceed
// in this fashion unitl either both numbers are equal or one of the
// bases goes over 36.
#include <iostream>
#include <cctype>
#include <cmath>

using namespace std;

// get the number value of the given character
int getCharValue(char c)
{
    if(isalpha(c))
        return (c - 'A') + 10;
    else
        return c - '0';
}

// get the minimum base that we can use to represent
// the given number
int getMinBase(string num)
{
    // min base is 2, so start at 1
    int min = 1;
    // look through the characters to find the min base
    // we can represent the number with
    for(int i = 0; i < num.length(); ++i)
    {
        int base = getCharValue(num[i]);
        if(base > min)
            min = base;
    }

    // add one to the base to correct it
    return min + 1;
}

// get the value of the given number if evaluated
// in the given base.
int getValueInBase(string num, int base)
{
    int value = 0;
    // look at each character
    for(int i = 0; i < num.length(); ++i)
        // add the value of the next character in the given base
        value += getCharValue(num[num.length()-i-1])*pow(base, i);
    return value;
}

// get the bases for the two input numbers that result in the two
// numbers being equal. If no base in [2,36] results in their
// equivalence, b1 and b2 are populated with -1.
void getBases(string first, string second, int & b1, int & b2)
{
    // initialize their values (not equal so we enter the loop)
    int value1 = 1;
    int value2 = 2;
    // get the starting bases
    b1 = getMinBase(first);
    b2 = getMinBase(second);
    // iterate until the values are equal
    while(value1 != value2)
    {
        value1 = getValueInBase(first, b1);
        value2 = getValueInBase(second, b2);

        // increment the lower values base if the values arent equal
        if(value1 > value2)
            ++b2;
        else if(value1 < value2)
            ++b1;
        // if we hit the upper base, we're done
        if(b1 > 36 || b2 > 36)
        {
            b1 = -1;
            b2 = -1;
            break;
        }
    }
}

// print the output for the given numbers and bases
void printResult(string first, string second, int b1, int b2)
{
    // if they're both -1 then they can't ever be equal
    if(b1 == -1 && b2 == -1)
        cout << first << " is not equal to " << second <<
                " in any base 2..36" << endl;
    else// otherwise we've found a solution
        cout << first << " (base " << b1 << ") = " <<
                second << " (base " << b2 << ")" << endl;
}

int main()
{
    string first, second;
    int b1, b2;
    // iterate through all input
    while(true)
    {
        cin >> first >> second;
        // if we've hit EOF
        if(!cin)
            break;
        // get the bases that make the input numbers equivalent in value
        getBases(first, second, b1, b2);
        // print the result
        printResult(first, second, b1, b2);
    }
}
