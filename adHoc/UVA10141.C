#include <iostream>

using namespace std;

int main()
{
    int numReqs, numProps, m;
    double p;
    string requirement, n;
    int count = 0;
    while(true)
    {
        cin >> numReqs >> numProps;
        if(numReqs == 0 && numProps == 0)
            break;

        // blank line between outputs
        if(count > 0)
            cout << endl;

        // discard requirement names
        getline(cin, requirement);
        for(int i = 0; i < numReqs; ++i)
            getline(cin, requirement);

        string name;
        double price = 100000000;
        int metRequirements = -1;
        for(int i = 0; i < numProps; ++i)
        {
            getline(cin, n);
            cin >> p >> m;

            // discard requirement names
            getline(cin, requirement);
            for(int j = 0; j < m; ++j)
                getline(cin, requirement);
    
            if(metRequirements == -1 || m >= metRequirements)
            {
                if(m > metRequirements || p < price)
                {
                    metRequirements = m;
                    price = p;
                    name = n;
                }
            }
        }

        cout << "RFP #" << ++count << endl;
        cout << name << endl;
    }

    return 0;
}
