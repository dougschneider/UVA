// GEOMETRY
// This algorithm uses trigonometry to calculate the distance the laser travels
// as it bounces from wall to wall. The final distance is adjusted if the last
// bounce is cut short due to running out of hallway.  The exit is calculated
// based on where the laser lands. Then Pythagoras' theorem uses the length of
// the hallway and the exit location to calculate the length of the direct
// path. The ratio of these is printed out.
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int numTests;
double L, W, theta, E, A, B;

double getADistance()
{
    double hyp, adj;
    double curL = 0, result = 0;
    double opp = W;
    bool even = false;

    // go back and forth while there is more hallway to go
    while(curL < L)
    {
        // get the travelled distance
        hyp = fabs(opp/sin(theta));
        result += hyp;

        // get the length of hallway used
        adj = fabs(opp/tan(theta));
        curL += adj;

        // keep track of the wall we've bounced off
        even = !even;
    }

    // remove the last bit of length to adjust for running
    // out of hallway
    result -= hyp;
    curL -= adj;

    // calculate the new distance to add
    double ratio = ((L-curL)/adj);
    result += hyp*ratio;

    // calculate where the exit is
    E = opp*ratio;
    E = even ? E : W - E;

    // return the result
    return result;
}

// get the direct distance this must be called after
// E (the location of the exit) has been calculated
double getBDistance()
{
    // direct line from Jake to the exit
    return pow(pow(E, 2.0) + pow(L, 2.0), 0.5);
}

// convert the degrees to radians
double inline toRadians(int degrees)
{
    return degrees*(M_PI/180);
}

int main()
{
    cin >> numTests;

    // initialize the output for the correct decimal precision
    cout << fixed;
    cout << setprecision(3);

    // for each test case
    for(int i = 0; i < numTests; ++i)
    {
        // read in this case
        cin >> L >> W >> theta;
        theta = toRadians(theta);

        // handle edge case, theta == 0
        if(theta == 0)
            cout << 1.000 << endl;
        else // print the result
            cout << getADistance()/getBDistance() << endl;
    }

    return 0;
}
