#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int num;
    while(true)
    {
        cin >> num;
        if(!cin)
            break;
        
        if(num == 1)
        {
            cin >> num;
            cout << "Jolly" << endl;
            continue;
        }

        bool jumps[num-1];
        for(int i = 0; i < num-1; ++i)
            jumps[i] = false;

        int current, next;
        cin >> current;
        for(int i = 1; i < num; ++i)
        {
            cin >> next;
            if(abs(next-current) <= num-1)
                jumps[(int)abs(next-current)-1] = true;
            current = next;
        }

        bool jolly = true;
        for(int i = 0; i < num-1; ++i)
            jolly &= jumps[i];

        if(jolly)
            cout << "Jolly" << endl;
        else
            cout << "Not jolly" << endl;
    }
    return 0;
}
