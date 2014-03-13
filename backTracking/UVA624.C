// BACKTRACKING
// This algorithm recursively tries all permutations of the tracks pruning
// branches when we go over the total amount of track time available.
// The string of cds is stored when a new best time is encountered.
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int numTracks, N;

int solve(int current, int time, vector<int>& times, string& best)
{
    // if over the time limit, invalid state
    if(time > N)
        return -1;

    // base case, return 0 time
    if(current == numTracks)
        return 0;

    int max = 0;
    int next = 0;
    string s;
    // solve the recursive case including this track
    next = solve(current+1, time+times[current], times, s);
    if(next != -1)
    {
        // add the time of this track
        next += times[current];

        // if the result is good, use it
        if(next > max)
        {
            stringstream ss;
            ss << times[current] << " " << s;
            getline(ss, best);
            max = next;
        }
    }

    // solve the recursive case not including this track
    next = solve(current+1, time, times, s);

    // if the result is good, use it
    if(next > max)
    {
        max = next;
        best = s;
    }

    return max;
}

int main()
{
    // consider each test case
    while(true)
    {
        cin >> N >> numTracks;
        // done on EOF
        if(!cin)
            break;

        // read in all the tracks
        vector<int> times(numTracks);
        for(int i = 0; i < numTracks; ++i)
            cin >> times[i];

        // compute the result
        string result;
        int sum = solve(0, 0, times, result);

        // print the result
        cout << result << "sum:" << sum << endl;
    }
    return 0;
}
