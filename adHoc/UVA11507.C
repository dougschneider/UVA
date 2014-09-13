#include <iostream>

#define PX 1
#define NX -1
#define PZ 2
#define NZ -2
#define PY 3
#define NY -3
#define NO 0

using namespace std;

int getBend()
{
    string bend;
    cin >> bend;
    if(bend.compare("+y") == 0)
        return PY;
    else if(bend.compare("-y") == 0)
        return NY;
    else if(bend.compare("+z") == 0)
        return PZ;
    else if(bend.compare("-z") == 0)
        return NZ;
    else if(bend.compare("No") == 0)
        return NO;
}

void handleBend(int bend, int& direction)
{
    if(bend == NO)
        return;

    if(direction == PX)
        direction = bend;
    else if(direction == NX)
        direction = -bend;
    else if(direction == PY)
    {
        if(bend == PZ || bend == NZ)
            direction = PY;
        else if(bend == PY)
            direction = NX;
        else if(bend == NY)
            direction = PX;
    }
    else if(direction == NY)
    {
        if(bend == PZ || bend == NZ)
            direction = NY;
        else if(bend == PY)
            direction = PX;
        else if(bend = NY)
            direction = NX;
    }
    else if(direction == PZ)
    {
        if(bend == PY || bend == NY)
            direction = PZ;
        else if(bend == PZ)
            direction = NX;
        else if(bend == NZ)
            direction = PX;
    }
    else if(direction == NZ)
    {
        if(bend == PY || bend == NY)
            direction = NZ;
        else if(bend == PZ)
            direction = PX;
        else if(bend == NZ)
            direction = NX;
    }
}

void outputDirection(int bend)
{
    if(bend == PX)
        cout << "+x" << endl;
    else if(bend == NX)
        cout << "-x" << endl;
    else if(bend == PY)
        cout << "+y" << endl;
    else if(bend == NY)
        cout << "-y" << endl;
    else if(bend == PZ)
        cout << "+z" << endl;
    else if(bend == NZ)
        cout << "-z" << endl;
}

int main()
{
    int length;
    while(true)
    {
        cin >> length;
        if(length == 0)
            break;

        int direction = PX;

        for(int i = 0; i < length-1; ++i)
        {
            int bend = getBend();
            handleBend(bend, direction);
        }

        outputDirection(direction);
    }
    return 0;
}
