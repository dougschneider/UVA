#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    int numTests;
    ll a, b;

    cin >> numTests;
    for(int i = 0; i < numTests; ++i)
    {
        cin >> a >> b;
        if(a > b)
            cout << ">";
        else if(a < b)
            cout << "<";
        else
            cout << "=";
        cout << endl;
    }
    
    return 0;
}
