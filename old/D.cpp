#define MultiCase (cin >> CaseId)
#define Main(Callback) main() { int CaseId = 1; { Callback } CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else return 0
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
const intl N = 200000, Mod = 1000000007;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c % Mod; }
intl fac[N + 10], ifac[N + 10];
void initfac() {
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
}
int n, m, a[N + 10], fa[N + 10];
vector<int> g[N + 10];
void init(int n) {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		g[i].clear();
	}
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int Main(ffopen(); initfac(); MultiCase; ) {
	cin >> n >> m;
	init(n);
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		fa[find(u)] = find(v);
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) g[find(i)].push_back(i);
	intl ans = fac[n];
	for (int i = 1; i <= n; i++) {
		if (fa[i] != i) continue;
		sort(g[i].begin(), g[i].end(), [&](int i, int j) { return a[i] < a[j]; } );
		int gn = g[i].size();
		for (int j = 0, c = 1; j <= gn; j++, c++) {
			if (j == gn || !j || a[g[i][j]] != a[g[i][j - 1]]) {
				ans *= fac[c - 1], ans %= Mod;
				c = 1;
			}
		}
		ans *= ifac[gn], ans %= Mod;
	}
	cout << ans % Mod << '\n';
} Return; }

