#define ffopen(s) \
	cin.tie(0)->sync_with_stdio(0); \
	freopen((string(s) + ".in").c_str(), "r", stdin); \
	freopen((string(s) + ".out").c_str(), "w", stdout);
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100000;
int n, a[N + 10], f[N + 10];
vector<int> g[N + 10];
void dfs(int u, int p) {
	f[u] = a[u];
	for (int v : g[u]) if (v != p) {
		dfs(v, u);
		if (f[v] > 0) f[u] += f[v];
	}
}
signed main() { //ffopen("tree");
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
	cout << ans << "\n";
	return 0;
}
