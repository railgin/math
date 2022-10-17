#include <iostream>
#include <string>
#include <vector>
using namespace std;

int MaxElem(const vector<int>& e)
{
	int max(e[0]);
	int n_v = e.size();
	for (int i = 0; i < n_v; ++i)
	{
		if (e[i] > max)
		{
			max = e[i];
		}
	}
	return max;
}

vector<int> elems;

int maxCollatz(int n)
{
	if (n == 1)
	{
		return MaxElem(elems);
	}
	if (n % 2 == 0)
	{
		elems.push_back(n);
		n /= 2;
		maxCollatz(n);
	}
	else
	{
		elems.push_back(n);
		n = n * 3 + 1;
		maxCollatz(n);

	}
}

int main()
{
	
	int n;
	cin >> n;
	cout<<maxCollatz(n);

	return 0;
}