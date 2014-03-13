// NONTRIVIAL
// NUMBER THEORY
// This program computs the 1500th ugly number by starting with the first ugly
// number(1). It then multiplies this number by each 2, 3, 5 and adds the
// lowest number to the list. This is done iteratively multiplying 2, 3, or 5
// by the lowest ugly number that they have each been multiplied by, and adding
// each number to the list when they are the lowest of the three.
#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<int> uglies;
set<int> addedUglies;

int main()
{
    uglies.push_back(1);
    addedUglies.insert(1);

    int count = 1;
    int i2 = 2;
    int i2_ugly = 0;
    int i3 = 3;
    int i3_ugly = 0;
    int i5 = 5;
    int i5_ugly = 0;
    while(true)
    {
        // if i2 is the lowest
        if(i2 <= i3 && i2 <= i5)
        {
            // have we already added this number to the list?
            if(addedUglies.find(i2) == addedUglies.end())
            {
                addedUglies.insert(i2);
                uglies.push_back(i2);
                ++count;
            }
            // get the next iteration
            ++i2_ugly;
            i2 = 2  * uglies[i2_ugly];
        }
        // if i3 is the lowest
        else if(i3 <= i2 && i3 <= i5)
        {
            // have we already added this number to the list?
            if(addedUglies.find(i3) == addedUglies.end())
            {
                addedUglies.insert(i3);
                uglies.push_back(i3);
                ++count;
            }
            // get the next iteration
            ++i3_ugly;
            i3 = 3  * uglies[i3_ugly];
        }
        // if i5 is the lowest
        else if(i5 <= i2 && i5 <= i3)
        {
            // have we already added this number to the list?
            if(addedUglies.find(i5) == addedUglies.end())
            {
                addedUglies.insert(i5);
                uglies.push_back(i5);
                ++count;
            }
            // get the next iteration
            ++i5_ugly;
            i5 = 5  * uglies[i5_ugly];
        }
        // if we've found the 1500th number, break out
        if(count > 1499)
            break;
    }
    // output the answer
    cout << "The 1500'th ugly number is " << uglies[1499] << "." << endl;
    return 0;
}
