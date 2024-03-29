#include <bits/stdc++.h>

typedef std::pair<int, int> ii;
typedef long long ll;
const int mod = 1e9+7;

struct Matrix
{
	std::vector<std::vector<long long>> mat;
	int n, m;
	Matrix(int N, int M)
	{
		mat.resize(N);
		for (int i = 0; i < N; i++)
			mat[i].resize(M);
		n = N;
		m = M;
	}
	Matrix(const std::vector<std::vector<long long>> &arr)
	{
		mat = arr;
		for (int i = 0; i < n; i++)
		{
			assert(arr[i].size() == arr[0].size());
		}
		n = arr.size();
		m = arr[0].size();
	}
	Matrix operator+(const Matrix &b)
	{
		assert(b.n == n && b.m == m);
		Matrix res(n, m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				res.mat[i][j] = mat[i][j] + b.mat[i][j];
			}
		}
		return res;
	}
	void operator+=(const Matrix &b)
	{
		assert(b.n == n && b.m == m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				mat[i][j] += b.mat[i][j];
			}
		}
	}
	Matrix operator-(const Matrix &b)
	{
		assert(b.n == n && b.m == m);
		Matrix res(n, m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				res.mat[i][j] = mat[i][j] - b.mat[i][j];
			}
		}
		return res;
	}
	void operator-=(const Matrix &b)
	{
		assert(b.n == n && b.m == m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				mat[i][j] -= b.mat[i][j];
			}
		}
	}
	Matrix operator*(const Matrix &b)
	{
		assert(m == b.n);
		Matrix res(n, b.m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < b.m; j++)
			{
				for (int k = 0; k < m; k++)
				{
					res.mat[i][j] += mat[i][k] * b.mat[k][j];
				}
			}
		}
		return res;
	}
	void operator%=(const long long mod)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				mat[i][j] %= mod;
			}
		}
	}
	Matrix get_id_matrix() const
	{
		assert(n == m);
		Matrix ret(n, n);
		for (int i = 0; i < n; i++)
		{
			ret.mat[i][i] = 1;
		}
		return ret;
	}
};

Matrix mod_mul(const Matrix &a, const Matrix &b, long long mod)
{
	assert(a.m == b.n);
	Matrix res(a.n, b.m);
	for (int i = 0; i < a.n; i++)
	{
		for (int j = 0; j < b.m; j++)
		{
			for (int k = 0; k < a.m; k++)
			{
				res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				res.mat[i][j] %= mod;
			}
		}
	}
	return res;
}

void mod_mul(const Matrix &a, const Matrix &b, long long mod, Matrix& res)
{
	assert(a.m == b.n);
	for (int i = 0; i < a.n; i++)
	{
		for (int j = 0; j < b.m; j++)
		{
			for (int k = 0; k < a.m; k++)
			{
				res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				res.mat[i][j] %= mod;
			}
		}
	}
}

Matrix fast_exp_mod(Matrix base, long long exp, long long mod)
{
	base %= mod;
	Matrix ret = base.get_id_matrix();
	while (exp)
	{
		if (exp & 1)
		{
			Matrix tmp(ret.n, ret.m);
			mod_mul(ret, base, mod, tmp);
			ret = tmp;
		}
		base = mod_mul(base, base, mod);
		exp >>= 1;
	}
	return ret;
}

//fast implementation for 2x2 matrix

std::pair<ii, ii> operator*(const std::pair<ii, ii>& a, const std::pair<ii, ii>& b)
{
	int r00 = (1ll*a.first.first * b.first.first + 1ll*a.first.second * b.second.first) % mod;
	int r01 = (1ll*a.first.first * b.first.second + 1ll*a.first.second * b.second.second) % mod;
	int r10 = (1ll*a.second.first * b.first.first + 1ll*a.second.second * b.second.first) % mod;
	int r11 = (1ll*a.second.first * b.first.second + 1ll*a.second.second * b.second.second) % mod;
	return {{r00, r01}, {r10, r11}};
}

std::pair<ii, ii> pow(ll exp)
{
	std::pair<ii, ii> base = {{3,2}, {1,1}}; //example matrix for 3x2N domino tiling;
	std::pair<ii, ii> ret = {{1,0},{0,1}};
	while (exp)
	{
		if (exp & 1)
		{
			ret = ret * base;
		}
		base = base * base;
		exp >>= 1;
	}
	return ret;
}