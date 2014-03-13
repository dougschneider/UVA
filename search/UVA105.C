// NONTRIVIAL
// SEARCH
// This algorithm makes a sweep through the buildings increasing
// the left boundary of the buildings as it goes. It gets the max height
// of all the buildings that the current index is within. When the maxHeight
// changes a new entry is added to the skyline vector containing the new height
// and the left bound that it changed at.
#include <iostream>
#include <vector>

using namespace std;

// a simple building representation to contain data
struct Building
{
    int left, right, height;
};

int main()
{
    vector<Building> buildings;
    int maxR = -1000000;
    // read in all of the buildings
    while(true)
    {
        Building b;
        cin >> b.left >> b.height >> b.right;
        if(!cin)
            break;
        buildings.push_back(b);
        // track the max R so we know when we're done later
        maxR = max(maxR, b.right);
    }

    vector<int> skyline;
    int l = buildings[0].left;
    int currentHeight = -1;
    while(true)
    {
        // if our left is over the max right, we're done
        if(l > maxR)
            break;

        // get the max height of the buildings at this point
        int maxHeight = 0;
        for(int i = 0; i < buildings.size(); ++i)
        {
            if(buildings[i].left <= l && l < buildings[i].right)
                maxHeight = max(maxHeight, buildings[i].height);
        }

        // if the max height has changed, add a new point to the
        // skyline
        if(maxHeight != currentHeight)
        {
            skyline.push_back(l);
            skyline.push_back(maxHeight);
            currentHeight = maxHeight;
        }
        // move left another step
        ++l;
    }

    // print the skyline
    for(int i = 0; i < skyline.size(); ++i)
    {
        cout << skyline[i];
        if(i+1 < skyline.size())
            cout << " ";
    }
    cout << endl;

    return 0;
}
