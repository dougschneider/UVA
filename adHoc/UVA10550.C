#include <iostream>

using namespace std;

double num = 40, deg = 360;

int main()
{
    int a, b, c, d;
    while(true)
    {
        int total = deg*3;
        cin >> a >> b >> c >> d;
        if(a == 0 && b == 0 && c == 0 && d == 0)
            break;
        if(b > a)
            total += ((40 - abs(b-a))/num)*deg;
        else
            total += (abs(b-a)/num)*deg;
        if(c < b)
            total += ((40 - abs(c-b))/num)*deg;
        else
            total += (abs(c-b)/num)*deg;
        if(d > c)
            total += ((40 - abs(d-c))/num)*deg;
        else
            total += (abs(d-c)/num)*deg;
        cout << total << endl;
    }

    return 0;
}
