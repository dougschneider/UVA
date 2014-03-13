// DYNAMIC PROGRAMMING
// This algorithm finds the solution using dynamic
// programming with the following recurrence relation:
//      solve(subject-1, marks-i) for all i s.t. P <= i <= T
// a result of 1 is returned when subject == 0, and marks == 0,
// i.e. we've used all subjects and we're out of marks to allocate.
#include <iostream>

using namespace std;

typedef long long int lli;

// the table for use in DP
lli table[71][71];

int minPass, numSubjects, numMarks;

lli solve(int subject, int marks)
{
    // if the marks go below 0, this is an invalid configuration
    if(marks < 0)
        return 0;

    // if we are done all subjects and there are 0 marks remaining
    // we've found a solution
    if(subject == 0 && marks == 0)
        return 1;
    // if out of subjects and marks is not zero, not a valid solution
    else if(subject == 0)
        return 0;

    // if we have a result cached, use it
    if(table[subject][marks] != -1)
        return table[subject][marks];

    // sum up the result for using all possible marks for this subject
    lli result = 0;
    for(int i = minPass; i <= numMarks; ++i)
        result += solve(subject-1, marks-i);

    // cache and return the result
    table[subject][marks] = result;
    return result;
}

int main()
{
    int numTests;
    cin >> numTests;
    // consider each test case
    for(int i = 0; i < numTests; ++i)
    {
        cin >> numSubjects >> numMarks >> minPass;

        // initialize the DP table
        for(int j = 0; j < 71; ++j)
            for(int k = 0; k < 71; ++k)
                table[j][k] = -1;

        // print the solution
        cout << solve(numSubjects, numMarks) << endl;
    }

    return 0;
}
