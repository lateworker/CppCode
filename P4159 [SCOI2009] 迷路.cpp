#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const int Mod = 2009;
int n, b;
int idx(int i, int j, int m = 9) { return (i - 1) * m + j; }
struct Mat {
	int m;
	vector<int> a;
	Mat(int m) { this->m = m; a.resize(m * m + 3); }
	auto operator[] (int i) { return a.begin() + idx(i, 0, m); }
	auto operator[] (int i) const { return a.begin() + idx(i, 0, m); }
	Mat operator* (const Mat& b) const {
		Mat c(m);
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				const int& aij = (*this)[i][j];
				for (int k = 1; k <= m; k++) {
					c[i][k] += aij * b[j][k] % Mod;
					c[i][k] %= Mod;
				}
			}
		} return c;
	}
};
auto& operator<< (auto& cerr, const Mat& x) {
	for (int i = 1; i <= x.m; i++) {
		for (int j = 1; j <= x.m; j++) {
			cerr << x[i][j] << ' ';
		} cerr << '\n';
	} return cerr;
}
int main() { ffopen();
	cin >> n >> b;
	Mat a(n * 9);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < 9; j++) {
			a[idx(i, j + 1)][idx(i, j)] = 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char c; cin >> c;
			if (c == '0') continue;
			a[idx(i, 1)][idx(j, c - '0')] = 1;
		}
	}
	Mat c = a; b--;
	for (; b; a = a * a, b >>= 1)
		if (b & 1) c = c * a;
	cout << c[idx(1, 1)][idx(n, 1)] << '\n';
	return 0;
}
