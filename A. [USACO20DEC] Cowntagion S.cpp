#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 100000;
intl n, ans;
vector<int> g[N + 10];
void dfs(int u, int p) {
	intl cnt = 0;
	for (int v : g[u]) if (v != p) ++cnt;
	if (cnt) ans += __lg(cnt) + cnt + 1;
	for (int v : g[u]) if (v != p) dfs(v, u);
}
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	dfs(1, 0);
	cout << ans << "\n";
	return 0;
}
