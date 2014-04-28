#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int numTests;
    cin >> numTests;

    int salaries[3];

    for(int i = 0; i < numTests; ++i)
    {
        cin >> salaries[0] >> salaries[1] >> salaries[2];
        sort(salaries, salaries+3);
        cout << "Case " << i+1 << ": " << salaries[1] << endl;
    }

    return 0;
}
