#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int K = 17, N = (1 << K);
int kk, n, m, s;
vector<pair<int, int>> g[N + 3];
int index(int u, int i, int j) { return n + u * (kk + 1) * (kk + 1) + i * (kk + 1) + j; }
intl dj[N + 3], a[K + 3];
bool vis[N + 3][K + 3][K + 3];
int main() {
	cin >> kk >> m >> s;
	n = (1 << kk);
	for (int i = 1; i <= kk; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) {
		int u, v; intl w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	memset(dj, 0x3f, sizeof dj);
	priority_queue<pair<intl, int>, vector<pair<intl, int>>, greater<pair<intl, int>>> pque;
	dj[s] = 0, pque.emplace(dj[s], s);
	while (!pque.empty()) {
		auto [dis, u] = pque.top(); pque.pop();
		if (dis > dj[u]) continue;
		for (auto [v, w] : g[u])
			if (dj[u] + w < dj[v])
				dj[v] = dj[u] + w, pque.emplace(dj[v], v);
		queue<tuple<int, int, int>> que;
		vis[u][0][0] = true, que.emplace(u, 0, 0);
		while (!que.empty()) {
			auto [v, i, j] = que.front(); que.pop();
			if (i == kk) {
				if (dj[u] + a[j] < dj[v])
					dj[v] = dj[u] + a[j], pque.emplace(dj[v], v);
			} else {
				if (!vis[v][i + 1][j])
					vis[v][i + 1][j] = true, que.emplace(v, i + 1, j);
				if (!vis[v ^ (1 << i)][i + 1][j + 1])
					vis[v ^ (1 << i)][i + 1][j + 1] = true, que.emplace(v ^ (1 << i), i + 1, j + 1);
			}
		}
	}
	for (int i = 0; i < n; i++) cout << dj[i] << " \n"[i == n - 1];
	return 0;
}
