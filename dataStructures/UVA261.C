// NONTRIVIAL
// DATA STRUCTURES
// this program finds whether each input string has the windows property. If
// not it says where the first character breaking the conditions for the window
// property occurs.  It does this by iterating through each possible window
// property size and sliding it down the input line until either there are two
// many different windows, or the end of the string is reached. This decides
// whether the line has the windows property.
#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

// get whether the input text has the window property or not.
bool hasWindowProperty(string test)
{
    if(test.length() == 0)
        return false;

    // try each window size
    set<string> windows;
    for(int k = 1; k <= test.length(); ++k)
    {
        // slide the window down the length of the input
        for(int i = 0; i <= test.length()-k; ++i)
        {
            // add the window to the set of windows
            windows.insert(test.substr(i, k));
        }
        // if there are too many windows we don't have the property
        if(windows.size() > k+1)
            return false;
        // empty the set of windows for the next window size
        windows.clear();
    }
    // we have the window property
    return true;
}

// get the output text for the given input
string getResult(string test)
{
    // if it has the propert we're done
    if(hasWindowProperty(test))
        return "YES";

    // find where the property is broken
    ostringstream ss;
    ss << "NO:";
    // try each substring
    for(int i = 1; i <= test.length(); ++i)
    {
        // if it doesn't have the property we've found where the property is
        // broken
        if(!hasWindowProperty(test.substr(0, i)))
        {
            ss << i;
            return ss.str();
        }
    }
}

int main()
{
    char line[102];
    while(cin)
    {
        cin.getline(line, 102);
        string test(line);
        // ignore empty lines
        if(test == "")
            continue;
        if(cin.eof())
            break;
        cout << getResult(test) << endl;
    }

    return 0;
}
