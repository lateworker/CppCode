#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 100000, LN = __lg(N) + 1, inf = 0x3f3f3f3f3f3f3f3f;
intl n, tn, a[N + 10], b[N + 10], f[N + 10], dep[N + 10];
vector<pair<int, intl>> g[N + 10];

struct line {
	intl k = 0, b = inf;
	intl at(intl x0) { return k * x0 + b; }
};
template<size_t N_>
struct SegmentTree {
	struct Segt {
		line val;
		Segt *le, *ri;
		Segt() { le = ri = this, val = {0, inf}; }
	};
	inline static Segt pool[N_];
	inline static size_t psz = 0;
	intl l0 = 0, r0 = 100000000000;
	Segt* root = pool;
	Segt* node() {
		Segt* u = pool + ++psz;
		u->le = u->ri = pool;
		u->val = {0, inf};
		return u;
	}
	void insert(Segt*& u, intl l, intl r, line val) {
		if (u == pool) { u = node(); u->val = val; return; }
		intl mid = (l + r) >> 1;
		if (val.at(mid) < u->val.at(mid)) swap(u->val, val);
		if (l == r) return;
		if (val.at(l) < u->val.at(l)) insert(u->le, l, mid, val);
		if (val.at(r) < u->val.at(r)) insert(u->ri, mid + 1, r, val);
	}
	line query(Segt* u, intl l, intl r, intl x0) {
		if (u == pool) return {0, inf};
		if (l == r) return u->val;
		intl mid = (l + r) >> 1;
		line res = x0 <= mid ? query(u->le, l, mid, x0) : query(u->ri, mid + 1, r, x0);
		return u->val.at(x0) < res.at(x0) ? u->val : res;
	}
	void insert(line val) { insert(root, l0, r0, val); }
	intl query(intl x0) { return query(root, l0, r0, x0).at(x0); }
};

int dfn[N + 10], stt[N + 10][LN + 1], psz;
void dfs(int u, int p) {
	dfn[u] = ++psz, stt[dfn[u]][0] = p;
	for (auto [v, w] : g[u]) if (v != p) {
		dep[v] = dep[u] + w;
		dfs(v, u);
	}
}
int minST(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
int glca(int u, int v) {
	if (u == v) return u;
	u = dfn[u], v = dfn[v];
	if (u > v) swap(u, v);
	int d = __lg(v - u); ++u;
	return minST(stt[u][d], stt[v - (1 << d) + 1][d]);
}
intl gdis(int u, int v) { return dep[u] + dep[v] - 2 * dep[glca(u, v)]; }

int siz[N + 10], vfa[N + 10];
bitset<N + 10> del;
SegmentTree<N * 4 + 10> st[N + 10];
void gsiz(int u, int p) {
	if (siz[u] = 0, del[u]) return;
	siz[u] = 1;
	for (auto [v, w] : g[u]) if (v != p)
		gsiz(v, u), siz[u] += siz[v];
}
int gctr(int u, int p, const int& n) {
	if (del[u]) return 0;
	for (auto [v, w] : g[u]) if (v != p)
		if (siz[v] << 1 > n) return gctr(v, u, n);
	return u;
}
void build(int u, int p) {
	if (del[u]) return;
	gsiz(u, 0); int c = gctr(u, 0, siz[u]);
	vfa[c] = p, del[c] = true;
	for (auto [v, w] : g[c]) build(v, c);
}
void update(int i) {
	for (int u = i; u; u = vfa[u]) {
		st[u].insert(line{b[i], f[i] + a[i] + b[i] * gdis(u, i)});
	}
}
intl query(int i) {
	intl res = inf;
	for (int u = i; u; u = vfa[u]) {
		res = min(res, st[u].query(gdis(u, i)));
	}
	return res;
}

vector<intl> travel(vector<intl> A, vector<int> B, vector<int> U, vector<int> V, vector<int> W) {
	n = A.size();
	for (int i = 1; i <= n; i++) a[i] = A[i - 1], b[i] = B[i - 1];
	for (int i = 1; i < n; i++) {
		auto [u, v, w] = make_tuple(U[i - 1], V[i - 1], W[i - 1]);
		++u, ++v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	
	dfs(1, 0); tn = __lg(n) + 1;
	for (int j = 1; j <= tn; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			stt[i][j] = minST(stt[i][j - 1], stt[i + (1 << (j - 1))][j - 1]);
		}
	}

	build(1, 0);
	for (int i = 1; i <= n; i++) cerr << vfa[i] << " \n"[i == n];
	memset(f, 0x3f, sizeof f), f[1] = 0;
	vector<int> idx(n);
	iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return b[i] > b[j]; });
	for (int i : idx) {
		f[i] = min(f[i], query(i));
		update(i);
	}
	
	vector<intl> ans;
	for (int i = 2; i <= n; i++) {
		ans.push_back(min(f[i], query(i)));
	}
	return ans;
}
//int main() {
//	vector<intl> ans = travel({10, 5, 13, 4, 3}, {10, 7, 5, 9, 1}, {1, 0, 3, 2}, {0, 2, 2, 4}, {1, 5, 10, 3});
//	for (intl x : ans) cout << x << "\n";
//	return 0;
//}
