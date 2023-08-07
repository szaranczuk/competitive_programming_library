#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

const ll INF = 1e18;

ll binpow(ll base, ll exp, ll mod, bool p)
{
	if (p)
	{
		exp %= (mod - 1);
	}
	ll mul = base % mod;
	ll res = 1ll;
	while (exp)
	{
		if (exp & 1)
		{
			res *= mul;
			res %= mod;
		}
		exp >>= 1;
		mul *= mul;
		mul %= mod;
	}
	return res;
}

ll extended_gcd(ll a, ll b, ll& x, ll& y)
{
	bool flag = false;
	if (a < b) 
	{
		swap(a, b);
		flag = true; 
	}
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll g = extended_gcd(b, a % b, x1, y1);
	x = y1;
	y = (x1 - y1 * (a / b));
	if (flag)
	{
		swap(x, y);
	}
	return g;
}
