#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

struct Lemming
{
    int power;

    Lemming()
    {
    }

    Lemming(int power) :
        power(power)
    {
    }

    bool operator<(const Lemming& other) const
    {
        return this->power < other.power;
    }
};

struct Battlefield
{
    Lemming blue;
    Lemming green;

    void clear()
    {
        blue.power = 0;
        green.power = 0;
    }

    void fight()
    {
        int tmp = blue.power - green.power;
        green.power -= blue.power;
        blue.power = tmp;
    }
};

void readLemmings(int numLemmings, vector<Lemming>& lemmings)
{
    int power;
    for(int i = 0; i < numLemmings; ++i)
    {
        cin >> power;
        lemmings.push_back(Lemming(power));
    }
}

int main()
{
    int numTests, numBattlefields, numGreenLemmings, numBlueLemmings;

    cin >> numTests;
    for(int i = 0; i < numTests; ++i)
    {
        cin >> numBattlefields >> numGreenLemmings >> numBlueLemmings;

        if(i > 0)
            cout << endl;

        vector<Lemming> greenLemmings;
        vector<Lemming> blueLemmings;

        readLemmings(numGreenLemmings, greenLemmings);
        readLemmings(numBlueLemmings, blueLemmings);

        vector<Battlefield> fields(numBattlefields);
        while(greenLemmings.size() > 0 && blueLemmings.size() > 0)
        {
            sort(greenLemmings.begin(), greenLemmings.end());
            reverse(greenLemmings.begin(), greenLemmings.end());
            sort(blueLemmings.begin(), blueLemmings.end());
            reverse(blueLemmings.begin(), blueLemmings.end());
            vector<Lemming>::iterator git = greenLemmings.begin();
            vector<Lemming>::iterator bit = blueLemmings.begin();

            vector<Lemming>::iterator it = greenLemmings.begin();

            for(int i = 0; i < numBattlefields; ++i)
            {
                fields[i].clear();

                if(greenLemmings.size() > 0)
                {
                    fields[i].green = *git;
                    greenLemmings.erase(git);
                }

                if(blueLemmings.size() > 0)
                {
                    fields[i].blue = *bit;
                    blueLemmings.erase(bit);
                }
            }

            for(int i = 0; i < numBattlefields; ++i)
            {
                fields[i].fight();
                if(fields[i].green.power > 0)
                    greenLemmings.push_back(fields[i].green);
                if(fields[i].blue.power > 0)
                    blueLemmings.push_back(fields[i].blue);
            }
        }

        if(greenLemmings.size() > 0)
        {
            cout << "green wins" << endl;
            vector<Lemming>::iterator it = greenLemmings.begin();
            for(; it != greenLemmings.end(); ++it)
                cout << it->power << endl;
        }
        else if(blueLemmings.size() > 0)
        {
            cout << "blue wins" << endl;
            vector<Lemming>::iterator it = blueLemmings.begin();
            for(; it != blueLemmings.end(); ++it)
                cout << it->power << endl;
        }
        else
        {
            cout << "green and blue died" << endl;
        }
    }

    return 0;
}
