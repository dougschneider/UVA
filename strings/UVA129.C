// NONTRIVIAL
// STRINGS
// this solution works by producing new dictionary ordered
// words and checking them for whether they are easy or hard
// in the order they're generated. The nth hardest word is
// then output according to the problems specifications.
//
// The words are generated using a backtracking algorithm.
// This algorithm is similar to imagining exploring a tree in
// a depth first search manner where branches are cut when we
// find a path that can't possibly contain the answer.
#include <cstdio>
#include <iostream>

using namespace std;

char first = 'A';
char last;
int n, L;

string current;
int idx = 0;

// generate the next possible string in
// the dictionary. used indicates whether the
// last string was hard or not.
string getNextString(bool used)
{
    // if we didn't use the last string we need
    // to correct the duplicate characters
    if(!used)
    {
        // increment the last character
        current[idx] += 1;

        // if we go outside the limit we need to propogate
        // the change back
        if(current[idx] > last)
        {
            current = current.substr(0, idx--);
            current[idx] += 1;
            // loop until the change is fully propogated back
            for(int i = idx; i > 0; --i)
            {
                // if we're outside the bound of letters
                if(current[i] > last)
                {
                    // we remove the last character to maintain dictionary order
                    current = current.substr(0, i);
                    // propogate the update backwards
                    current[i-1] += 1;
                }
                // otherwise the change has been fully propogated
                else
                {
                    break;
                }
            }
        }
    }
    // otherwise we can just add another character
    else
    {
        current.push_back(first);
        ++idx;
    }
    return current;
}

// return true if the given string is easy as defined by the problem
// otherwise return false
bool isEasy(string input)
{
    // look at each possible size of repetition
    for(int i = 1; i <= input.length()/2; ++i)
    {
        // look at each possible starting location
        for(int k = 0; k < i; ++k)
        {
            string first = input.substr(k, i);
            string second;
            // look at at each pattern offset
            for(int j = i + k; j <= input.length()-i; j += i)
            {
                // if there is a repetition return true
                second = input.substr(j, i);
                if(first == second)
                    return true;
                first = second;
            }
        }
    }
    // there are no repetitions, return false.
    return false;
}

// find the nth hard sequence
string calculateHardSequence()
{
    int current = 0;
    int wasHard = true;
    string next;
    // loop until we've found it
    while(true)
    {
        // get the next dictionary word to check
        next = getNextString(wasHard);
        wasHard = !isEasy(next);
        // keep track of the current hard sequence
        if(wasHard)
            ++current;
        // we've found it, break out
        if(current == n)
            break;
    }
    return next;
}

// format print the result
void print(const string & result)
{
    for(int i = 0; i < result.length(); ++i)
    {
        cout << result[i];

        // add new lines every 16 groups
        if((i+1) % (16*4) == 0 && i+1 < result.length())
        {
            cout << endl;
        }
        // start a new group every 4 letters
        else if((i + 1) % 4 == 0 && i+1 < result.length())
        {
            cout << " ";
        }
    }
    cout << endl;
    cout << result.length() << endl;
}

int main()
{
    int dummy;
    // loop until we're out of input
    while(true)
    {
        current = "";
        idx = -1;
        dummy = scanf("%d %d", &n, &L);
        if(n == 0 && L == 0)
            break;
        last = first + L-1;
        print(calculateHardSequence());
    }
}
