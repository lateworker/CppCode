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
const intl N = 1000000, Mod = 1000000007;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
int n, m, k;
intl f[N + 10], pf[N + 10];
int main() { ffopen();
	cin >> n >> m >> k;
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		int j = max(i - k + 1, 0);
		if (j) f[i] = (pf[i - 1] - pf[j - 1] + Mod) * (m - 1) % Mod, f[i] %= Mod;
		else f[i] = m + pf[i - 1] * (m - 1) % Mod, f[i] %= Mod;
		pf[i] = (pf[i - 1] + f[i]) % Mod;
	}
	cout << (fpow(m, n) + Mod - f[n]) % Mod << '\n';
	return 0;
}
