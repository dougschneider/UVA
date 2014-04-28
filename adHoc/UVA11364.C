#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int numTests, num;
    cin >> numTests;

    for(int i = 0; i < numTests; ++i)
    {
        cin >> num;
        vector<int> numbers(num);
        for(int j = 0; j < num; ++j)
            cin >> numbers[j];
        sort(numbers.begin(), numbers.end());

        int total = 0;
        for(int j = 1; j < num; ++j)
        {
            total += abs(numbers[j] - numbers[j-1]);
        }

        if(num > 1)
            total += abs(numbers[num-1] - numbers[0]);

        cout << total << endl;
    }

    return 0;
}
