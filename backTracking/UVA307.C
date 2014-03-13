#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool r_find(vector<int>& sticks, int next, int length, int curSize, int used)
{
    if(used == sticks.size())
        return curSize == 0;

    for(int i = next; i < sticks.size(); ++i)
    {
        int current = sticks[i];

        int nextSize = curSize + current;
        if(current == -1 || nextSize > length)
            continue;
        if(nextSize == length)
            nextSize = 0;

        sticks[i] = -1;
        if(r_find(sticks, i+1, length, nextSize, used+1))
            return true;
        sticks[i] = current;
    }

    return false;
}

int getLength(vector<int>& sticks, int max)
{
    for(int i = 1; i < max; ++i)
    {
        if(max % i != 0)
            continue;

        if(r_find(sticks, 0, i, 0, 0))
            return i;
    }
    throw exception();
}

int main()
{
    int numSticks;
    while(true)
    {
        cin >> numSticks;
        if(numSticks == 0)
            break;

        int l;
        vector<int> sticks;
        for(int i = 0; i < numSticks; ++i)
        {
            cin >> l;
            sticks.push_back(l);
        }

        int num = accumulate(sticks.begin(), sticks.end(), 0); 
        cout << getLength(sticks, num) << endl;
    }
    return 0;
}
