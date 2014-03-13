// NONTRIVIAL
// COMBINATORICS
// This algorithm works by first stepping the ball machine
// forward an entire day. It then looks at the tranformations
// made to each balls position, and finds the length of the
// permutation cycle for each ball position. Using the cycle
// lengths we find the lowest common multiple. This number
// is the number of days that the ball machine can go
// without repeating.
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

// a ball to be used in the ball machine
struct Ball
{
    Ball(int number) :
        number(number)
    {
    }

    int number;
};

// A ball machine able to simulate the position of
// all balls in an N ball machine
class BallMachine
{
public:

    // create a new ballmachine with the given
    // number of balls
    BallMachine(int numBalls)
    {
        for(int i = 1; i <= numBalls; ++i)
            ballQueue.push_back(Ball(i));
    }

    // step the ballmachine one minute forward
    void step()
    {
        // put the next ball in the minute
        minuteQueue.push_back(ballQueue.front());
        ballQueue.pop_front();
        // if the minute is at capacity
        if(minuteQueue.size() == 5)
        {
            // put the last ball on the five minute
            fiveMinuteQueue.push_back(minuteQueue.back());
            minuteQueue.pop_back();

            // shift all remaining balls to the queue
            for(int i = 0; i < 4; ++i)
            {
                ballQueue.push_back(minuteQueue.back());
                minuteQueue.pop_back();
            }
            assert(minuteQueue.size() == 0);
        }
        // if the five minute is at capacity
        if(fiveMinuteQueue.size() == 12)
        {
            // put the last ball on the hour
            hourQueue.push_back(fiveMinuteQueue.back());
            fiveMinuteQueue.pop_back();
            // shift all remaining balls to the queue
            for(int i = 0; i < 11; ++i)
            {
                ballQueue.push_back(fiveMinuteQueue.back());
                fiveMinuteQueue.pop_back();
            }
            assert(fiveMinuteQueue.size() == 0);
        }
        // if the hour is at capacity
        if(hourQueue.size() == 12)
        {
            // shift all balls onto the queue
            Ball last = hourQueue.back();
            hourQueue.pop_back();
            for(int i = 0; i < 11; ++i)
            {
                ballQueue.push_back(hourQueue.back());
                hourQueue.pop_back();
            }
            ballQueue.push_back(last);
            assert(hourQueue.size() == 0);
        }
    }

    // get the current time according to this ball machine
    string getTime()
    {
        stringstream ss;
        string result;
        ss << (hourQueue.size() + 1) << ":" <<
              (fiveMinuteQueue.size()/2) <<
              (minuteQueue.size() + 5*(fiveMinuteQueue.size()%2));
        ss >> result;
        return result;
    }

    list<Ball> ballQueue;

private:
    list<Ball> minuteQueue;
    list<Ball> fiveMinuteQueue;
    list<Ball> hourQueue;
};

// get the length for the cycle for the given ball number
// based on the transformations given.
// A cycle length is the number of transformations for a ball
// before it is back to its original position.
int getCycleLength(int ballNum, const vector<int>& transformations)
{
    int start = ballNum;
    int current = ballNum;
    int numTransformations = 0;
    while(true)
    {
        // transform the position, and count it
        current = (current + transformations[current]) % transformations.size();
        ++numTransformations;
        // if we've reached the beginning, we're done
        if(current == start)
            break;
    }
    return numTransformations;
}

// get the greatest common divisor of two numbers
// taken from Competitive Programming 3
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// get the lowest common multiple of two numbers
// taken from Competitive Programming 3
long long lcm(long long a, long long b)
{
    return a * (b / gcd(a, b));
}

// get the lowest common multiple over a vector of
// numbers
long long lcm_list(vector<int>& numbers)
{
    // if we're down to the last two, get their
    // lcm
    if(numbers.size() == 2)
        return lcm(numbers[0], numbers[1]);

    // remove the next number
    int next = numbers.back();
    numbers.pop_back();
    // recursively get the lcm
    return lcm(next, lcm_list(numbers));
}

int main()
{
    int numBalls;
    while(true)
    {
        cin >> numBalls;
        if(numBalls == 0)
            break;
        // create a BallMachine and make it
        // go forward a day
        BallMachine bm(numBalls);
        do
        {
            bm.step();
        }while(bm.getTime() != "1:00");
        do
        {
            bm.step();
        }while(bm.getTime() != "1:00");

        // find the transformations that were made to the balls
        vector<int> transformations(numBalls);
        int count = 0;
        list<Ball>::iterator it = bm.ballQueue.begin(),
                             end = bm.ballQueue.end();
        for(; it != end; ++it)
        {
            transformations[it->number-1] = ((++count + (numBalls - it->number))
                                             % numBalls);
        }

        // get the cycle lengths for each ball
        vector<int> cycleLengths(numBalls);
        for(int i = 0; i < numBalls; ++i)
            cycleLengths[i] = getCycleLength(i, transformations);
        // the solution is the lcm of all cycle lengths
        cout << numBalls << " balls cycle after " <<
                lcm_list(cycleLengths) << " days." << endl;
    }
}
