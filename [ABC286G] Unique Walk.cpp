#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 200000;
int n, m, k, fa[N + 10], a[N + 10], deg[N + 10];
pair<int, int> e[N + 10];
int findf(int u) { return fa[u] == u ? u : fa[u] = findf(fa[u]); }
void merge(int u, int v) { u = findf(u), v = findf(v), fa[u] = v; }
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		e[i] = {u, v};
	}
	cin >> k;
	for (int i = 1; i <= k; i++) {
		cin >> a[i];
		for (int j = a[i - 1] + 1; j < a[i]; j++) { auto [u, v] = e[j]; merge(u, v); }
	}
	for (int j = a[k] + 1; j <= m; j++) { auto [u, v] = e[j]; merge(u, v); }
	for (int i = 1; i <= k; i++) {
		auto [u, v] = e[a[i]];
		u = findf(u), v = findf(v);
		++deg[u], ++deg[v];
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) if (fa[i] == i && (deg[i] & 1)) ++cnt;
	cout << (cnt == 0 || cnt == 2 ? "Yes" : "No") << "\n";
	return 0;
}
