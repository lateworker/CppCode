#include <bits/stdc++.h>
#define mid(l, r) mid = ((l + r) >> 1)
using namespace std;

template<size_t N>
struct SEGT {
	struct Segt {
		Segt *le, *ri; int val;
		Segt() { le = ri = this, val = 0; }
	} *root;
	
	SEGT() { root = pool, psz = 0; }
	
	void pushup(Segt* u) { u->val = u->le->val + u->ri->val; }
	void update(Segt*& u, int l, int r, int pos, int val) {
		if (u == pool) u = node();
		if (l == r) return void(u->val += val);
		int mid(l, r);
		pos <= mid ? update(u->le, l, mid, pos, val) : update(u->ri, mid + 1, r, pos, val);
		pushup(u);
	}
	int query(Segt* u, int l, int r, int lf, int rt) {
		if (u == pool) return 0;
		if (lf <= l && r <= rt) return u->val;
		int mid(l, r);
		if (rt <= mid) return query(u->le, l, mid, lf, rt);
		if (mid < lf) return query(u->ri, mid + 1, r, lf, rt);
		return query(u->le, l, mid, lf, rt) + query(u->ri, mid + 1, r, lf, rt);
	}
	
	static Segt pool[N]; static int psz;
	Segt* node() { SEGT::Segt* u = pool + ++ psz; u->le = u->ri = pool; return u; }
};
template<size_t N> SEGT<N>::Segt SEGT<N>::pool[N];
template<size_t N> int SEGT<N>::psz = 0;

const int N = 100000, L = __lg(N + 1) + 1;
int n, m, a[N + 10];
vector<int> g[N + 10];

int dep[N + 10], dfn[N + 10], ST[N + 10][L + 1], psz;
void gST(int u, int p) {
//	cout << u << " " << p << '\n';
	dep[u] = dep[p] + 1, dfn[u] = ++psz, ST[dfn[u]][0] = p;
	for (int v : g[u]) if (v != p) gST(v, u);
}
int minST(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
int LCA(int u, int v) {
	if (u == v) return u;
	u = dfn[u], v = dfn[v];
	if (u > v) swap(u, v);
	int d = __lg(v - u); ++u;
	return minST(ST[u][d], ST[v - (1 << d) + 1][d]);
}
int gdis(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }

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
void build(int u, int p) {
	if (del[u]) return;
	gsiz(u, 0); int c = gcet(u, 0, siz[u]);
	vfa[c] = p, del[c] = true;
	for (int v : g[c]) build(v, c);
}

SEGT<10000> st[2][N + 10];
void update(int pos, int val) {
	for (int u = pos, f = vfa[u]; u; u = f, f = vfa[u]) {
		st[0][u].update(st[0][u].root, 0, n, gdis(u, pos), val);
		if (f) st[1][u].update(st[0][u].root, 0, n, gdis(f, pos), val);
	}
}
int query(int pos, int k) {
	int res = 0;
	for (int u = pos, v = 0; u; v = u, u = vfa[u]) {
		int dis = gdis(u, pos);
		if (dis > k) continue;
		res += st[0][u].query(st[0][u].root, 0, n, 0, k - dis);
		if (v) res -= st[1][v].query(st[0][v].root, 0, n, 0, k - dis);
	} return res;
}

int main() { // cin.tie(0)->sync_with_stdio(0);
	freopen("P6329.in", "r", stdin);
//	freopen("P6329.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	cout << "FUCK1\n";
	gST(1, 0);
	cout << "FUCK2\n";
//	for (int j = 1; j <= __lg(n); j++) {
//		cout << j << "\n";
//		for (int i = 1; i <= n - (1 << j) + 1; i++)
//			ST[i][j] = minST(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
//	}
//	build(1, 0);
//	for (int i = 1; i <= n; i++) update(i, a[i]);
//	for (int i = 1; i <= m; i++) {
//		int op, x, y;
//		cin >> op >> x >> y;
//		if (op == 0) {
//			cout << query(x, y) << "\n";
//		} else
//		if (op == 1) {
//			update(x, a[x] - y), a[x] = y;
//		}
//	}
	return 0;
}
