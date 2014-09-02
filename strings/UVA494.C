#include <iostream>

using namespace std;

int count;
bool inWord;

void printAndReset()
{
  cout << count << endl;
  count = 0;
  inWord = false;
}

bool isLetter(char c)
{
  return (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z');
}

int main()
{
  char c;
  count = 0;
  inWord = false;
  while(true)
  {
    cin.get(c);
    if(cin.eof())
      break;
    if(c == '\n')
    {
      printAndReset();
    }
    if(isLetter(c) && !inWord)
    {
      count++;
      inWord = true;
    }
    else if(!isLetter(c))
    {
      inWord = false;
    }
  }
  return 0;
}
