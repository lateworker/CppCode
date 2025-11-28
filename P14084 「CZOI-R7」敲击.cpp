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
const intl N = 200, M = N + 2, Mod = 998244353;
intl n, m, b, p;
intl h[N + 10], f[N + 10], cc[N + 10];
int idx(int i, int j, int x) { return (i - 1) * x + j; }
struct Mat {
//	inline static intl pool[M * M * 4 + 10];
//	inline static int psz = 1;
	int m;
	intl a[M * M + 3];
	Mat(int m) {
		this->m = m;
		memset(a, 0, sizeof a);
	}
//	~Mat() { psz -= m * m + 3; }
	auto operator[] (int i) { return a + idx(i, 0, m); }
	auto operator[] (int i) const { return a + idx(i, 0, m); }
	Mat operator* (const Mat& b) const {
		Mat c(m);
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				const intl& aij = (*this)[i][j];
				if (!aij) continue;
				for (int k = 1; k <= m; k++) {
					c[i][k] += aij * b[j][k] % Mod;
					c[i][k] %= Mod;
				}
			}
		} return c;
	}
};
int main() { ffopen();
	
	string s; cin >> s;
	n = s.size(); s = '#' + s;
	cin >> b >> m;
	
	int t = min(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = t; j; j--) h[j] += h[j - 1], h[j] %= Mod;
		if (s[i] == '1') ++h[p], h[p] %= Mod, ++p;
	}
	
	cc[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j; j--) {
			cc[j] += cc[j - 1];
			cc[j] %= Mod;
		}
	}
	
	Mat a(t + 2), c(t + 2);
	c[t + 2][t + 2] = p <= m;
	a[t + 2][t + 2] = (p << 1) <= m;
	for (int k = 0; k <= t; k++) {
		c[t + 2][k + 1] = h[k];
		if (k + p <= m) a[t + 2][k + 1] = h[k];
	}
	for (int j = 0; j <= t; j++) {
		for (int k = 0; k <= t; k++) {
			if (j + k > m) break;
			c[j + 1][k + 1] = a[j + 1][k + 1] = cc[k];
		}
	}
	for (--b; b; a = a * a, b >>= 1)
		if (b & 1) c = c * a;
	
	intl ans = 0;
	for (int i = 0; i <= t + 1; i++) {
		ans += c[t + 2][i + 1], ans %= Mod;
	}
	cout << ans << '\n';
	
	return 0;
}
