#include <iostream>
#include <vector> 
#include <string>
using namespace std;

class ComplexNumber
{
private:
	double Re;
	double Im;

public:
	/*ComplexNumber() изначально тут есть неявный конструктор по умолч такого вида, позволяет писать "ComplexNumber name;"
	{

	}*/

	ComplexNumber(double a = 0, double b = 0) : Re(a), Im(b)
	{
		/*Re = a; копирующая инициализация
		Im = b;*/ 
		//cout << this << "\t" << "constructor activated" << endl;	
	}

	ComplexNumber(const ComplexNumber& num): Re(num.Re), Im(num.Im)//конструктор копирования, создание нового числа при помощи копирования
																//уже существующего, : - прямая инициализация 
	{
		cout << "Copy constructor worked here!\n";
	}

	~ComplexNumber()
	{
		cout << "RIP:" << Re << " + " << Im << "i" << endl;
	}
	
	double getRe()
	{
		return Re;
	}

	double getIm()
	{
		return Im;
	}

	void printNumber()
	{
		cout << Re << " + " << Im << "i" << endl;
	}

	double mod(double Re, double Im)
	{
		return sqrt(Re * Re + Im * Im);
	}

	friend ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b);
	friend ComplexNumber operator-(const ComplexNumber& a, const ComplexNumber& b);
	friend ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b);
	friend ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber& b);
	friend ostream& operator<< (ostream& out, const ComplexNumber& num);
	friend istream& operator>> (istream& in, ComplexNumber& num);

	ComplexNumber& operator+=(const ComplexNumber& b)
	{
		Re += b.Re;
		Im += b.Im;
		return *this;

	}

	ComplexNumber& operator-=(const ComplexNumber& b)
	{
		Re -= b.Re;
		Im -= b.Im;
		return *this;
	}

	ComplexNumber& operator=(const ComplexNumber& b)
	{
		Re = b.Re;
		Im = b.Im;
		cout << "Here worked =";
		return *this;
		
	}

};

ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b)
{
	return ComplexNumber(a.Re + b.Re, a.Im + b.Im);
}

ComplexNumber operator-(const ComplexNumber& a, const ComplexNumber& b)
{
	return ComplexNumber(a.Re - b.Re, a.Im - b.Im);
}

ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b)
{
	return ComplexNumber(a.Re*b.Re - a.Im*b.Im, a.Re*b.Im + a.Im*b.Re);
}

ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber& b)
{
	return ComplexNumber((a.Re * b.Re + a.Im * b.Im)/(b.Re* b.Re + b.Im*b.Im),(a.Im*b.Re - a.Re*b.Im)/ (b.Re * b.Re + b.Im*b.Im));
}

ostream& operator<< (ostream& out, const ComplexNumber& num)
{
	out << num.Re << " + " << num.Im <<"i";
	return out;
}

istream& operator>> (istream& in, ComplexNumber& num)
{
	in >> num.Re;
	in >> num.Im;
	return in;
}

void calculate(const ComplexNumber& a, const ComplexNumber& b, char op)
{
	switch (op)
	{
	case '+':
		cout << a + b << endl;
		break;
	case '-':
		cout << a - b << endl;
		break;
	case '*':
		cout << a * b << endl;
		break;
	case '/':
		cout << a / b << endl;
		break;
	default:
		cout << "Error. Unknown operator!" << endl;
		break;
	}
	
}

int main()
{
	
	

	char oper;
	ComplexNumber one, two;
	char ind;
	do
	{
		cout << "Enter Re and Im parts of the first number: ";
		cin >> one;
		cout << "Enter operator:";
		cin >> oper;
		cout << "Enter Re and Im parts of the second number: ";
		cin >> two;
		cout << "Result is: ";
		calculate(one, two, oper);

		cout << "Do you want to continue? Y/N: ";
		cin >> ind;
	

	} while (ind == 'Y');
	
	//delete[] arr;
	return 0;
}
