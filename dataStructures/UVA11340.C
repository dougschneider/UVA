#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    int numTests, numValues, value, numLines;
    long long totalValue;
    unsigned char c;
    string line;

    cin >> numTests;
    for(int i = 0; i < numTests; ++i)
    {
        cin >> numValues;

        vector<int> values(1000, 0);
        for(int j = 0; j < numValues; ++j)
        {
            // disregard new line
            getline(cin, line);

            // get character to store value of
            c = cin.get();
            cin >> value;
            values[c] = value;
        }

        totalValue = 0;
        cin >> numLines;
        for(int j = 0; j <= numLines; ++j)
        {
            getline(cin, line);

            for(int k = 0; k < line.size(); ++k)
            {
                c = line[k];
                totalValue += values[c];
            }
        }
        
        cout << totalValue / 100;
        cout << ".";
        cout << setfill('0') << setw(2);
        cout << totalValue % 100;
        cout << "$" << endl;
    }

    return 0;
}
