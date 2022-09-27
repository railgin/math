#include <iostream>
#include <vector> 
#include <string>
using namespace std;

class matrix
{
private:
	int n;
	int m;
	double** arr = new double* [n]; //new возвращает указатель с адресом на выделенную память, массив из n указателей типа double

public:
	void ArrayAllocate(double** arr)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = new double[m];
		}
	}

	void ArrayInit(double** arr)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				arr[i][j] = 0;
			}
		}
	}

	matrix(int dim1 = 0, int dim2 = 0) : n(dim1), m(dim2)
	{
		ArrayAllocate(arr);
		ArrayInit(arr);
		cout << "Here worked default constr" << endl;
	}

	/*matrix(int dim1, int dim2, bool one = true) : n(dim1), m(dim2)
	{
		ArrayCreate(arr);
		ArrayInit(arr);
		cout << "Here worked constr" << endl;
	}*/

	matrix(const matrix& matr) : n(matr.n), m(matr.m)
	{
		this->arr = new double* [n];
		for (int i = 0; i < n; i++)
		{
			this->arr[i] = new double[m];
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				this->arr[i][j] = matr.arr[i][j];
			}
		}

		cout << "Copy constructor worked here!\n";
	}

	~matrix()
	{
		for (int i = 0; i < n; i++)
		{
			delete[] arr[i];
		}

		delete[] arr;

		cout << "Here worked destr" << endl;
	}

	void printMatrix()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	matrix& operator+=(const matrix& m2)
	{
		if (this->n != m2.n || this->m != m2.m)
		{
			cout << "This matrices cant be added!" << endl;
			exit(1);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				this->arr[i][j] += m2.arr[i][j];
			}
		}
		return *this;
	}

	matrix& operator-=(const matrix& m2)
	{
		if (this->n != m2.n || this->m != m2.m)
		{
			cout << "This matrices cant be deducted!" << endl;
			exit(1);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				this->arr[i][j] -= m2.arr[i][j];
			}
		}
		return *this;
	}

	matrix operator+(const matrix& m2) const
	{
		matrix res(*this);
		res += m2;
		return res;
	}

	matrix operator-(const matrix& m2) const
	{
		matrix res(*this);
		res -= m2;
		return res;
	}

	matrix operator*(const matrix& m1) const // функция имеет вид м1.operator*(м2);
	{
		if (this->m != m1.n)
		{
			cout << "This matrices cant be multiplied" << endl;
			exit(1);
		}
		matrix product(this->n, m1.m);
		for (int i = 0; i < (this->n); i++)
		{
			for (int j = 0; j < m1.m; j++)
			{
				double sum = 0.0;
				for (int p = 0; p < (this->m); p++)
				{
					sum += (this->arr[i][p]) * (m1.arr[p][j]);
				}
				product.arr[i][j] = sum;
				sum = 0.0;
			}
		}
		return product;
	}

	friend ostream& operator<<(ostream& out, const matrix& m);
	friend istream& operator>>(istream& in, const matrix& m);
	//friend matrix operator*(const matrix& m1, const matrix& m2);
	

};

//matrix operator*(const matrix& m1, const matrix& m2)
//{
//	if (m1.m != m2.n)
//	{
//		cout << "This matrices cant be multiplied" << endl;
//	}
//	matrix product(m1.n, m2.m, true);
//	for (int i = 0; i < (m1.n); i++)
//	{
//		for (int j = 0; j < m2.m; j++)
//		{
//			double sum = 0.0;
//			for (int p = 0; p < (m1.m); p++)
//			{
//				sum += (m1.arr[i][p]) * (m2.arr[p][j]);
//			}
//			product.arr[i][j] = sum;
//			sum = 0.0;
//		}
//	}
//	return product;
//}


ostream& operator<<(ostream& out, const matrix& mat)
{
	for (int i = 0; i < mat.n; i++)
	{
		for (int j = 0; j < mat.m; j++)
		{
			out << mat.arr[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}

istream& operator>>(istream& in, const matrix& mat)
{
	for (int i = 0; i < mat.n; i++)
	{
		for (int j = 0; j < mat.m; j++)
		{
			in >> mat.arr[i][j];
		}
	}
	return in;
}

void calculate(const matrix& m1, const matrix& m2, char oper)
{
	switch (oper)
	{
	case '+':
		cout << m1 + m2 << endl;
		break;
	case '-':
		cout << m1 - m2 << endl;
		break;
	case '*':
		cout << m1 * m2 << endl;
		break;
	default:
		break;
	}
}

class MatrixArray
{
private:
	int len;
	matrix* v;
public:
	MatrixArray(int N = 0) : v(0), len(0)
	{
		if (N > 0)
		{
			v = new matrix[N];
		}
		if (v)
		{
			len = N;
		}
	}

	MatrixArray(const MatrixArray& MatrArr): len(0), v(0)
	{
		if (MatrArr.len > 0)
		{
			v = new matrix[MatrArr.len];
		}
		if (v)
		{
			len = MatrArr.len;
			for (int i = 0; i < len; i++)
			{
				v[i] = MatrArr.v[i];
			}
		}
	}

	~MatrixArray()
	{
		delete[] v;
	}

	matrix& operator[](const int index)
	{
		return v[index];
	}

	matrix operator[](const int index) const
	{
		return v[index];
	}

	int size() const
	{
		return len;
	}
};

int main()
{
	int n, m, N;
	cin >> N;

	/*char sign;
	do
	{
		int n, m, i, j;
		cout << "Enter quantity of rows and columns of the first matrix: ";
		cin >> n >> m;
		matrix A(n, m);
		cin >> A;

		cout << "Enter quantity of rows and columns of the second matrix: ";
		cin >> i >> j;
		matrix B(i, j);
		cin >> B;

		char op;
		cout << "Enter operation: ";
		cin >> op;

		calculate(A, B, op);

		cout << "Do you want to continue calculation? Y/N: ";
		cin >> sign;
	} while (sign == 'Y');*/

	//matrix x(D); // matrix x(D), matrix x = D -- срабатывает констр копирования;
	//x.printMatrix();
	MatrixArray T(N);
	for (int i = 0; i < N; i++)
	{
		cin >> n >> m;
		matrix D(n, m);
		cin >> D;
		T[i] = D;
	}
	for (int i = 0; i < N; i++)
	{
		T[i].printMatrix();
		cout << endl;
	}


	return 0;
}