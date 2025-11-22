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
const int N = 1000000;
int n, q, a[N + 10], ans[N + 10];
struct Segt {
	Segt *le, *ri;
	int val;
	Segt() { le = ri = this; val = 0; }
} pool[N * 8 + 10]; int psz;
Segt* node() {
	Segt* u = pool + (++psz);
	u->le = u->ri = pool;
	u->val = 0;
	return u;
}
Segt* copy(Segt* u) { Segt* v = node(); *v = *u; return v; }
void pushup(Segt* u) { if (u != pool) u->val = min(u->le->val, u->ri->val); }
void update(Segt*& u, int l, int r, int pos, int val, bool ctr = true) {
	if (ctr) u = copy(u);
	else if (u == pool) u = node();
	if (l == r) { u->val = val; return; }
	int mid = (l + r) >> 1;
	pos <= mid ? update(u->le, l, mid, pos, val) : update(u->ri, mid + 1, r, pos, val);
	pushup(u);
}
int query(Segt* u, int l, int r, int pos) {
	if (u == pool) return l;
	if (u->val >= pos) return -1;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	int res = query(u->le, l, mid, pos);
	if (res == -1) res = query(u->ri, mid + 1, r, pos);
	return res;
}
Segt* root[N + 10];
vector<int> g[N + 10];
vector<pii> seg[N + 10], qry[N + 10], evt[N + 10];
int main() { ffopen();
	cin >> n >> q;
	root[0] = pool;
	for (int i = 1; i <= n; i++) {
		cin >> a[i], --a[i];
		update(root[i] = root[i - 1], 0, n, a[i], i);
		g[a[i]].push_back(i);
		seg[!a[i]].emplace_back(i, i);
	}
	for (int i = 1; i < n; i++) {
		for (auto [l, r] : seg[i]) {
			auto u = upper_bound(g[i].begin(), g[i].end(), r);
			if (u != g[i].end()) seg[query(root[*u], 0, n, l)].emplace_back(l, *u);
			u = lower_bound(g[i].begin(), g[i].end(), l);
			if (u != g[i].begin()) --u, seg[query(root[r], 0, n, *u)].emplace_back(*u, r);
		}
	}
	for (int i = 0; i <= n; i++) {
		sort(seg[i].begin(), seg[i].end(), [&](const pii& x, const pii& y) {
			return x.second == y.second ? x.first > y.first : x.second < y.second;
		} );
		vector<pii> now;
		int mal = 0;
		for (auto [l, r] : seg[i]) {
			if (l > mal) {
				now.emplace_back(l, r);
				evt[r].emplace_back(l, i);
			}
			chkmax(mal, l);
		}
		seg[i].swap(now);
//		cerr << i << '\n';
//		for (auto[ l, r] : seg[i]) cerr << l << ' ' << r << '\n';
	}
	for (int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r;
		qry[r].emplace_back(l, i);
	}
	psz = 0; Segt* rt = pool;
	for (int i = 1; i <= n; i++) {
		for (auto [j, mex] : evt[i]) {
			update(rt, 0, n, mex, j, false);
			assert(pool->val == 0);
		}
		for (auto [j, idx] : qry[i]) {
			ans[idx] = query(rt, 0, n, j) + 1;
		}
	}
	for (int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}
