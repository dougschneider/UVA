// DATA STRUCTURES
// This code reads in the story and creates a set of unique words. The words
// are then printed out in lexicographic order. All strings of non-alphabetic
// characters are used to indicate the separation of two words.
#include <string>
#include <iostream>
#include <set>
#include <string.h>

using namespace std;

// convert the input string into lowercase
void toLowercase(char * input)
{
    // for each character
    for(int i = 0; i < strlen(input); ++i)
    {
        if(isupper(input[i]))
        {
            // replace it with it's lowercase equivalent
            input[i] = tolower(input[i]);
        }
    }
}

int main()
{
    set<string> words;
    char word[201];
    int current = 0;
    char next;
    // for each line of the story
    while(cin)
    {
        // don't skip whitespace while taking input
        cin >> noskipws >> next;
        // if it's a word character
        if(isalpha(next) && !isspace(next))
        {
            // update the current word
            word[current] = next;
            ++current;
        }
        else// it is a word separator
        {
            // end the word
            word[current] = '\0';
            // add valid words to the dictionary
            toLowercase(word);
            current = 0;
            if(strlen(word) == 0)
                continue;
            words.insert(string(word));
        }
    }
    // print the words in alphabetic order
    set<string>::iterator it = words.begin(), end = words.end();
    for(; it != end; ++it)
        cout << *it << endl;

    return 0;
}
