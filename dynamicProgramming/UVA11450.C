#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> garments;

int cache[201][21];

void clearCache()
{
    for(int i = 0; i < 201; ++i)
        for(int j = 0; j < 21; ++j)
            cache[i][j] = -2;
}

int solve(int money, int current)
{
    if(current < 0)
        return 0;

    if(cache[money][current] != -2)
        return cache[money][current];

    int best = -1;
    int next;
    int cost;
    int result;
    for(int i = 0; i < garments[current].size(); ++i)
    {
        cost = garments[current][i];
        if(money - cost < 0)
            continue;

        result = solve(money - cost, current - 1); 
        if(result == -1)
            continue;

        next = result + cost;
        best = max(best, next);
    }

    cache[money][current] = best;
    return best;
}

int main()
{
    int numTests, money, numGarments, numModels, cost;

    cin >> numTests;
    for(int i = 0; i < numTests; ++i)
    {
        clearCache();

        cin >> money >> numGarments;
        garments = vector<vector<int>>(numGarments);
        for(int j = 0; j < numGarments; ++j)
        {
            cin >> numModels;
            garments[j] = vector<int>(numModels);
            for(int k = 0; k < numModels; ++k)
                cin >> garments[j][k];
        }

        int result = solve(money, numGarments-1);
        if(result == -1)
            cout << "no solution" << endl;
        else
            cout << result << endl;
    }
    return 0;
}
