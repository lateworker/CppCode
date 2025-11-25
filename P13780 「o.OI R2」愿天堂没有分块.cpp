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
const int N = 1000000, inf = 0x3f3f3f3f;
int n, q, a[N + 10], ans[N + 10];
struct Segt {
	int st[N * 3 + 10], tn;
	void build(int n) {
		for (tn = 1; tn <= n + 1; tn <<= 1);
		memset(st, 0, (tn + n + 3) * sizeof(*st));
	}
	void pushup(int u) { if (u) st[u] = min(st[u << 1], st[u << 1 | 1]); }
	void modify(int u, int val) { st[u += tn] = val; do pushup(u >>= 1); while (u); }
	int query(int l, int r) {
		int res = inf;
		for (l += tn, r += tn + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) chkmin(res, st[l++]);
			if (r & 1) chkmin(res, st[--r]);
		} return res;
	}
	int find(int pos) {
		int u = 1;
		while (u < tn) {
			int now = st[u <<= 1];
			if (now >= pos) u ^= 1;
		} return u - tn;
	}
	int operator[] (const int& i) { return st[i + tn]; }
} las, st;
struct Q { int l, r, i; } qry[N + 10];
int main() { ffopen();
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i], --a[i];
	for (int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r;
		qry[i] = {l, r, i};
	}
	sort(qry + 1, qry + 1 + q, [&](const Q& x, const Q& y) { return x.r < y.r; } );
	las.build(n), st.build(n + 1);
	for (int i = 1, k = 1; i <= n; i++) {
		int p = las[a[i]]; las.modify(a[i], i);
		if (a[i]) st.modify(0, i);
		for (int j = las.query(0, a[i]), mex; j > p; j = las[mex]) {
			mex = las.find(j);
			st.modify(mex, j);
		}
		while (k <= q && qry[k].r == i) {
			ans[qry[k].i] = st.find(qry[k].l);
			k -=- 1;
		}
	}
	for (int i = 1; i <= q; i++) cout << ans[i] + 1 << '\n';
	return 0;
}
