// NONTRIVIAL
// ARITHMETIC
// This algorithm works by reading in the numbers and converting them first
// from their input base to base 10. And then from base 10 to the output base.
//
// Conversion to base 10 is done by multipling each index in the number by the
// input base to the power of the index.
//
// Conversion to the output base is performed by taking the number modulo the
// output base. The result is the next digit to add the the number. The number
// is then divided by the output base, and this process is repeated until the
// number becomes zero.
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

// get the number value of the given character
int getCharValue(char c)
{
    if(isalpha(c))
        return (c - 'A') + 10;
    else
        return c - '0';
}

// conver the given number of a character
char toChar(int num)
{
    // if > 9, convert it to a letter
    if(num > 9)
        return (num - 10) + 'A';
    else// convert it to the number character it represents
        return '0' + num;
}

// get the value of the given number in the given base
int getValue(string num, int base)
{
    int value = 0;
    // iterate through the indices multiplying the value at
    // each index by the base to the power of the index
    for(int i = 0; i < num.length(); ++i)
        value += getCharValue(num[num.length()-i-1])*pow(base, i);
    return value;
}

// conver the given number (in base 10) to its
// number in the given base
string toBase(int num, int base)
{
    string value = "";
    int lower;
    while(true)
    {
        // get the next digit
        lower = num%base;
        // reduce the number
        num /= base;
        // add the next digit to the string
        value.push_back(toChar(lower));
        // once we hit zero we're done
        if(num == 0)
            break;
    }
    // return the reversed string
    return string(value.rbegin(), value.rend());
}

int main()
{
    string num;
    int fromBase, to;
    // read stdin until we're out of input
    while(true)
    {
        cin >> num >> fromBase >> to;
        // exit at EOF
        if(!cin)
            break;
        // get the converted string
        string result = toBase(getValue(num, fromBase), to);
        // if the result is too long, print error
        if(result.length() > 7)
            printf("  ERROR\n");
        else// else print the padded result
            printf("%7s\n", result.c_str());
    }
}
