#include <iostream>

using namespace std;

int main()
{
    int matrix[100][100];
    int N;
    while(cin >> N)
    {
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                cin >> matrix[i][j];
                if(i > 0) matrix[i][j] += matrix[i-1][j];
                if(j > 0) matrix[i][j] += matrix[i][j-1];
                if(i > 0 && j > 0) matrix[i][j] -= matrix[i-1][j-1];
            }
        }

        long int best = -999999999;
        long int current;
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                for(int a = i; a < N; ++a)
                {
                    for(int b = j; b < N; ++b)
                    {
                        current = matrix[a][b];
                        if(j > 0) current -= matrix[a][j-1];
                        if(i > 0) current -= matrix[i-1][b];
                        if(i > 0 && j > 0) current += matrix[i-1][j-1];
                        best = max(best, current);
                    }
                }
            }
        }

        cout << best << endl;
    }
    return 0;
}
