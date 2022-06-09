#include <iostream>

using namespace std;

const int M = 3;
const int N = 2;

int main()
{
    int A[M][N] = {
        {1, 4},
        {5, 9},
        {7, 10}
    };

    int B[N][M];

    //This transposes the matrix
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            B[i][j] = A[j][i];
        }
    }

    cout << "Original Matrix: " << endl;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    cout << "Transposed Matrix: " << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

}
