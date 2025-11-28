#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 100000;
int n, a[N + 10], siz[N + 10], dep[N + 10];
vector<int> g[N + 10];
void dfs(int u, int p) {
	dep[u] = dep[p] + 1, siz[u] = 1;
	for (int v : g[u]) if (v != p) {
		dfs(v, u);
		siz[u] += siz[v];
	}
	++a[dep[u]], --a[n - siz[u] + 2];
}
void slove() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v), ++a[v];
	}
	for (int i = 1; i <= n; i++) {
		if (!a[i]) {
			for (int i = 1; i <= n; i++) a[i] = 0;
			dfs(i, 0);
			break;
		}
	}
	for (int i = 1; i <= n; i++) a[i] += a[i - 1];
	for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) g[i].clear(), a[i] = 0;
	}
	return 0;
}
