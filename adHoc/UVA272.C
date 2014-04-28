#include <iostream>

using namespace std;

int main()
{
    char ch;
    bool in = false;
    while(true)
    {
        cin.get(ch);
        if(!cin)
            break;

        if(ch == '"')
        {
            if(in)
                cout << "''";
            else
                cout << "``";
            in = !in;
        }
        else
        {
            cout << ch;
        }
    }

    return 0;
}
