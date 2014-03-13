// GEOMETRY
// This algorithm works by first calculating the convex hull of the given tile.
// It then finds the area of both the tile and the convex hull. It then uses
// those to find the wasted space.
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

#define EPSILON 1E-10

/* The following (up to END CITATION) is taken from:
 * http://webdocs.cs.ualberta.ca/~contest/code/2D_Geometry/convex_hull.c
 */

struct Point
{
    int x, y;
};

Point *P0;

enum {CCW, CW, CL};

int cross_prod(Point *p1, Point *p2, Point *p0)
{
    double res, x1, x2, y1, y2;

    x1 = p1->x - p0->x;
    x2 = p2->x - p0->x;
    y1 = p1->y - p0->y;
    y2 = p2->y - p0->y;

    res = x1*y2 - x2*y1;

    if (fabs(res) < EPSILON)
        return CL;
    else if (res > 0.0)
        return CW;
    else
        return CCW;
}

int polar_cmp(Point *p1, Point *p2)
{
    int res;
    double d, x1, x2, y1, y2;

    res = cross_prod(p1, p2, P0);

    if (res == CW)
        return -1;
    else if (res == CCW)
        return 1;
    else {
        x1 = p1->x - P0->x;
        x2 = p2->x - P0->x;
        y1 = p1->y - P0->y;
        y2 = p2->y - P0->y;

        d = ((x1*x1) + (y1*y1)) - ((x2*x2) + (y2*y2));

        if (fabs(d) < EPSILON)
            return 0;
        else if (d < 0.0)
            return -1;
        else
            return 1;
    }
}

int convex_hull(Point *poly, int n, Point *hull)
{
    int i, min, h;

    if (n < 1)
        return 0;

    min = 0;
    P0 = &hull[0];
    *P0 = poly[0];

    for (i = 1; i < n; i++) {
        if ((poly[i].y < P0->y) || 
                ((poly[i].y == P0->y) && (poly[i].x < P0->x))) {
            min = i;
            *P0 = poly[i];
        }
    }

    poly[min] = poly[0];
    poly[0] = *P0;
    h = 1;

    if (n == 1)
        return h;

    qsort(poly+1, n-1, sizeof(poly[1]),
            (int (*)(const void *, const void *))polar_cmp);

    for (i = 1; i < n; i++) {
        if ((fabs(poly[i].x - hull[0].x) > EPSILON) ||   
                (fabs(poly[i].y - hull[0].y) > EPSILON))  {
            break;
        }
    }

    if (i == n)
        return h;

    hull[h++] = poly[i++];

    for ( ; i < n; i++) {
        while ((h > 1) &&
                (cross_prod(&poly[i], &hull[h-1], &hull[h-2]) != CCW)) {
            h--;
        }

        hull[h++] = poly[i];
    }

    return h;
}
/* END CITATION */

// find the area of the given simple polygon
// with the given number of points
double getArea(Point* poly, int size)
{
    double det = 0;
    // find the determinant
    for(int i = 0; i < size; ++i)
    {
        det += poly[i].x * poly[(i+1)%size].y;
        det -= poly[i].y * poly[(i+1)%size].x;
    }

    // return area
    return fabs(det/2.0);
}

int main()
{
    int numPoints;
    int count = 0;

    // initialize cout for the required precision
    cout << fixed;
    cout << setprecision(2);

    // consider each test case
    while(true)
    {
        cin >> numPoints;
        // break out on the last test case
        if(numPoints == 0)
            break;
        ++count;

        // read in the given tile
        Point points[numPoints];
        for(int i = 0; i < numPoints; ++i)
            cin >> points[i].x >> points[i].y;

        // calculate the tiles area
        double tileArea = getArea(points, numPoints);

        // find the convex hull of the tile
        Point hull[numPoints];
        int hullSize = convex_hull(points, numPoints, hull);

        // calculate the hulls area
        double hullArea = getArea(hull, hullSize);

        // get the percentage of wasted space
        double wasted = 100*(1.0-(tileArea/hullArea));

        // print the result
        cout << "Tile #" << count << endl;
        cout << "Wasted Space = " << wasted << " %" << endl;
        cout << endl;
    }
    return 0;
}
