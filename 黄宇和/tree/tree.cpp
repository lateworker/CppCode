#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 500000;
int n, siz[N + 10];
vector<int> g[N + 10];
bitset<N + 10> del;
void gsiz(int u, int p) {
	siz[u] = 0;
	if (del[u]) return;
	siz[u] = 1;
	for (int v : g[u]) if (v != p)
		gsiz(v, u), siz[u] += siz[v];
}
int gctr(int u, int p, const int& n) {
	if (del[u]) return 0;
	for (int v : g[u]) if (v != p)
		if (siz[v] * 2 > n) return gctr(v, u, n);
	return u;
}
void dfs(int u, int p, int mi, int ma, vector<pair<int, int>>& cmi, vector<pair<int, int>>& cma) {
	if (del[u]) return;
	if (u < mi) cmi.emplace_back(ma, u);
	if (u > ma) cma.emplace_back(mi, u);
	for (int v : g[u]) if (v != p) {
		dfs(v, u, min(mi, u), max(ma, u), cmi, cma);
	}
}
struct Tnum {
	int st[N + 10];
	void modify(int u, int val) { for (; u <= n; u += u & -u) st[u] += val; }
	int query(int u) { int res = 0; for (; u; u -= u & -u) res += st[u]; return res; }
} st;
intl count(const vector<pair<int, int>>& cmi, const vector<pair<int, int>>& cma) {
	vector<tuple<int, int, bool>> vec;
	for (const auto& ___ : cmi) {
		int x, u; tie(x, u) = ___;
		vec.emplace_back(u, x, false);
	}
	for (const auto& ___ : cma) {
		int y, v; tie(y, v) = ___;
		vec.emplace_back(y, v, true);
	}
	sort(vec.begin(), vec.end());
	intl res = 0;
	for (const auto& ___ : vec) {
		int i, j, k; tie(i, j, k) = ___;
		if (k) res += st.query(j);
		else st.modify(j, 1);
	}
	for (const auto& ___ : vec) {
		int i, j, k; tie(i, j, k) = ___;
		if (!k) st.modify(j, -1);
	}
	return res;
}
intl ans;
void solve(int u) {
	if (del[u]) return;
	gsiz(u, 0);
	int c = gctr(u, 0, siz[u]);
	intl res = 0;
	vector<pair<int, int>> tcmi, tcma;
	tcmi.emplace_back(c, c);
	tcma.emplace_back(c, c);
	for (int v : g[c]) {
		vector<pair<int, int>> cmi, cma;
		dfs(v, c, c, c, cmi, cma);
		res -= count(cmi, cma);
		tcmi.insert(tcmi.end(), cmi.begin(), cmi.end());
		tcma.insert(tcma.end(), cma.begin(), cma.end());
	}
	res += count(tcmi, tcma) - 1;
	ans += res;
	del[c] = true;
	for (int v : g[c]) solve(v);
}
int main() { ffopen(tree);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	solve(1);
	cout << ans << "\n";
	return 0;
}
