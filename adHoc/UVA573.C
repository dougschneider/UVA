#include <iostream>

using namespace std;

int main()
{
    int wellHeight, slide;
    double fatigue, climb;

    while(true)
    {
        cin >> wellHeight >> climb >> slide >> fatigue;
        if(wellHeight == 0)
            break;

        fatigue = (fatigue/100.0)*climb;

        int day = 0;
        double height = 0;
        while(height >= 0)
        {
            if(climb > 0)
                height += climb;
            ++day;
            if(height > wellHeight)
                break;
            height -= slide;
            climb -= fatigue;
        }

        if(height > 0)
            cout << "success";
        else
            cout << "failure";
        cout << " on day " << day << endl;
    }

    return 0;
}
