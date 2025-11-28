#include <bits/stdc++.h>
using namespace std;
const int N = 500000;
int n;
pair<int, int> f[N + 10], se[N + 10];
vector<int> g[N + 10];
bool gtr(const pair<int, int>& x, const pair<int, int>& y) {
	if (x.first == y.first) return x.second > y.second;
	return x.first > y.first;
}
void dfs(int u, int p) {
	f[u] = {0, u}, se[u] = {0, 0};
	for (int v : g[u]) if (v != p) {
		dfs(v, u);
		pair<int, int> fv = f[v]; ++fv.first;
		if (gtr(fv, f[u])) {
			se[u] = f[u], f[u] = fv;
		} else if (gtr(fv, se[u])) {
			se[u] = fv;
		}
	}
}
void chg(int u, int p) {
	for (int v : g[u]) if (v != p) {
		pair<int, int> fv = f[v], fu; ++fv.first;
		fu = fv == f[u] ? se[u] : f[u]; ++fu.first;
		if (fu.second != v) {
			if (gtr(fu, f[v])) {
				se[v] = f[v], f[v] = fu;
			} else if (gtr(fu, se[v])) {
				se[v] = fu;
			}
		}
		chg(v, u);
	}
}
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
//	for (int i = 1; i <= n; i++) cerr << f[i].first << ' ' << f[i].second << ' ' << se[i].first << ' ' << se[i].second << '\n';
	
	chg(1, 0);
//	for (int i = 1; i <= n; i++) cerr << f[i].first << ' ' << f[i].second << ' ' << se[i].first << ' ' << se[i].second << '\n';
	for (int i = 1; i <= n; i++) cout << f[i].second << '\n';
	return 0;
} 
