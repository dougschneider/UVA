#include <iostream>

using namespace std;

int main()
{
    int numPoints, divX, divY, x, y;

    while(true)
    {
        cin >> numPoints;
        if(numPoints == 0)
            break;

        cin >> divX >> divY;

        for(int i = 0; i < numPoints; ++i)
        {
            cin >> x >> y;
            string result;
            if(x == divX || y == divY)
            {
                cout << "divisa" << endl;
                continue;
            }

            if(y > divY)
                result = "N";
            else
                result = "S";

            if(x > divX)
                result += "E";
            else
                result += "O";

            cout << result << endl;
        }
    }
    return 0;
}
