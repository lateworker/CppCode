#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
freopen((string(s) + ".in").c_str(), "r", stdin); \
freopen((string(s) + ".out").c_str(), "w", stdout);
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int K = 17, N = (1 << K);
int kk, n, m, s;
intl a[K + 10], dj[N + 10];
void calca() {
	queue<int> que;
	vector<bool> inq(kk + 10, false);
	for (int i = 1; i <= kk; i++) inq[i] = true, que.push(i);
	while (!que.empty()) {
		int i = que.front();
		inq[i] = false; que.pop();
		for (int j = 1; j <= kk; j++) {
			int x = i == j ? 2 : abs(i - j);
			int y = i + j <= kk ? i + j : kk * 2 - i - j;
			for (int k = x; k <= y; k += 2)
				if (a[i] + a[j] < a[k]) {
					a[k] = a[i] + a[j];
					if (!inq[k]) inq[k] = true, que.push(k);
				}
		}
	}
}
vector<pair<int, intl> > g[N + 10];
void dijkstra(int s) {
	memset(dj, 0x3f, sizeof dj);
	priority_queue<pair<intl, int>, vector<pair<intl, int> >, greater<pair<intl, int> > > que;
	dj[s] = 0, que.push({dj[s], s});
	while (!que.empty()) {
		int u; intl dis; tie(dis, u) = que.top(); que.pop();
		if (dis > dj[u]) continue;
		for (pair<int, intl> e : g[u]) {
			int v; intl w; tie(v, w) = e;
			if (dj[u] + w < dj[v])
				dj[v] = dj[u] + w, que.push({dj[v], v});
		}
	}
}
int cdiff(int x, int y) { return __builtin_popcount(x ^ y); }
signed main() { ffopen("path");
	cin >> kk >> m >> s;
	n = (1 << kk);
	for (int i = 1; i <= kk; i++) cin >> a[i];
	calca();
	for (int i = 0; i < n; i++) {
		intl val = a[cdiff(i, s)];
		g[i].emplace_back(s, val);
		g[s].emplace_back(i, val);
	}
	for (int i = 1; i <= m; i++) {
		int u, v; intl w;
		cin >> u >> v >> w;
		if (u == v) continue;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	dijkstra(s);
	for (int i = 0; i < n; i++) cout << dj[i] << " ";
	cout << "\n";
	return 0;
}
/*
in:
2 4 3
2 3
2 1 1
1 3 3
1 3 2
3 2 1
ans:
3 2 1 0 
*/
