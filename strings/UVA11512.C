// STRINGS
// This program finds the largest repeated substring in an input string, and
// the number of times it's repeated.  It does this by building a suffix array
// for the string.  It then goes through the array, suffix by suffix, and
// looking forward finds if a prefix of the suffix is repeated. It does this
// for each suffix. At the end we have the longest repeated substring.
//
// The code used to build the suffix array is copied from Competitive
// Programming (with minor modifications). This code is marked below.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

using namespace std;

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

// get the length of the longest repeating substring in
// the input S. The longest repeating substring is
// stored in the output parameter "repetition"
//
// If there are no repetitions, repetition is unchanged and 0
// is returned.
int getLongestRepetition(char* S, string & repetition)
{
    size_t longest = 0;
    map<string, int> repetitions;
    // for each suffix
    for(int i = 1; i < N; ++i)
    {
        string suffix = string(S + SA[i]);
        int suffixLength = suffix.length();
        char current;
        int max = N;
        // for each letter in the suffix
        for(int j = 0; j < suffixLength; ++j)
        {
            int count = 1;
            current = suffix[j];
            // for each remaining suffix;
            for(int k = i+1; k < max; ++k)
            {
                // we are still matching
                if(S[SA[k]+j] == current)
                {
                    ++count;
                }
                else// we're out of matching suffixes
                {
                    max = k;
                    break;
                }
            }
            // we have another equally long suffix
            if(count > 1 && j+1 == longest)
            {
                // update the count
                if(repetitions[string(suffix, 0, j+1)] < count)
                    repetitions[string(suffix, 0, j+1)] = count;
                longest = j+1;
            }
            // we have a new longest suffix
            else if(count > 1 && j+1 > longest)
            {
                // restart the list of words (since we have a new longest)
                repetitions.clear();
                longest = j+1;
                repetitions[string(suffix, 0, j+1)] = count;
            }
            // there are no more matching suffixes
            if(count == 1)
                break;
        }
    }

    // there are no repetitions
    if(repetitions.size() == 0)
        return 0;

    repetition = repetitions.begin()->first;
    return repetitions.begin()->second;
}

int main()
{
    int dummy;
    int numTests;
    dummy = scanf("%d\n", &numTests);
    string repetition;
    // look at each test case
    for(int i = 0; i < numTests; ++i)
    {
        // read in test and build suffix array
        dummy = scanf("%s\n", S);
        N = strlen(S) + 1;
        suffix_array(S, N);

        // get the length of the longest repetition and print it
        string result;
        int count = getLongestRepetition(S, result);
        if(result == "")
            cout << "No repetitions found!" << endl;
        else
            cout << result << " " << count << endl;
    }
    return 0;
}
