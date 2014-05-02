#include <iostream>

using namespace std;

int main()
{
    int numPeople, budget, numHotels, numWeekends, price, capacity;
    while(true)
    {
        cin >> numPeople >> budget >> numHotels >> numWeekends;
        if(!cin)
            break;

        int minPrice = -1;

        for(int j = 0; j < numHotels; ++j)
        {
            cin >> price;
            capacity = -1;
            for(int i = 0; i < numWeekends; ++i)
            {
                int c;
                cin >> c;
                if(c > capacity)
                    capacity = c;
            }

            if(capacity == -1 || capacity < numPeople || price*numPeople > budget)
                continue;

            if(price < minPrice || minPrice == -1)
                minPrice = price;
        }

        if(minPrice == -1)
            cout << "stay home";
        else
            cout << minPrice*numPeople;
        cout << endl;

    }
    return 0;
}
