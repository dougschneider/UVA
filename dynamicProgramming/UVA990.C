// DYNAMIC PROGRAMMING
// This algorithm uses dynamic programming over the time remaining, and over
// each chest. For each chest we choose the best of two recursive calls the
// first being to use the current chest, and the remaining time is reduced.
// The second is to skip the current chest, and the remaining time remains the
// same. The result for each call is cached in a DP table in the form of a
// vector of treasures that are the solution to that subproblem.
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// a treasure used for easy storage in this problem
struct Treasure
{
    int depth, value;
};

// a sum functor for use with accumulate to sum the values
// of a list of treasures
struct SumValue
{
    int operator()(int first, Treasure& second)
    {
        return first + second.value;
    }
};

Treasure treasure[30];

int weight;
// the DP table
vector<Treasure> table[30][1001];

// return the set of treasures that solve the problem for
// the given treasure and time
vector<Treasure> solve(int current, int time)
{
    // if we're done and the time is not less than 0
    // return base case (empty list)
    if(current < 0 && time >= 0)
        return vector<Treasure>();

    // if time goes below 0, return invalid state
    if(time < 0)
    {
        vector<Treasure> result;
        Treasure blank;
        blank.value = -1;
        result.push_back(blank);
        return result;
    }

    // if we have the result cached, use it
    if(table[current][time].size() == 0 || table[current][time][0].value != -1)
        return table[current][time];

    // find the result for using this chest
    vector<Treasure> t1 = solve(current-1,
                                time-(3*weight*treasure[current].depth));
    t1.push_back(treasure[current]);
    int v1 = accumulate(t1.begin(), t1.end(), 0, SumValue());

    // if using this chest leads to an invalid state, we can't use it
    if(t1.size() > 0 && t1[0].value == -1)
    {
        // make this option undesirable
        v1 = 0;
        t1.clear();
    }

    // find the result for not using this chest
    vector<Treasure> t2 = solve(current-1, time);
    int v2 = accumulate(t2.begin(), t2.end(), 0, SumValue());
    vector<Treasure>& larger = t1;

    // use the better result
    if(v2 > v1)
        larger = t2;

    // cache and return the result
    table[current][time] = larger;
    return larger;
}

int main()
{
    int numTreasures, time;

    bool first = true;
    // consider each test case
    while(true)
    {
        cin >> time >> weight >> numTreasures;
        // break out at EOF
        if(!cin)
            break;

        // print blank lines between test cases
        if(!first)
            cout << endl;
        first = false;

        // initialize the dp table
        Treasure blank;
        blank.value = -1;
        for(int i = 0; i < 30; ++i)
        {
            for(int j = 0; j < 1001; ++j)
            {
                table[i][j].clear();
                table[i][j].push_back(blank);
            }
        }

        // read in the treasures
        for(int i = 0; i < numTreasures; ++i)
            cin >> treasure[i].depth >> treasure[i].value;

        // get the result
        vector<Treasure> result = solve(numTreasures-1, time);
        int v = accumulate(result.begin(), result.end(), 0, SumValue());

        // print the result
        cout << v << endl;
        cout << result.size() << endl;
        for(int i = 0; i < result.size(); ++i)
            cout << result[i].depth << " " << result[i].value << endl;
    }
    return 0;
}
