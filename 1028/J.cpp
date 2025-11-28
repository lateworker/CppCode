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
const int N = 200000;
class Segt {
#define mid ((l + r) >> 1)
	int st[N * 4 + 10], tg[N * 4 + 10], tn;
	void pushup(int u) { st[u] = st[u << 1] + st[u << 1 | 1]; }
	void modify(int u, int l, int r, int val) {
		st[u] += (r - l + 1) * val;
		tg[u] += val;
	}
	void pushdown(int u, int l, int r) {
		if (tg[u]) {
			modify(u << 1, l, mid, tg[u]);
			modify(u << 1 | 1, mid + 1, r, tg[u]);
			tg[u] = 0;
		}
	}
	void update(int u, int l, int r, int lf, int rt, int val) {
		if (lf <= l && r <= rt) return modify(u, l, r, val);
		pushdown(u, l, r);
		if (lf <= mid) update(u << 1, l, mid, lf, rt, val);
		if (mid < rt) update(u << 1 | 1, mid + 1, r, lf, rt, val);
		pushup(u);
	}
	int query(int u, int l, int r, int lf, int rt) {
		if (lf <= l && r <= rt) return st[u];
		pushdown(u, l, r);
		if (rt <= mid) query(u << 1, l, mid, lf, rt);
		if (mid < lf) query(u << 1 | 1, mid + 1, r, lf, rt);
		return query(u << 1, l, mid, lf, rt) + query(u << 1 | 1, mid + 1, r, lf, rt);
	}
public:
	void init(int n) {
		tn = n;
		memset(st, 0, (tn * 4 + 5) * sizeof(int));
		memset(tg, 0, (tn * 4 + 5) * sizeof(int));
	}
	void update(int lf, int rt, int val) { this->update(1, 1, tn, lf, rt, val); }
	int query(int lf, int rt) { return this->query(1, 1, tn, lf, rt); }
#undef mid
} st;
int n, a[N + 10];
void apply(int l, int r, int x, int op) {
	int lx = l + x - 1, rx = r + x - 1;
	if (lx > n) return;
	st.update(lx, min(rx, n), op);
}
void slove() {
	cin >> n;
	st.init(n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	int ans = 0;
	vector<tuple<int, int, int> > stk; // val, l, r
	for (int i = 1; i <= n; i++) {
		ans += st.query(1, i);
		cerr << i << '\n';
		int x = abs(a[i] - a[i + 1]), lx = i;
		while (!stk.empty() && get<0>(stk.back()) <= x) {
			int x0, l0, r0; tie(x0, l0, r0) = stk.back();
			apply(l0, r0, x0, -1), lx = l0;
			stk.pop_back();
		}
		apply(lx, i, x, 1);
		stk.emplace_back(x, lx, i);
	}
	cout << ans << '\n';
}
int main() {
	ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}

