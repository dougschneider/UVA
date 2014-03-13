// NONTRIVIAL
// STRINGS
// This program works by reading in the two sequences. It
// the concatanates the two sequences with a '#' between them.
// The suffix array of the concatanated string is then computed
// followed by the longest common prefix array for the suffix array.
// The list of longest common substrings is then computed using the
// list of longest common prefixes.
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

set<string> commonSubstrings;
int secondLength;

// The code encased in this comment is used to build the suffix array
// and is taken from Competitive Programming
// -------------------------------START----------------------------------------
#define MAXN 200010
int RA[MAXN], SA[MAXN], LCP[MAXN], *FC, *SC, step;
char S[MAXN], Q[MAXN];
int N;

bool cmp(int a, int b)
{
    if(step == -1 || FC[a] != FC[b])
        return FC[a] < FC[b];
    return FC[a+(1<<step)] < FC[b+(1<<step)];
}

void suffix_array(char *S, int n)
{
    for(int i = 0; i < n; ++i)
        RA[i] = S[SA[i] = i];
    for(FC = RA, SC = LCP, step = -1; (1<<step)<n; ++step)
    {
        sort(SA, SA+n, cmp);
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(i > 0 && cmp(SA[i-1], SA[i]))
                ++cnt;
            SC[SA[i]] = cnt;
        }
        if(cnt == n-1)
            break;
        swap(FC, SC);
    }
    for(int i = 0; i < n; ++i)
        RA[SA[i]] = i;
}
// -------------------------------END------------------------------------------

// compute the LCP from the suffix array
void computeLCP()
{
    // the first prefix has to be length 0
    LCP[0] = 0;
    // look at each suffix
    for(int i = 1; i < N; ++i)
    {
        // get the length of the common prefix
        int prefixLength = 0;
        while(S[SA[i] + prefixLength] == S[SA[i-1] + prefixLength])
            ++prefixLength;
        LCP[i] = prefixLength;
    }
}

// return true if the two strings are not both in the
// same string (at least one but not both contain the '#')
bool areInDifferentStrings(string first, string second)
{
    bool firstContains = first.find("#") != string::npos;
    bool secondContains = second.find("#") != string::npos;
    return (firstContains || secondContains) &&
           !(firstContains && secondContains);
}

// get the longest common substrings using the
// suffix array and the longest common prefixes
void getLongestCommonSubstrings()
{
    int longest = 1;
    // look at each prefix
    for(int i = 1; i < N; ++i)
    {
        int current = LCP[i];
        // if the prefix is long enough and the two suffixes occur
        // in the two different strings
        if(current >= longest &&
                areInDifferentStrings(string(S + SA[i-1]), string(S + SA[i])))
        {
            // update the longest common substrings
            if(current > longest)
                commonSubstrings.clear();
            commonSubstrings.insert(string(S + SA[i]).substr(0, LCP[i]));
            longest = current;
        }
    }
}

int main()
{
    string first, second;
    int testNum = 0;
    // look at all test cases
    while(true)
    {
        string sequence;
        commonSubstrings.clear();
        // read in the strings
        cin >> first;
        cin >> second;
        if(!cin)
            break;
        else if(testNum > 0)
            cout << endl;
        ++testNum;

        // concatanate the strings
        stringstream ss;
        ss << first << "#" << second;
        ss >> sequence;
        secondLength = second.length();
        N = sequence.length() + 1;
        memcpy(S, sequence.c_str(), N);
        S[N] = '\0';

        // create the suffix array
        suffix_array(S, N);
        // compute the longest common prefixes of the suffix array
        computeLCP();

        // get the longest common substrings
        getLongestCommonSubstrings();
        // print the result
        if(commonSubstrings.size() == 0)
        {
            cout << "No common sequence." << endl;
        }
        else
        {
            set<string>::iterator it = commonSubstrings.begin(), end = commonSubstrings.end();
            for(; it != end; ++it)
                cout << *it << endl;
        }
    }

    return 0;
}
