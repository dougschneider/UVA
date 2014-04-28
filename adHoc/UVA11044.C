#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int numTests, r, c;

    cin >> numTests;
    for(int i = 0; i < numTests; ++i)
    {
        cin >> r >> c;
        r -= 2;
        c -= 2;
        cout << (int) (ceil(r/3.0)*ceil(c/3.0)) << endl;
    }

    return 0;
}
