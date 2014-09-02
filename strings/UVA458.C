#include <iostream>

using namespace std;

int main()
{
  char c;
  while(true)
  {
    cin.get(c);
    if(cin.eof())
      break;
    if(c != '\n')
      c -= 7;
    cout << c;
  }

  return 0;
}
