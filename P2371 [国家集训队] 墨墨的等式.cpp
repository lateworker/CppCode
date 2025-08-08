#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 500000;
int n, m, a[14];
vector<pair<int, int>> g[N + 10];
intl dj[N + 10];
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
intl solve(intl x) {
	intl res = 0;
	for (int i = 0; i < a[1]; i++)
		if (dj[i] <= x) res += (x - dj[i]) / a[1] + 1;
	return res;
}
int main() {
	intl l, r;
	cin >> n >> l >> r;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (x) a[++m] = x;
	} n = m;
	sort(a + 1, a + 1 + n);
	for (int i = 0; i < a[1]; i++) {
		for (int j = 2; j <= n; j++)
			g[i].emplace_back((i + a[j]) % a[1], a[j]);
	}
	dijkstra(0);
	cout << solve(r) - solve(l - 1) << "\n";
	return 0;
}
