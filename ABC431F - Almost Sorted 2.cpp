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
const intl Mod = 998244353, N = 300000;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl fac[N + 10], ifac[N + 10];
int n, d, a[N + 10];
int main() { ffopen();
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	cin >> n >> d;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n, greater());
	intl ans = 1;
	for (int i = 1, j = 1; i <= n; i++) {
		while (a[j] > a[i] + d) ++j;
		ans = ans * (i - j + 1) % Mod;
	}
	for (int i = 1, j; i <= n; i = j) {
		for (j = i; j <= n + 1; j++) {
			if (a[i] == a[j]) continue;
			ans = ans * ifac[j - i] % Mod;
			break;
		}
	}
	cout << ans << '\n';
	return 0;
}
