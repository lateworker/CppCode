#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 200000, inf = 0x3f3f3f3f;
int n, m, s, q, dj[N + 10];
vector<pair<int, int> > g[N + 10];
void dijkstra() {
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
	memset(dj, inf, sizeof dj);
	dj[s] = 0, que.push({dj[s], s});
	while (!que.empty()) {
		auto [dis, u] = que.top(); que.pop();
		if (dis > dj[u]) continue;
		for (auto [v, w] : g[u]) if (dj[u] + w < dj[v]) {
			dj[v] = dj[u] + w, que.push({dj[v], v});
		}
	}
}
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> s >> q;
	for (int i = 1; i <= m; i++) {
		int u, v, w; cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	dijkstra();
	for (int i = 1; i <= q; i++) {
		int h; cin >> h;
		cout << dj[h] << "\n";
	}
	return 0;
}
