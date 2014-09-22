#include <iostream>

using namespace std;

int solve(int* parts, int length, int& i, int& j)
{
    int solution, sum;
    solution = 1;
    sum = 0;
    i = 0;
    int start, end;
    start = 0;
    for(int k = 0; k < length; ++k)
    {
        sum += parts[k];
        if(sum > solution)
        {
            end = k+1;
            i = start;
            j = end;
            solution = sum;
        }
        else if(sum == solution)
        {
            end = k+1;
            if(end-start == j-i)
            {
                if(start < i)
                {
                    i = start;
                    j = end;
                }
            }
            else if(end-start > j-i)
            {
                i = start;
                j = end;
            }
        }

        if(sum < 0)
        {
            sum = 0;
            start = k+1;
        }
    }

    return solution;
}

int main()
{
    int numTests, routeLength;
    cin >> numTests;
    for(int i = 0; i < numTests; ++i)
    {
        cin >> routeLength;

        int parts[routeLength-1];
        for(int j = 0; j < routeLength-1; ++j)
            cin >> parts[j];

        int start, end;
        start = end = 0;
        int result = solve(parts, routeLength-1, start, end);
        if(start == end)
            cout << "Route " << i+1 << " has no nice parts" << endl;
        else
            cout << "The nicest part of route " << i+1 << " is between stops " << start+1 << " and " << end+1 << endl;
    }

    return 0;
}
