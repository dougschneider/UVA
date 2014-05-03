#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int numTests, numPeople, next;
    cin >> numTests;

    for(int i = 0; i < numTests; ++i)
    {
        int answer = -1;
        cin >> numPeople;
        for(int j = 0; j < numPeople; ++j)
        {
            cin >> next;
            answer = max(answer, next);
        }
        cout << "Case " << i+1 << ": " << answer << endl;
    }

    return 0;
}
