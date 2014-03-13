// NONTRIVIAL
// SORTING
// This algorithm works by creating a set of
// words to ignore. It then reads in each title.
// It looks at each word, if it isn't ignored, it
// adds that title to an index with the current word.
// The titles are lowercased and keywords uppercased
// to match the required output
#include <cctype>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// set of words to ignore
set<string> ignoreWords;

// index mapping a keyword to a set of titles containing it
map<string, vector<string>> index;

// read in the ignored words up to the "::" and
// store them all for later.
void readIgnoreWords()
{
    string word;
    // read until the "::"
    while(true)
    {
        cin >> word;
        if(word == "::")
            break;
        // add the word to the ignore set
        ignoreWords.insert(word);
    }
}

// add the given title to the index with the given keyword.
void addTitle(const string & title, const string & keyword)
{
    if(index.find(keyword) == index.end())
        index[keyword] = vector<string>();
    index[keyword].push_back(title);
}

// process the given title adding all possibilities to
// the index.
void processTitle(const string & title)
{
    stringstream ss;
    ss << title;
    string next;
    string soFar = "";
    // look at each word in the title
    while(true)
    {
        ss >> next;
        // stop when we're done
        if(!ss)
            break;

        // store the remaining words
        string remaining;
        getline(ss, remaining);
        ss.flush();
        ss.clear();
        ss << remaining;

        // update the title so far
        if(soFar != "")
            soFar += " ";
        // if we shouldn't ignore this word, process it
        if(ignoreWords.find(next) == ignoreWords.end())
        {
            string upperNext(next);
            // make the key uppercase
            transform(upperNext.begin(), upperNext.end(), upperNext.begin(), ::toupper);
            // add the title to the index
            addTitle(soFar + upperNext + remaining, next);
        }
        // update the title so far
        soFar += next;
    }
}

// read and process the titles to create the index
void processTitles()
{
    string title;
    // read until we're out of input
    while(true)
    {
        getline(cin, title);
        if(!cin)
            break;
        // make the title lowercase
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        // add it to the index
        processTitle(title);
    }
}

void printIndex()
{
    map<string, vector<string>>::iterator it = index.begin(), end = index.end();
    // look at each key
    for(; it != end; ++it)
    {
        // print each word for this key
        for(int i = 0; i < it->second.size(); ++i)
            cout << it->second[i] << endl;
    }
}

int main()
{
    readIgnoreWords();
    processTitles();
    printIndex();
    return 0;
}
