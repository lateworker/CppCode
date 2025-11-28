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
const intl N = 100000, Mod = 1000000007;
int n, a[N + 10];
intl f[N + 10][2], ans;
vector<int> g[N + 10];
void dfs(int u) {
	f[u][a[u]] = 1, f[u][!a[u]] = 0;
	for (int v : g[u]) {
		dfs(v);
		ans += f[u][0] * f[v][1] % Mod + f[u][1] * f[v][0] % Mod, ans %= Mod;
		f[u][0] += f[v][0], f[u][1] += f[v][1];
		f[u][a[u]] += f[v][!a[u]];
		f[u][0] %= Mod, f[u][1] %= Mod;
	}
}
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], --a[i];
	for (int i = 2; i <= n; i++) {
		int fa; cin >> fa;
		g[fa].push_back(i);
	}
	dfs(1);
	cout << ans % Mod << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) {
			g[i].clear();
		}
		ans = 0;
	}
	return 0;
}
