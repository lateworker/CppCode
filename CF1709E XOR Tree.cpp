#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 200000;
int n, a[N + 10], ans;
vector<int> g[N + 10];
void dfs(int u, int p, int d, set<int>& res) {
	res.insert(d);
	bool tag = false;
	for (int v : g[u]) if (v != p) {
		set<int> now;
		dfs(v, u, d ^ a[v], now);
		if (now.size() > res.size()) now.swap(res);
		for (int x : now) if (res.count(x ^ a[u])) tag = true;
		for (int x : now) res.insert(x);
	} if (tag) res.clear(), ++ans;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	set<int> tmp;
	dfs(1, 0, a[1], tmp);
	cout << ans << "\n";
	return 0;
}
