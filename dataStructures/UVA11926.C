#include <bitset>
#include <iostream>

using namespace std;

bitset<1000000> future;

bool setOnce(int min, int max)
{
    bool conflict = false;
    for(int i = min; i < max; ++i)
    {
        conflict |= future.test(i);
        future.set(i);
    }
    return conflict;
}

bool setRepeating(int min, int max, int space)
{
    bool conflict = false;
    for(int i = min; i < 1000000; i += space)
    {
        for(int j = i; j < i + max - min && j < 1000000; ++j)
        {
            conflict |= future.test(j);
            future.set(j);
        }
    }
    return conflict;
}

int main()
{
    int numOnce, numRepeating;
    while(true)
    {
        cin >> numOnce >> numRepeating;

        if(numOnce == 0 && numRepeating == 0)
            break;
        future.reset();

        bool conflict = false;
        int min, max, space;
        for(int i = 0; i < numOnce; ++i)
        {
            cin >> min >> max;
            conflict |= setOnce(min, max);
        }

        for(int i = 0; i < numRepeating; ++i)
        {
            cin >> min >> max >> space;
            conflict |= setRepeating(min, max, space);
        }

        if(conflict)
            cout << "CONFLICT" << endl;
        else
            cout << "NO CONFLICT" << endl;
    }
    return 0;
}
