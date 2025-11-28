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
const intl N = 2000000, Mod = 1000000007;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl n, m, k, fac[N + 10], ifac[N + 10];
intl nCr(intl n, intl m) {
	if (n < m || n < 0 || m < 0) return 0;
	return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod;
}
void slove() {
	cin >> n >> m >> k;
	intl dmax = (m + k - 1) / k, ans = 0;
	for (intl d = 1; d <= dmax; d++) {
		for (intl i = 1; i <= k && (d - 1) * k + i <= m; i++) {
			intl ajc = (d - 1) * k + i;
			ans += d * nCr(ajc - d - (i != 1), n - d - (i != 1)) % Mod * nCr(m - ajc + d, d) % Mod, ans %= Mod;
		}
	}
	cout << ans << '\n';
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
