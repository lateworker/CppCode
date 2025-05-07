#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const intl N = 4000, inf = 0x3f3f3f3f3f3f3f3f;
vector< pair<int, intl> > g[N + 10];
intl n, m, dis[N + 10];
bool SPFA(int s, int n) {
	memset(dis, 0x3f, sizeof dis);
	vector<int> cnt(n + 1, 0);
	vector<bool> inq(n + 1, false);
	queue<int> que;
	dis[s] = 0, inq[s] = true, que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		inq[u] = false;
		if (cnt[u] >= n) return true;
		for (auto [v, w] : g[u])
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;
				if (!inq[v]) inq[v] = true, que.push(v);
			}
	} return false;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		intl l, r, s;
		cin >> l >> r >> s;
		++l, ++r;
		g[r].emplace_back(l - 1, -s);
		g[l - 1].emplace_back(r, +s);
	}
	for (int i = 1; i <= n; i++) g[i + 1].emplace_back(i, -1);
	for (int i = 1; i <= n + 1; i++) g[n + 2].emplace_back(i, 0);
	if (SPFA(n + 2, n + 2)) return cout << "-1\n", 0;
	cout << dis[n + 1] - dis[1] << "\n";
	return 0;
}
/*
p[r] >= p[l - 1] + s
p[l - 1] >= p[r] - s
p[i + 1] >= p[i] + 1
*/
