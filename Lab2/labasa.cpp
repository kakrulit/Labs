#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;

int getRandNum(int min, int max) {
    return min + rand() % (max - min + 1);
}

void fillMatrix(vector<vector<int>>& matrix, const int A, const int B)
{
    for (int i = 0; i < A; i++)
    {
        for (int j = 0; j < B; j++)
        {
            matrix[i][j] = getRandNum(10, 100);
        }
    }
}

void swapOddRows(vector<vector<int>>& matrix, const int start, const int end)
{
    for (int i = start; i < end / 2; i++)
    {
        if (i % 2 == 0)
        {
            swap(matrix[i], matrix[matrix.size() - i - 1]);
        }
    }
}

void test()
{
    vector<int> numThreads = { 1, 2, 4 };

    for (auto& el : numThreads)
    {
        int A = getRandNum(2000, 3000);
        int B = getRandNum(2000, 3000);

        vector<vector<int>> matrix(A, vector<int>(B, 0));

        fillMatrix(matrix, A, B);

        int chunkSize = A / el;

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < el; i++)
            {
                int start = i * chunkSize;
                int end = (i == el - 1) ? A : (i + 1) * chunkSize;
                swapOddRows(matrix, start, end);
            }
        }

        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

        chrono::duration<double> sec_diff = end - start;

        cout << "Time: " << sec_diff.count() << " sec." << endl;
    }
}

int main()
{
    srand(time(NULL));

    test();

    return 0;
}