#include <iostream>
#include <vector>

using namespace std;

int main()
{
    while(true)
    {
        vector<int> numbers;

        int next;
        cin >> next;
        if(!cin)
            break;
        while(true)
        {
            if(next == -999999)
                break;

            numbers.push_back(next);
            cin >> next;
        }

    }
}
