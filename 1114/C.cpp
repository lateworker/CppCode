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
const intl Mod = 1000000007, N = 300000;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl fac[N + 10], ifac[N + 10];
intl nCr(intl n, intl m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod;
}
intl nPr(intl n, intl m) {
	return nCr(n, m) * fac[m] % Mod;
}
intl n;
void slove() {
	cin >> n;
	for (int k = 1; k < n; k++) {
		int x = (n - k + 1) / k, y = (n - k + 1) % k;
		if ((n - k + 1) % k) cout << fac[x] * (x + 1) % Mod * (k - y + 1) % Mod * fac[n - x - 1] % Mod << ' ';
		else cout << fac[x] * fac[n - x] % Mod << ' ';
	}
	cout << fac[n] << "\n";
}
int main() { ffopen();
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
