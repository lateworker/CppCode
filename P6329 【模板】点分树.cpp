#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int n, m, a[N + 10];
vector<int> g[N + 10];
bool del[N + 10];
int siz[N + 10], vfa[N + 10];
void gsiz(int u, int p) {
	if (siz[u] = 0, del[u]) return;
	siz[u] = 1;
	for (int v : g[u]) if (v != p)
		gsiz(v, u), siz[u] += siz[v];
}
int gcet(int u, int p, const int& szt) {
	if (del[u]) return 0;
	for (int v : g[u]) if (v != p)
		if (siz[v] << 1 > szt) return gcet(v, u, szt);
	return u;
}
void gval(int u, int p, int d, vector<int>& res) {
	if (del[u]) return;
	
}
void prepare(int u, int p) {
	if (del[u]) return;
	gsiz(u, 0); int c = gcet(u, 0, siz[u]);
	vfa[c] = p;
	for (int v : g[c]) {
		// 
	} del[c] = true;
	for (int v : g[c]) prepare(v, c);
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	} prepare(1, 0);
	for (int i = 1; i <= n; i++) cout << vfa[i] << " \n"[i == n];
	return 0;
}
