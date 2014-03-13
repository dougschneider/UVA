// NONTRIVIAL
// SORTING
// This program gets the best order of jobs to complete
// by using STL's sort algorithm. And implementing the
// operator< for a job where first the cost of waiting
// for the other job is compared, and then they are
// compared numerically (based on job id).
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// an implementation of a Job. This is used to
// implement easy sorting of Jobs.
struct Job
{
    int num, time, fine;

    // return true if the cost of delaying this Job
    // is less than delaying the other job. If it is a tie
    // they are ordered based on their ID's. Larger ID comes
    // first.
    bool operator<(const Job& other) const
    {
        // calculate cost of delaying first job
        int firstCost = this->fine*other.time;
        // calculate cost of delaying second job
        int secondCost = other.fine*this->time;
        if(firstCost < secondCost)
        {
            // if the first job will cost less than
            // it's better to do the second job first
            return true;
        }
        else if(firstCost == secondCost)
        {
            // if it's a tie, compare their id's
            return this->num > other.num;
        }
        return false;

    }
};

int main()
{
    int dummy;
    int numTests, numJobs, time, fine;
    dummy = scanf("%d\n\n", &numTests);
    // for each test
    for(int i = 0; i < numTests; ++i)
    {
        vector<Job> jobs;
        dummy = scanf("%d\n", &numJobs);

        // for each job
        for(int j = 0; j < numJobs; ++j)
        {
            dummy = scanf("%d %d\n", &time, &fine);
            // create a job and add it to the list
            Job job;
            job.num = j+1;
            job.time = time;
            job.fine = fine;
            // add the job to the list
            jobs.push_back(job);
        }

        // sort the jobs
        vector<Job>::iterator first = jobs.begin(), last = jobs.end();
        sort(first, last);

        // output the job ids in order to complete
        vector<Job>::reverse_iterator it = jobs.rbegin(), end = jobs.rend();
        for(; it != end; ++it)
        {
            // add spaces between each job id
            if(it != jobs.rbegin())
                cout << " ";
            cout << it->num;
        }
        cout << endl;

        // if there are more tests, add an extra blank line
        if(i+1 < numTests)
        {
            dummy = scanf("\n");
            cout << endl;
        }
    }
    return 0;
}
