#include <iostream>
using namespace std;
const int N = 2;
double f1(double x, double y)
{
	return (x * x + y * y * y - 4);
}
double derXf1(double x, double y)
{
	return (2 * x);
}
double derYf1(double x, double y)
{
	return (3 * y * y);
}
double f2(double x, double y)
{
	return (x / y - 2);
}
double derXf2(double x, double y)
{
	return 1 / y;
}
double derYf2(double x, double y)
{
	return (-x / (y * y));
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int a = 1, i, j, k;
	double eps = pow(10, -8), x0[N] = { 2, 1 }, x1[N], W[N][N], opW[N][N], F[N], max, detW, d1, d2, f;
	cout << " eps = " << eps << endl;
	do
	{
		cout << endl << " Шаг " << a << ":\n F(x" << a - 1 << "):" << endl;
		F[0] = f1(x0[0], x0[1]);
		F[1] = f2(x0[0], x0[1]);

		for (i = 0; i < N; i++)
			cout << " " << F[i] << endl;
		cout << endl << " W(x" << a - 1 << "):" << endl;

		W[0][0] = derXf1(x0[0], x0[1]);
		W[0][1] = derYf1(x0[0], x0[1]);
		W[1][0] = derXf2(x0[0], x0[1]);
		W[1][1] = derYf2(x0[0], x0[1]);

		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
				cout << " " << W[i][j] << "\t";
			cout << endl;
		}
		d1 = 1;
		d2 = 1;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (i == j)
					d1 *= W[i][j];
				else
					d2 *= W[i][j];
			}
		}
		detW = d1 - d2;
		cout << endl << " detW = " << detW << ", W^(-1)(x" << a - 1 << "):" << endl;

		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				opW[i][j] = pow(-1, (i + j)) * (1 / detW);
				if (i == j)
					opW[i][j] *= W[N - 1 - j][N - 1 - i];
				else
					opW[i][j] *= W[i][j];
				cout << " " << opW[i][j] << "\t";
			}
			cout << endl;
		}

		cout << endl << " X[" << a << "]:" << endl;
		for (i = 0; i < N; i++)
		{
			f = x0[i];
			for (j = 0; j < N; j++)
				f -= F[j] * opW[i][j];
			x1[i] = f;
			cout << " " << x1[i] << endl;
		}

		max = 0;
		for (i = 0; i < N; i++)
		{
			x0[i] = abs(x1[i] - x0[i]);
			if (max < x0[i])
				max = x0[i];
			x0[i] = x1[i];
		}
		cout << "_______________" << endl;
		a++;
	} while (!(max < eps));
	return 0;
}