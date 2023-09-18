#include <bits/stdc++.h>

struct Matrix
{
	std::vector<std::vector<long long>> mat;
	int n, m;
	Matrix(int N, int M)
	{
		mat.resize(N);
		for (int i = 0; i < N; i++) mat[i].resize(M);
		n = N;
		m = M;
	}
	Matrix(const std::vector<std::vector<long long>>& arr)
	{
		mat = arr;
	}
	Matrix operator+(const Matrix& b)
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
	void operator+=(const Matrix& b)
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
	Matrix operator-(const Matrix& b)
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
	void operator-=(const Matrix& b)
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
	Matrix operator*(const Matrix& b)
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
};

Matrix mod_mul(const Matrix& a, const Matrix& b, long long mod)
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