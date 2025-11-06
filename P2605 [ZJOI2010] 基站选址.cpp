#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 20000, K = 100, inf = 0x3f3f3f3f;
int n, m, d[N + 5], c[N + 5], s[N + 5], w[N + 5], dp[N + 5][K + 5];
struct Segt {
	int st[N * 2 + 5], tg[N * 2 + 5];
	void pushup(int u) { if (!u) return; st[u] = min(st[u << 1], st[u << 1 | 1]); }
	void modify(int u, int val) { st[u] += val, tg[u] += val; }
	void pushdown(int u) {
		if (tg[u]) {
			modify(u << 1, tg[u]);
			modify(u << 1 | 1, tg[u]);
			tg[u] = 0;
		}
	}
	void update_add(int l, int r, int val) {
		l += n, r += n + 1;
		for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
		for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
			if (l & 1) u = l, modify(l++, val);
			if (r & 1) v = r, modify(--r, val);
			do pushup(u >>= 1); while (l == r && u);
			do pushup(v >>= 1); while (l == r && v);
		}
	}
	void update_min(int pos, int val) {
		pos += n;
		for (int i = __lg(n) + 1; i; i--) pushdown(pos >> i);
		st[pos] = min(st[pos], val);
		do pushup(pos >>= 1); while (pos);
	}
	int query(int l, int r) {
		l += n, r += n + 1;
		for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
		int res = inf;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = min(res, st[l++]);
			if (r & 1) res = min(res, st[--r]);
		} return res;
	}
	void build() {
		for (int i = 1; i <= n; i++) {
			st[i + n] = inf, tg[i + n] = 0;
		}
		for (int u = n - 1; u; u--) pushup(u);
	}
} st[K + 5];
vector<int> g[N + 5];
void prepare() {
	for (int i = 2; i < n; i++) {
		int r = upper_bound(d + 1, d + 1 + n, d[i] + s[i]) - d - 1;
		g[r].push_back(i);
	}
}
signed main() {
	cin >> n >> m; n += 2, m += 2;
	for (int i = 3; i < n; i++) cin >> d[i];
	d[1] = -inf, d[n] = inf;
	for (int i = 2; i < n; i++) cin >> c[i];
	for (int i = 2; i < n; i++) cin >> s[i];
	for (int i = 2; i < n; i++) cin >> w[i];
	prepare();
	memset(dp, 0x3f, sizeof dp);
	for (int k = 1; k <= m; k++) st[k].build();
	dp[1][1] = 0, st[1].update_min(1, 0);
	for (int i = 2; i <= n; i++) {
		for (int k = 1; k <= m; k++)
			for (int j : g[i - 1]) {
				int l = lower_bound(d + 1, d + 1 + n, d[j] - s[j]) - d;
				st[k].update_add(1, l - 1, w[j]);
			}
		for (int k = 2; k <= min(m, i); k++) {
			int res = st[k - 1].query(k - 1, i - 1);
			dp[i][k] = min(dp[i][k - 1], res + c[i]);
			st[k].update_min(i, dp[i][k]);
		}
	}
	cout << dp[n][m] << "\n";
	return 0;
}
