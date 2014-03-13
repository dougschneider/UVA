// NONTRIVIAL
// SORTING
// This algorithm works by looking at each input number
// and converting them to normal form. Each normal form
// number is added to the index and the count for it's
// occurence is incremented. At the end numbers with
// more than one occurence are printed with their number
// of occurences. Or "No duplicates." is printed if there are
// no duplicate nubers.
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

map<string, int> index;

set<string> duplicates;

// static map for letter conversion
map<char, char> conversion = {{'A', '2'},
                              {'B', '2'},
                              {'C', '2'},
                              {'D', '3'},
                              {'E', '3'},
                              {'F', '3'},
                              {'G', '4'},
                              {'H', '4'},
                              {'I', '4'},
                              {'J', '5'},
                              {'K', '5'},
                              {'L', '5'},
                              {'M', '6'},
                              {'N', '6'},
                              {'O', '6'},
                              {'P', '7'},
                              {'R', '7'},
                              {'S', '7'},
                              {'T', '8'},
                              {'U', '8'},
                              {'V', '8'},
                              {'W', '9'},
                              {'X', '9'},
                              {'Y', '9'},
                              {'1', '1'},
                              {'2', '2'},
                              {'3', '3'},
                              {'4', '4'},
                              {'5', '5'},
                              {'6', '6'},
                              {'7', '7'},
                              {'8', '8'},
                              {'9', '9'},
                              {'0', '0'},
                              {'-', '\0'}};

// get the standard form of the input string
string getStandardForm(const string & number)
{
    char standardForm[9];
    int current = 0;
    // look at each letter
    for(int i = 0; i < number.length(); ++i)
    {
        // use the letter if it is valid
        char next = conversion[number[i]];
        if(next != 0)
        {
            standardForm[current++] = next;
            // insert the dash in the correct place
            if(current == 3)
                standardForm[current++] = '-';
        }
    }
    // add a null at the end
    standardForm[8] = '\0';
    return string(standardForm);
}

// print the result of the current test
void printResult()
{
    // if there are no dupicates; print so and exit
    if(duplicates.size() == 0)
    {
        cout << "No duplicates." << endl;
        return;
    }

    // print each duplicate
    set<string>::iterator it = duplicates.begin(), end = duplicates.end();
    for(; it != end; ++it)
        cout << *it << " " << index[*it] << endl;
}

// process the given number of phone numbers
void processNumbers(int num)
{
    // clear global data
    index.clear();
    duplicates.clear();

    string number;
    // read in the blank line
    getline(cin, number);
    // read in each number
    for(int i = 0; i < num; ++i)
    {
        getline(cin, number);
        // get the number in standard form
        number = getStandardForm(number);
        // create a new count if the number is new
        if(index.find(number) == index.end())
            index[number] = 0;
        // increment the count
        index[number] += 1;
        // if the count has hit 2, add it to the duplicates list
        if(index[number] == 2)
            duplicates.insert(number);
    }

    // print the result
    printResult();
}

int main()
{
    int numTests, numNumbers;
    cin >> numTests;
    // for each test
    for(int i = 0; i < numTests; ++i)
    {
        cin >> numNumbers;

        // process the numbers and print the result
        processNumbers(numNumbers);

        // print a blank line as a divider between tests
        if(i + 1 < numTests)
            cout << endl;
    }
    return 0;
}
