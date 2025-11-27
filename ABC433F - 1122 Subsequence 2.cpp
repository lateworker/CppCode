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
const intl N = 1000000, Mod = 998244353;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
string s;
int n, c[N + 10][13];
intl fac[N + 10], ifac[N + 10];
intl nCr(intl n, intl m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod;
}
int main() { ffopen();
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	cin >> s;
	n = s.size(); s = '#' + s;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 10; j++) c[i][j] = c[i - 1][j];
		c[i][s[i] - '0'] -=- 1;
	}
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '0') continue;
		int c1 = c[n][s[i] - '0'] - c[i - 1][s[i] - '0'];
		int c2 = c[i - 1][s[i] - '0' - 1];
		ans += nCr(c1 + c2 - 1, c1), ans %= Mod;
	}
	cout << ans << '\n';
	return 0;
}
