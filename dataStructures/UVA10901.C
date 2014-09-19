#include <iostream>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

struct Car
{
    int id;
    int startTime;
    int arrivalTime;

    Car()
    {
    }

    Car(int id, int startTime) :
        id(id), startTime(startTime)
    {
    }
};

int main()
{
    int numTests;
    cin >> numTests;

    int capacity, travelTime, numCars;
    for(int k = 0; k < numTests; ++k)
    {
        cin >> capacity >> travelTime >> numCars;

        if(k > 0)
            cout << endl;

        queue<Car> leftBank;
        queue<Car> rightBank;
        int currentTime;
        bool atLeftBank;
        int currentCapacity;

        int startTime;
        string bank;
        for(int i = 0; i < numCars; ++i)
        {
            cin >> startTime >> bank;
            if(bank.find("left") != string::npos)
                leftBank.push(Car(i, startTime));
            else
                rightBank.push(Car(i, startTime));
        }

        vector<Car> arrivals(leftBank.size() + rightBank.size());
        int leftArrived = 0;
        int maxLeft = leftBank.size();
        int rightArrived = 0;
        currentTime = 0;
        atLeftBank = true;
        currentCapacity = 0;
        while(leftBank.size() > 0 || rightBank.size() > 0)
        {
            if(atLeftBank)
            {
                while(leftBank.size() > 0 &&
                        leftBank.front().startTime <= currentTime &&
                        currentCapacity < capacity)
                {
                    arrivals[leftBank.front().id] = leftBank.front();
                    arrivals[leftBank.front().id].arrivalTime = currentTime + travelTime;
                    leftArrived++;
                    currentCapacity++;
                    leftBank.pop();
                }

                if(currentCapacity > 0 ||
                        (rightBank.size() > 0 &&
                         rightBank.front().startTime <= currentTime))
                {
                    // switch banks
                    atLeftBank = false;
                    currentTime += travelTime;
                    currentCapacity = 0;
                }
                else
                {
                    if(leftBank.size() > 0)
                        currentTime = leftBank.front().startTime;
                    if(rightBank.size() > 0)
                        currentTime = min(currentTime, rightBank.front().startTime);
                }
            }
            else
            {
                while(rightBank.size() > 0 &&
                        rightBank.front().startTime <= currentTime &&
                        currentCapacity < capacity)
                {

                    arrivals[rightBank.front().id] = rightBank.front();
                    arrivals[rightBank.front().id].arrivalTime = currentTime + travelTime;
                    rightArrived++;
                    currentCapacity++;
                    rightBank.pop();
                }

                if(currentCapacity > 0 || leftBank.front().startTime <= currentTime)
                {
                    // switch banks
                    atLeftBank = true;
                    currentTime += travelTime;
                    currentCapacity = 0;
                }
                else
                {
                    if(leftBank.size() > 0)
                        currentTime = leftBank.front().startTime;
                    if(rightBank.size() > 0)
                        currentTime = min(currentTime, rightBank.front().startTime);
                }
            }
        }

        for(int i = 0; i < arrivals.size(); ++i)
            cout << arrivals[i].arrivalTime << endl;
    }

    return 0;
}
