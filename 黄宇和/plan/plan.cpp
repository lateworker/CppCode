#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int long long
using namespace std;
using intl = long long;
const int N = 200000;
int n, m, fa[N + 10], siz[N + 10], dfn[N + 10], idfn[N + 10], psz;
intl a[N + 10], s[N + 10], w[N + 10], wp[N + 10];
vector<int> g[N + 10];
void dfs(int u) {
	idfn[dfn[u] = ++psz] = u, s[u] = a[u], siz[u] = 1;
	for (int v : g[u]) {
		dfs(v), s[u] += s[v], siz[u] += siz[v];
	}
	for (int v : g[u]) {
		w[v] = a[u] * s[v];
	}
}
void buildt(int u) {
	wp[u] += w[u];
	for (int v : g[u]) {
		wp[v] += wp[u];
		buildt(v);
	}
}
struct segt { int pos; intl val; } st[N * 4 + 10];
int tg[N * 4 + 10];
segt max(const segt& x, const segt& y) { return x.val > y.val ? x : y; }
void pushup(int u) { st[u] = max(st[u << 1], st[u << 1 | 1]); }
void modify(int u, int val) {
	st[u].val += val, tg[u] += val;
}
void pushdown(int u) {
	if (tg[u]) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u]);
		tg[u] = 0;
	}
}
void update(int u, int l, int r, int lf, int rt, int val) {
	if (lf <= l && r <= rt) return modify(u, val);
	pushdown(u);
	int mid = (l + r) >> 1;
	if (lf <= mid) update(u << 1, l, mid, lf, rt, val);
	if (mid < rt) update(u << 1 | 1, mid + 1, r, lf, rt, val);
	pushup(u);
}
segt query(int u, int l, int r, int lf, int rt) {
	if (lf <= l && r <= rt) return st[u];
	pushdown(u);
	int mid = (l + r) >> 1;
	if (rt <= mid) return query(u << 1, l, mid, lf, rt);
	if (mid < lf) return query(u << 1 | 1, mid + 1, r, lf, rt);
	return max(query(u << 1, l, mid, lf, rt), query(u << 1 | 1, mid + 1, r, lf, rt));
}
void build(int u, int l, int r) {
	if (l == r) {
		int x = idfn[l];
		st[u] = {x, wp[x]};
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}
signed main() {
	cin >> n;
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		g[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	dfs(1), buildt(1), build(1, 1, n);
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
//		cout << w[i] << " " << wp[i] << "\n";
		ans += w[i];
	}
	for (int c = 1; c <= n; c++) {
		auto [pos, val] = st[1];
		for (int u = pos; u != 1; u = fa[u]) {
			if (!w[u]) {
				ans += a[u] * a[pos];
				break;
			}
			update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, -w[u]);
			ans -= w[u], w[u] = 0;
		}
	}
	cout << ans << "\n";
	return 0;
}
