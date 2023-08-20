#include <bits/stdc++.h>

using namespace std;

//Miller-Rabin: check if number is prime in O(lgn)

using u128 = __uint128_t;

long long power_modulo(long long base, long long exponent, long long modulo)
{
	base %= modulo;
	long long return_value = 1ll;
	while (exponent)
	{
		if (exponent & 1)
		{
			return_value = (u128)return_value * base % modulo;
		}
		base = (u128)base * base % modulo;
		exponent >>= 1;
	}
	return return_value;
}

bool miller_rabin(long long a, long long x, long long power_of_two, long long exponent_divided_by_power_of_two)
{
	long long factor = power_modulo(a, exponent_divided_by_power_of_two, x);
	if (factor == 1 || factor == x - 1) 
		return true;
	while (power_of_two--)
	{
		factor = (u128)factor * factor % x;
		if (factor == x - 1)
			return true;
	}
	return false; 
}

bool is_prime(long long x)
{
	if (x < 2) 
		return false;
	long long miller_exponent = x - 1;
	long long power_of_two = 0;
	long long exponent_divided_by_power_of_two = miller_exponent;
	while (exponent_divided_by_power_of_two & 1 == 0)
	{
		exponent_divided_by_power_of_two >>= 1;
		power_of_two++;
	}
	for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
	{
		if (x == a) 
			return true;
		if (!miller_rabin(a, x, power_of_two, exponent_divided_by_power_of_two))
			return false;
	}
	return true;
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << is_prime(2137) << " " << is_prime(91) << '\n';
}