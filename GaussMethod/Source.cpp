#include <iostream>
#include <math.h>
#include <string>
using namespace std;
const int N = 10;

double A[N][N] = { 0 };
double B[N] = { 0 };
double X[N] = { 0 };
int positionsX[N];
int n = 4;

void SetDefaultPositionsX()
{
	for (int i = 0; i < n; i++)
	{
		positionsX[i] = i;
	}
}
void InputMatrix_A()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "x" << i << j << ">> ";
			cin >> A[i][j];
		}
	}
}
void InputMatrix_B()
{
	for (int i = 0; i < n; i++)
	{
		cout << "b" << i << ">> ";
		cin >> B[i];
	}
}
void OutputMatrix(string message = "")
{
	cout << endl;
	cout << message << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout.width(7);
			cout.precision(4);
			cout << A[i][j];
		}
		cout << " | " << B[i];
		cout << endl;
	}
	cout << endl;
}
pair<int, int> FintMaxElement(int startWith)
{
	pair<int, int> max = { startWith, startWith };

	for (int i = startWith; i < n; i++)
	{
		for (int j = startWith; j < n; j++)
		{
			if (abs(A[i][j]) > abs(A[max.first][max.second])) { max.first = i; max.second = j; }
		}
	}
	return max;
}
void SwapColumns(int from, int to)
{
	for (int i = 0; i < n; i++) { swap(A[i][from], A[i][to]); }
}
void SwapRows(int from, int to)
{
	for (int i = 0; i < n; i++) { swap(A[from][i], A[to][i]); }
	swap(B[from], B[to]);
}
void MoveMaxElementToUp(int iteration)
{
	pair<int, int> maxElementPos = FintMaxElement(iteration);

	cout << "-------------------------------------------------" << endl;
	OutputMatrix(to_string(iteration) + " iteration");
	cout << "max: element = " << A[maxElementPos.first][maxElementPos.second] << "  x = " << maxElementPos.first << "   y = " << maxElementPos.second;

	if (maxElementPos.first != iteration)
	{
		SwapRows(maxElementPos.first, iteration);
		maxElementPos.first = iteration;
	}
	if (maxElementPos.second != iteration)
	{
		SwapColumns(maxElementPos.second, iteration);
		swap(positionsX[maxElementPos.second], positionsX[iteration]);
		maxElementPos.second = iteration;
	}

	OutputMatrix();
	cout << "-------------------------------------------------" << endl;
}
void GaussElimination()
{
	double W = 0.0;
	for (int i = 0; i < n - 1; i++)
	{
		MoveMaxElementToUp(i);
		for (int j = i + 1; j < n; j++)
		{
			W = A[j][i] / A[i][i];
			B[j] -= B[i] * W;
			for (int z = 0; z < n; z++)
			{
				A[j][z] -= A[i][z] * W;
			}
		}
	}
}
void CalculateX()
{
	for (int i = n - 1; i >= 0; i--)
	{
		double temp = B[i];
		for (int j = i; j < n; j++)
		{
			temp -= A[i][j] * X[positionsX[j]];
		}

		X[positionsX[i]] = temp / A[i][i];
		X[positionsX[i]] = round(X[positionsX[i]] * 1000) / 1000;
	}
}

void main()
{
	cout << "n: ";
	cin >> n;

	cout << "Enter A:" << endl;
	InputMatrix_A();

	cout << endl;

	cout << "Enter B:" << endl;
	InputMatrix_B();

	SetDefaultPositionsX();

	OutputMatrix("Sourse:");

	GaussElimination();

	OutputMatrix("Result:");

	CalculateX();

	for (int i = 0; i < n; i++)
	{
		cout << "x[" << i << "] = " << X[i] << endl;
	}

	system("pause");
}