#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const intl N = 200000, inf = 0x3f3f3f3f3f3f3f3f;
intl n, m, ans = inf;
vector< pair<intl, intl> > g[N + 10];
map<intl, intl> dp[N + 10];
void dfs(int u, int p) {
	dp[u][0] = 0;
	for (auto [v, w] : g[u]) if (v != p) {
		dfs(v, u);
		if (dp[v].size() > dp[u].size()) swap(dp[u], dp[v]);
		for (auto [dis, cnt] : dp[v]) if (m >= dis + w && dp[u].count(m - dis - w))
			ans = min(ans, cnt + dp[u][m - dis - w] + 1);
		for (auto [dis, cnt] : dp[v]) if (dis + w <= m) {
			if (dp[u].count(dis + w)) dp[u][dis + w] = min(dp[u][dis + w], cnt + 1);
			else dp[u][dis + w] = cnt + 1;
		}
	}
}
int main() {
	freopen("P4149_2.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		intl u, v, w; cin >> u >> v >> w; //++u, ++v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	} dfs(1, 0);
	cout << (ans == inf ? -1 : ans) << "\n";
	return 0;
}
