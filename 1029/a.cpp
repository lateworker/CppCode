#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define int long long
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 300000, Mod = 1000000007;
int n, lim[N + 10];
vector<int> f[N + 10];
vector<int> g[N + 10];
void dfs(int u, int p) {
	int deg = g[u].size() - (p ? 1 : 0);
	lim[u] = (deg >> 1) + 1;
	f[u].resize((lim[u] << 1) + 5, 0);
	f[u][lim[u]] = f[u][lim[u] + 2] = 1;
	for (int v : g[u]) if (v != p) {
		dfs(v, u);
		vector<int> h((lim[u] << 1) + 5);
		f[u].swap(h);
		for (int uc = -lim[u]; uc <= lim[u]; ++uc) {
			for (int vc = -min(1LL, lim[u] + uc); vc <= min(1LL, lim[u] - uc); ++vc) {
//				int now = uc + vc;
//				if (now < -lim[u] || now > lim[u]) continue;
				f[u][uc + vc + lim[u] + 1] += (intl) h[uc + lim[u] + 1] * f[v][vc + lim[v] + 1] % Mod;
				f[u][uc + vc + lim[u] + 1] %= Mod;
			}
		}
	}
}
void slove() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	cout << ((intl) f[1][lim[1]] + f[1][lim[1] + 1] + f[1][lim[1] + 2]) % Mod << '\n';
}
signed main() {
	ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) f[i].clear(), g[i].clear();
	}
	return 0;
}

