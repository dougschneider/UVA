// NONTRIVIAL
// STRINGS
// This program reads input lines and checks to see if they're mirrored,
// palindromes, or some combination of both. It does this by checking
// each property individually. And then printing output that matches the
// strings property.
#include <iostream>
#include <string.h>

using namespace std;

// return true if the input is a palindrome,
// otherwise false.
bool isPalindrome(char* line)
{
    // look at each character
    int start = 0, end = strlen(line)-1;
    while(start < end)
    {
        // if that character isn't on the other
        // side of the pivot, return false
        if(line[start] != line[end])
            return false;
        // update the indices
        ++start;
        --end;
    }
    // if we get here, it must be a palindrome
    return true;
}

// return the reverse (mirrored) character of
// the input.
char reverse(char c)
{
    switch(c)
    {
        case 'A': return 'A';
        case 'E': return '3';
        case 'H': return 'H';
        case 'I': return 'I';
        case 'J': return 'L';
        case 'L': return 'J';
        case 'M': return 'M';
        case 'O': return 'O';
        case 'S': return '2';
        case 'T': return 'T';
        case 'U': return 'U';
        case 'V': return 'V';
        case 'W': return 'W';
        case 'X': return 'X';
        case 'Y': return 'Y';
        case 'Z': return '5';
        case '1': return '1';
        case '2': return 'S';
        case '3': return 'E';
        case '5': return 'Z';
        case '8': return '8';
        default: return 0;
    }
}

// return true if the input line is a mirrored string
// otherwise false.
bool isMirrored(char* line)
{
    // look at each character
    int start = 0, end = strlen(line)-1;
    while(start <= end)
    {
        // get the mirrored character
        char reversed = reverse(line[start]);
        // if the character has no mirror or breaks the mirror property
        // return false
        if(reversed == 0 || reversed != line[end])
            return false;
        // update the start and end indices
        ++start;
        --end;
    }
    // if we get here, it must be a mirrored string
    return true;
}

int main()
{
    // output whether each input line is a palidrome, mirrored string,
    // mirrored palindrome, or neither.
    char line[21];
    while(cin >> line)
    {
        bool palindrome = isPalindrome(line);
        bool mirrored = isMirrored(line);
        if(palindrome && mirrored)
            cout << line << " -- is a mirrored palindrome." << endl << endl;
        else if(mirrored)
            cout << line << " -- is a mirrored string." << endl << endl;
        else if(palindrome)
            cout << line << " -- is a regular palindrome." << endl << endl;
        else
            cout << line << " -- is not a palindrome." << endl << endl;
    }
}
