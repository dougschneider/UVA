#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int numCoaches;

    while(true)
    {
        cin >> numCoaches;
        if(numCoaches == 0)
            break;

        vector<int> permutation(numCoaches);
        while(true)
        {
            stack<int> track, station;
            for(int i = 0; i < numCoaches; ++i)
            {
                track.push(numCoaches-i);
                cin >> permutation[i];
                if(permutation[i] == 0)
                    break;
            }
            if(permutation[0] == 0)
            {
                cout << endl;
                break;
            }

            bool possible = true;
            for(int j = 0; j < permutation.size();)
            {
                if(station.size() > 0 && station.top() == permutation[j])
                {
                    station.pop();
                    ++j;
                    continue;
                }
                else if(track.size() > 0 && track.top() == permutation[j])
                {
                    track.pop();
                    ++j;
                    continue;
                }
                else if(track.size() > 0)
                {
                    station.push(track.top());
                    track.pop();
                }
                else
                {
                    possible = false;
                    break;
                }
            }

            if(possible)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }
    return 0;
}
