#include <iostream>

using namespace std;

struct Matrix
{
    int size;
    char** matrix;

    Matrix(int size):
        size(size)
    {
        matrix = new char*[size];
        for(int i = 0; i < size; ++i)
            matrix[i] = new char[size];
    }

    ~Matrix()
    {
        for(int i = 0; i < size; ++i)
            delete [] matrix[i];
        delete [] matrix;
    }

    void readIn()
    {
        string tmp;
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
                cin >> matrix[i][j];
            getline(cin, tmp);
        }
    }

    void print()
    {
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
                cout << matrix[i][j];
            cout << endl;
        }
    }

    bool matches(int i, int j, const Matrix& smaller)
    {
        for(int k = 0; k < smaller.size; ++k)
            for(int l = 0; l < smaller.size; ++l)
                if(smaller.matrix[k][l] != matrix[i+k][j+l])
                    return false;
        return true;
    }

    int countOccurences(const Matrix& smaller)
    {
        int count = 0;
        for(int i = 0; i < size - smaller.size + 1; ++i)
            for(int j = 0; j < size - smaller.size + 1; ++j)
                if(matches(i, j, smaller))
                    ++count;
        return count;
    }

    Matrix* rotateCW()
    {
        Matrix* next = new Matrix(size);
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
                next->matrix[j][size-1-i] = matrix[i][j];
        return next;
    }
};

int main()
{
    int first, second;
    while(true)
    {
        cin >> first >> second;
        if(first == 0 && second == 0)
            break;

        Matrix* big = new Matrix(first);
        Matrix* small = new Matrix(second);
        Matrix* tmp = 0;

        big->readIn();
        small->readIn();
        cout << big->countOccurences(*small) << " ";
        tmp = small->rotateCW();
        delete small;
        small = tmp;
        cout << big->countOccurences(*small) << " ";
        tmp = small->rotateCW();
        delete small;
        small = tmp;
        cout << big->countOccurences(*small) << " ";
        tmp = small->rotateCW();
        delete small;
        small = tmp;
        cout << big->countOccurences(*small);
        tmp = small->rotateCW();
        small = tmp;
        cout << endl;
        delete small;
        delete big;
    }
    return 0;
}
