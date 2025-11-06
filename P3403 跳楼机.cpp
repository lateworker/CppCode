#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 100000;
intl h, dj[N + 10];
int x, y, z;
vector<pair<int, int>> g[N + 10];
void dijkstra(int s) {
	memset(dj, 0x3f, sizeof dj);
	priority_queue<pair<intl, int>, vector<pair<intl, int>>, greater<pair<intl, int>>> que;
	que.emplace(dj[s] = 0, s);
	while (!que.empty()) {
		auto [dis, u] = que.top(); que.pop();
		if (dis > dj[u]) continue;
		for (auto [v, w] : g[u])
			if (dj[u] + w < dj[v]) que.emplace(dj[v] = dj[u] + w, v);
	}
}
int main() {
	cin >> h >> x >> y >> z;
	if (x == 1 || y == 1 || z == 1) return cout << h << "\n", 0;
	--h;
	for (int i = 0; i < x; i++) {
		g[i].emplace_back((i + y) % x, y);
		g[i].emplace_back((i + z) % x, z);
	}
	dijkstra(0);
	intl ans = 0;
	for (int i = 0; i < x; i++) {
		if (dj[i] <= h) ans += (h - dj[i]) / x + 1;
	}
	cout << ans << "\n";
	return 0;
}
