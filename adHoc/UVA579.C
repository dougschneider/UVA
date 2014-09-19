#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
    int hours, minutes;
    while(true)
    {
        scanf("%d:%d\n", &hours, &minutes);

        if(hours == 0 && minutes == 0)
            break;

        double h = hours + (minutes/60.0);

        double minuteAngle = minutes*(360.0/60.0);
        double hourAngle = h*(360.0/12.0);

        double result = hourAngle-minuteAngle;
        while(result > 0) result -= 360;
        while(result < 0) result += 360;
        result = min(abs(result),
                     abs(result-360));

        printf("%.3lf\n", result);
    }
    return 0;
}
