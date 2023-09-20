#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

int getRandNum(int min, int max) {
	return min + rand() % (max - min + 1);
}

void fillMatrix(vector<vector<int>> &matrix, const int A, const int B)
{
	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < B; j++)
		{
			matrix[i][j] = getRandNum(10, 100);
		}
	}
}

void showMatrix(vector<vector<int>>& matrix, const int A, const int B)
{
	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < B; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void swapOddRows(vector<vector<int>> &matrix, const int A)
{
	for (int i = 0; i < A / 2; i++)
	{
		if (i % 2 == 0)
		{
			swap(matrix[i], matrix[A - i - 1]);
		}
	}
}

void fourThreadTest()
{
	int A = getRandNum(2000, 3000);
	int B = getRandNum(2000, 3000);

	vector<vector<int>> matrix(A, vector<int>(B, 0));

	fillMatrix(matrix, A, B);

	vector<thread> threads(4);

	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 4; i++)
	{
		threads[i] = std::thread(swapOddRows, std::ref(matrix), A / 4);
	}

	for (int i = 0; i < 4; ++i)
	{
		threads[i].join();
	}

	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

	chrono::duration<double> sec_diff = end - start;

	cout << "Time: " << sec_diff.count() << " sec." << endl;
}

void twoThreadTest()
{
	int A = getRandNum(2000, 3000);
	int B = getRandNum(2000, 3000);

	vector<vector<int>> matrix(A, vector<int>(B, 0));

	fillMatrix(matrix, A, B);

	vector<thread> threads(2);

	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 2; i++)
	{
		threads[i] = std::thread(swapOddRows, std::ref(matrix), A / 2);
	}

	for (int i = 0; i < 2; ++i)
	{
		threads[i].join();
	}

	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

	chrono::duration<double> sec_diff = end - start;

	cout << "Time: " << sec_diff.count() << " sec." << endl;
}

void oneThreadTest()
{
	int A = getRandNum(2000, 3000);
	int B = getRandNum(2000, 3000);

	vector<vector<int>> matrix(A, vector<int>(B, 0));

	fillMatrix(matrix, A, B);

	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	swapOddRows(matrix, A);
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> milli_diff = end - start;

	cout <<"Time: " << milli_diff.count() << " milli sec." << endl;
}

int main()
{
	srand(time(NULL));

	oneThreadTest();
	twoThreadTest();
	fourThreadTest();

	return 0;
}