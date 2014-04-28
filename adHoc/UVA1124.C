#include <iostream>

using namespace std;

int main()
{
    char ch;
    while(true)
    {
        cin.get(ch);
        if(!cin)
            break;
        cout << ch;
    }
    return 0;
}
