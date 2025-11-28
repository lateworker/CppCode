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
const intl N = 200000, Mod = 998244353;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl fac[N + 10], ifac[N + 10], pw2[N + 10], ipw2[N + 10];
intl nCr(intl n, intl m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod;
}
intl gt(intl n) { return nCr(n << 1, n) * fpow(n + 1, Mod - 2) % Mod; }
intl n;
void slove() {
	cin >> n;
	intl ans = 0;
	for (intl i = 0; i <= n >> 1; i++) {
		ans += nCr(n, i << 1) * gt(i) % Mod * fac[n] % Mod * ipw2[i] % Mod, ans %= Mod;
	}
	cout << ans << '\n';
}
int main() { ffopen();
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	pw2[0] = 1;
	for (int i = 1; i <= N; i++) pw2[i] = (pw2[i - 1] << 1) % Mod;
	ipw2[N] = fpow(pw2[N], Mod - 2);
	for (int i = N; i >= 1; i--) ipw2[i - 1] = (ipw2[i] << 1) % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
