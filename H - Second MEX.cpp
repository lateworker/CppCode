#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 200000, Mod = 998244353;
intl n, a[N + 10], c[N + 10], mi2[N + 10], g[N + 10];
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c % Mod; }
intl inv(intl a) { return a ? fpow(a, Mod - 2) : 1; }
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], ++c[a[i]];
	
	g[n + 3] = 1;
	for (int i = n + 2; i >= 0; i--) g[i] = g[i + 1] * mi2[c[i]] % Mod;
	
	bool tag = false;
	intl ans = 0, pmi = 1, psu = 0, cnt;
	
	for (intl smex = 0; smex <= n + 2; ++smex) {
		if (smex) {
			if (c[smex - 1]) pmi *= mi2[c[smex - 1]] - 1, pmi %= Mod;
			if (!tag) psu += inv(mi2[c[smex - 1]] - 1), psu %= Mod;
			cnt = pmi * max(psu, 1LL) % Mod * g[smex + 1] % Mod;
			ans += cnt * smex % Mod, ans %= Mod;
		}
		if (!c[smex]) {
			if (tag) break;
			tag = true, psu = 0;
		}
	}
	
	cout << (ans + Mod - 1) % Mod << '\n';
}
int main() { ffopen();
	mi2[0] = 1; for (int i = 1; i <= N; i++) mi2[i] = (mi2[i - 1] << 1) % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) c[a[i]] = 0;
	}
	return 0;
}
