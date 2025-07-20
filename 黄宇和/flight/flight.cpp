#include <bits/stdc++.h>
using intl = long long;
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const intl N = 100000, inf = 0x3f3f3f3f3f3f3f3f;
int n, dep[N + 10];
intl a[N + 10], b[N + 10], dp[N + 10];
vector<pair<int, int> > g[N + 10];
vector<int> pnt;
void dfs(int u, vector<int> ps) {
	int p = ps.empty() ? 0 : ps.back();
	ps.push_back(u);
	for (auto [v, w] : g[u]) if (v != p) {
		dep[v] = dep[u] + w;
		for (int r : ps) {
			intl cost = dp[r] - dep[r] * b[r] + a[r] + dep[v] * b[r];
			if (cost < dp[v]) dp[v] = cost, pnt.push_back(v);
		}
		dfs(v, ps);
	}
}
int main() {
	ffopen("flight");
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i < n; i++) {
		int u, v, w; 
		cin >> u >> v >> w;
		++u, ++v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	memset(dp, 0x3f, sizeof dp);
	dp[1] = 0; dfs(1, {});
	for (int i = 1; i <= n; i++) {
		vector<int> vec; vec.swap(pnt);
		for (int u : vec) dep[u] = 0, dfs(u, {});
		if (pnt.empty()) break;
	}
	for (int i = 2; i <= n; i++) cout << dp[i] << "\n";
	return 0;
}
