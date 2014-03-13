// NUMBER THEORY
// This algorithm works by recursively computing B^P mod M by splitting the
// problem in half and solving for each part to solve the final problem.
#include <cmath>
#include <iostream>

using namespace std;

typedef long long ll;

// Recursively solve B^P mod M
ll compute(ll B, ll P, ll M)
{
    // if P is 0, return 1 mod M
    if(P == 0)
        return 1 % M;
    // if P is odd, compute B^(P-1) mod M
    else if(P & 1 == 1)
        return (compute(B, P-1, M) * B) % M;
    // if P is two, compute B*B mod M
    else if(P == 2)
        return (B * B) % M;
    // split the problem in half and solve for the complete problem
    return (compute(B, P/2, M) * compute(B, P/2, M)) % M;
}

int main()
{
    ll B, P, M;
    // read input until EOF
    while(true)
    {
        cin >> B >> P >> M;
        // we've hit EOF so we're done
        if(!cin)
            break;
        cout << compute(B, P, M) << endl;
    }
}
