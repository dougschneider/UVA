// NONTRIVIAL
// BACKTRACKING
// This algorithm works by looking at each order in turn
// and recursively finding the result when the order is included
// and when it isn't included. We prune branches of the search
// when any of the stations would be over capacity by accepting
// an order. After the search, the max result is printed.
#include <iostream>

using namespace std;

struct Order
{
    int start, destination, numPassengers;

    // get the value of this order (total ticket cost)
    int getValue()
    {
        return (destination-start)*numPassengers;
    }
};

int maxEarning, maxCapacity, numOrders, lastStation;
Order orders[22];
int passengers[8];

void dfs(int current, int sum)
{
    // if any of the stations go over capacity, invalid solution
    bool valid = true;
    for(int i = 0; i < lastStation; ++i)
    {
        if(passengers[i] > maxCapacity)
            valid = false;
    }
    if(!valid)
        return;

    // if we're at the end of the orders, update the max
    if(current == numOrders)
    {
        // if current earning is more than the max, update it
        if(sum > maxEarning)
            maxEarning = sum;
        return;
    }
    
    // update the capacity at each station when using this order
    for(int i = orders[current].start; i < orders[current].destination; ++i)
        passengers[i] += orders[current].numPassengers;
    // get the result, using this order
    dfs(current+1, sum+orders[current].getValue());

    // update the capacity at each station when NOT using this order
    for(int i = orders[current].start; i < orders[current].destination; ++i)
        passengers[i] -= orders[current].numPassengers;
    // get the result, NOT using this order
    dfs(current+1, sum);
}

int main()
{
    // look at each test case
    while(true)
    {
        // initialize the max earning for the question
        maxEarning = 0;

        // read in the question data, break out at the end
        cin >> maxCapacity >> lastStation >> numOrders;
        if(maxCapacity == 0 && lastStation == 0 && numOrders == 0)
            break;

        // read in all of the orders
        for(int i = 0; i < numOrders; ++i)
            cin >> orders[i].start >> orders[i].destination >> orders[i].numPassengers;

        // get the max earning
        dfs(0, 0);
        // print the max earning
        cout << maxEarning << endl;
    }

    return 0;
}
