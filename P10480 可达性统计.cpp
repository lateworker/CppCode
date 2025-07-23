#include <bits/stdc++.h>
using namespace std;
const int N = 30000;
int n, m, deg[N + 10];
bitset<N + 10> dp[N + 10];
vector<int> g[N + 10];
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		g[y].push_back(x), ++deg[x];
	}
	queue<int> que;
	for (int i = 1; i <= n; i++) {
		dp[i].set(i);
		if (!deg[i]) que.push(i);
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int v : g[u]) {
			dp[v] |= dp[u];
			if (!--deg[v]) que.push(v);
		}
	}
	for (int i = 1; i <= n; i++) cout << dp[i].count() << "\n";
	return 0;
}
