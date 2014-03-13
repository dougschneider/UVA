// NONTRIVIAL
// ARITHMETIC
// This algorithm works by dividing the numerator and denominator and saving
// the observation of each remainder during the division. Once we see a
// remainder more than once we know we've seen the longest repeating decimal
// sequence. We then compute the result using the index that the remainder
// began at, and the index that we found the remainder again.
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// divide the given numerator and denominator to find the first repeating set
// of decimals
void divide(int num, int den)
{
    // get the digit before the decimal and add the decimal
    stringstream result;
    result << (int)num/den << ".";
    // get the initial remainder
    int remainder = (num%den)*10;
    // map of remainders to their position
    map<int, int> remainders;
    remainders[remainder] = 1;
    int idx = 2;
    // loop until there's a duplicate remainder(repeating decimal sequence
    while(true)
    {
        // add the next digit
        result << remainder/den;
        // get the new remainder
        remainder = (remainder%den)*10;
        // if we've seen this remainder before, we're done
        if(remainders.find(remainder) != remainders.end())
            break;
        // save the remainder and its position
        remainders[remainder] = idx++;
    }

    // build the result
    string r;
    result >> r;
    // cut it off if it's too long
    if(r.length() > 52)
    {
        r = r.substr(0, 52);
        r += "...";
    }
    // add the brackets are the start and end
    r.insert(remainders[remainder]+1, "(");
    r += ")";
    // print the result
    cout << num << "/" << den << " = " << r << endl;
    cout << "   " << idx-remainders[remainder] <<
            " = number of digits in repeating cycle" << endl;
}

int main()
{
    int num, den;
    while(true)
    {
        cin >> num >> den;
        // we're done at EOF
        if(!cin)
            break;
        // get the result
        divide(num, den);
        // print new line for each test
        cout << endl;
    }
    return 0;
}
