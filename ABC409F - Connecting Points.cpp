#include <bits/stdc++.h>
using namespace std;
const int N = 3000, inf = INT_MAX;
int n, q, x[N + 10], y[N + 10], fa[N + 10];
int findf(int u) { return fa[u] == u ? u : fa[u] = findf(fa[u]); }
void merge(int u, int v) { u = findf(u), v = findf(v), fa[u] = v; }
int gdis(int u, int v) { return abs(x[u] - x[v]) + abs(y[u] - y[v]); }
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i], fa[i] = i;
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> que;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			que.push({gdis(i, j), i, j});
	for (int i = 1; i <= q; i++) {
		int op; cin >> op;
		if (op == 1) {
			++n, fa[n] = n;
			cin >> x[n] >> y[n];
			for (int i = 1; i < n; i++)
				que.push({gdis(i, n), i, n});
		} else
		if (op == 2) {
			int k = INT_MAX;
			while (!que.empty()) {
				auto [dd, i, j] = que.top();
				if (dd > k) break; que.pop();
				if (findf(i) == findf(j)) continue;
				k = dd, merge(i, j);
			}
			cout << (k == inf ? -1 : k) << "\n";
		} else
		if (op == 3) {
			int u, v; cin >> u >> v;
			cout << (findf(u) == findf(v) ? "Yes" : "No") << "\n";
		}
	}
	return 0;
}
