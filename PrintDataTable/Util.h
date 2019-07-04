#pragma once
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

class Util
{
public:

	// Returns nth Fibonacci number
	static int fib(int n)
	{
		int F[2][2] = { {1,1},{1,0} };
		if (n == 0)
		{
			return 0;
		}

		power(F, n - 1);
		return F[0][0];
	}

	// Returns true if n is a Fibinacci Number, else false 
	static bool isFibonacci(int n)
	{
		// n is Fibinacci if one of 5*n*n + 4 or 5*n*n - 4 or both 
		// is a perferct square 
		return isPerfectSquare(5 * n*n + 4) ||
			isPerfectSquare(5 * n*n - 4);
	}

	// Adds new entry into the data table
	// data: number <-> count
	static void add_number(unordered_map<int, int>& data, int number)
	{
		auto it = data.find(number);
		if (it == data.end())
		{
			data.emplace(number, 1);
		}
		else
		{
			data[number] = it->second + 1;
		}
	}

	// Converts from number <-> count to count <-> set of number
	static map<int, set<int>, greater<int>> convert_data(const unordered_map<int, int>& data)
	{
		map<int, set<int>, greater<int>> output; // count <-> set of number in descending order

		for (auto it = data.begin(); it != data.end(); it++)
		{
			auto it2 = output.find(it->second);
			if (it2 == output.end())
			{
				set<int> s = { it->first };
				output.emplace(it->second, s);
			}
			else
			{
				it2->second.emplace(it->first);
			}
		}

		return output;
	}

private:
	Util() {}
	~Util() {}

	// A utility function that returns true if x is perfect square 
	static bool isPerfectSquare(int x)
	{
		int s = sqrt(x);
		return (s*s == x);
	}

	// Optimized version of power() in method 4
	static void power(int F[2][2], int n)
	{
		if (n == 0 || n == 1)
			return;
		int M[2][2] = { {1,1},{1,0} };

		power(F, n / 2);
		multiply(F, F);

		if (n % 2 != 0)
			multiply(F, M);
	}

	static void multiply(int F[2][2], int M[2][2])
	{
		int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
		int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
		int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
		int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

		F[0][0] = x;
		F[0][1] = y;
		F[1][0] = z;
		F[1][1] = w;
	}
};

