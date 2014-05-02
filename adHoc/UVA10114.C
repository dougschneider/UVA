#include <iostream>
#include <vector>

using namespace std;

struct Record
{
    int start;
    double depreciation;
};

int main()
{
    int numMonths, numRecords;
    double downPayment, loan, value;
    while(true)
    {
        cin >> numMonths >> downPayment >> loan >> numRecords;
        if(numMonths < 0)
            break;

        // read in the depreciation records
        vector<Record> records(numRecords);
        for(int i = 0; i < numRecords; ++i)
            cin >> records[i].start >> records[i].depreciation;

        int currentRecord = 0;

        double value = loan;
        value += downPayment;
        value *= (1-records[currentRecord].depreciation);

        double monthlyPayment = loan/numMonths;

        // perform depreciation and count number of months
        int count = 1;
        while(true)
        {
            if(loan < value)
                break;

            if(currentRecord+1 < records.size() && 
                    count >= records[currentRecord+1].start)
                ++currentRecord;

            loan -= monthlyPayment;
            value *= (1-records[currentRecord].depreciation);

            ++count;
        }

        --count;

        // print the result
        cout << count << " month";
        if(count != 1)
            cout << "s";
        cout << endl;
    }
    return 0;
}
