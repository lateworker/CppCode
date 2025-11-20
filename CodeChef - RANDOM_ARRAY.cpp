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
using piil = pair<intl, intl>;
const intl N = 200000, Mod = 1000000007;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl n, nn, f[N + 10];
piil a[N + 10], g[N + 10];
piil operator+ (const piil& x, const piil& y) { return make_pair(x.first + y.first, x.second + y.second); }
piil operator+= (piil& x, const piil& y) { return x = x + y; }
piil operator% (const piil& x, const intl& y) { return make_pair((x.first % y + y) % y, (x.second % y + y) % y); }
void slove() {
	cin >> nn;
	for (int i = 1; i <= nn; i++) {
		int m; cin >> m;
		for (int j = 1; j <= m; j++) {
			int x; cin >> x;
			a[++n] = {x, i};
		}
	}
	sort(a + 1, a + 1 + n, greater<piil>());
	piil now = {0, 0}; intl ans = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		auto [x, c] = a[i];
		while (a[j].first > x) {
			g[a[j].second] = (g[a[j].second] + make_pair(f[j], 1)) % Mod;
			now = (now + make_pair(f[j++], 1)) % Mod;
		}
		f[i] = (now.first - g[c].first + Mod) * fpow(now.second - g[c].second, Mod - 2) % Mod + a[i].first, f[i] %= Mod;
		ans += f[i], ans %= Mod;
	}
	cout << (ans * fpow(n, Mod - 2) % Mod + Mod) % Mod << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		n = 0;
		for (int i = 1; i <= nn; i++) g[i] = {0, 0};
	}
	return 0;
}
