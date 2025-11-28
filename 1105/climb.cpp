#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const intl N = 100000, Mod = 998244353;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl inv(intl a) { return fpow(a, Mod - 2); }
int n, tn, q, fa[N + 10], dfn[N + 10], siz[N + 10], psz;
intl a[N + 10], w[N + 10], sw[N + 10];
vector<int> g[N + 10];
void gdfn(int u) {
	siz[u] = 1, dfn[u] = ++psz;
	for (int v : g[u]) {
		gdfn(v);
		siz[u] += siz[v];
	}
}
intl f[N * 2 + 10], pi[N * 2 + 10], tg[N * 2 + 10];
void domod(intl& x) { x = (x % Mod + Mod) % Mod; }
void dfs(int u) {
	intl isum = inv(sw[u]);
	for (int v : g[u]) {
		pi[dfn[v] + tn] = pi[dfn[u] + tn] * w[v] % Mod * isum % Mod;
		dfs(v);
	}
}
void modify(int u, intl val) {
	f[u] *= val, pi[u] *= val, tg[u] *= val;
	domod(f[u]), domod(pi[u]), domod(tg[u]);
}
void pushdown(int u) {
	if (tg[u] != 1) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u]);
		tg[u] = 1;
	}
}
void pushup(int u) {
	if (u) f[u] = f[u << 1] + f[u << 1 | 1], domod(f[u]);
}
void update(int l, int r, intl val) {
	l += tn, r += tn + 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	}
}
void modifyf(int u, intl val) {
	u += tn;
	for (int i = __lg(n) + 1; i; i--) pushdown(u >> i);
	f[u] += val, domod(f[u]);
	do pushup(u >>= 1); while(u);
}
pair<intl, intl> query(int u) {
	u += tn;
	for (int i = __lg(n) + 1; i; i--) pushdown(u >> i);
	return {f[u], pi[u]};
}
int main() { ffopen(climb);
	cin >> n; tn = n - 1;
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		g[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		sw[fa[i]] += w[i];
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	gdfn(1), pi[1 + tn] = 1, dfs(1);
	for (int u = 1; u <= n; u++) {
		f[dfn[u] + tn] = a[u] * pi[dfn[u] + tn] % Mod;
	}
	for (int i = 0; i <= tn + n; i++) tg[i] = 1;
	for (int i = tn; i; i--) pushup(i);
	cout << f[1] << '\n';
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int u; intl nw, na;
		cin >> u >> nw >> na;
		intl pi_u, f_u;
		tie(f_u, pi_u) = query(dfn[u]);
		modifyf(dfn[u], ((na - a[u]) * pi_u % Mod + Mod) % Mod);
		a[u] = na;
		int p = fa[u];
		intl nsw = sw[p] - w[u] + nw;
		intl insw = inv(nsw);
		update(dfn[p] + 1, dfn[p] + siz[p] - 1, sw[p] * insw % Mod);
		if (p) update(dfn[u], dfn[u] + siz[u] - 1, nw * inv(w[u]) % Mod);
		w[u] = nw, sw[p] = nsw;
		
		cout << f[1] << '\n';
	}
	return 0;
}
