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
const int X = 60, N = 300000;
int n, q;
struct Odt {
	map<int, int> st;
	void init() {
		st.clear();
		st.insert({-1, -1}), st.insert({n + 2, n + 2});
	}
	vector<pii> getseg(pii x) {
		vector<pii> res;
		for (auto u = prev(st.upper_bound(x.first)); ; ) {
			if (u->first > x.second + 1) break;
			if (u->second < x.first - 1) { ++u; continue;}
			res.push_back(*u), st.erase(u++);
		} return res;
	}
	void err() {
		for (auto [l, r] : st) cerr << l << ' ' << r << '\n';
	}
} odt[X + 10];
pii st[N * 2 + 10];
int tg[N * 2 + 10];
pii merge(const pii& x, const pii& y) {
	int ma = max(x.first, y.first);
	return {ma, (x.first == ma) * x.second + (y.first == ma) * y.second};
}
void pushup(int u) { if (u) st[u] = merge(st[u << 1], st[u << 1 | 1]); }
void modify(int u, int val) { st[u].first += val, tg[u] += val; }
void pushdown(int u) {
	if (tg[u]) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u]);
		tg[u] = 0;
	}
}
void update(int l, int r, int val) {
	l += n, r += n + 1;
	for (int d = __lg(n) + 1; d; d--) pushdown(l >> d), pushdown(r >> d);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (u && l == r);
		do pushup(v >>= 1); while (v && l == r);
	}
}
pii query(int l, int r) {
	l += n, r += n + 1;
	for (int d = __lg(n) + 1; d; d--) pushdown(l >> d), pushdown(r >> d);
	pii res = {0, 0};
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = merge(res, st[l++]);
		if (r & 1) res = merge(res, st[--r]);
	} return res;
}
int main() { ffopen();
	cin >> n >> q;
	for (int i = 1; i <= n; i++) st[i + n] = {0, 1};
	for (int i = n - 1; i; i--) pushup(i);
	for (int i = 1; i <= X; i++) odt[i].init();
	for (int i = 1; i <= q; i++) {
//		cerr << i << " CRS---------\n";
//		for (int j : {1, 2}) {
//			cerr << "ODT: " << j << '\n';
//			odt[j].err();
//		}
//		for (int i = 1; i <= n; i++) cerr << i << ' ' << query(i, i).first << ' ' << query(i, i).second << "\n";
//		cerr << "------\n";
		int op, l, r, x;
		cin >> op >> l >> r;
		if (op == 1) {
			cin >> x;
			vector<pii> vec = odt[x].getseg({l, r});
			if (!vec.empty()) {
				int lf = min(l, vec.front().first);
				int rt = max(r, vec.back().second);
				odt[x].st.insert({lf, rt});
			} else odt[x].st.insert({l, r});
			int las = l - 1;
			for (auto [lx, rx] : vec) {
				if (las + 1 <= lx - 1) update(las + 1, lx - 1, 1);
				las = rx;
			}
			if (las + 1 <= r) update(las + 1, r, 1);
//			for (auto [s, t] : vec) cerr << s << ' ' << t << '\n';
		}
		if (op == 2) {
			cin >> x;
			vector<pii> vec = odt[x].getseg({l, r});
			if (!vec.empty()) {
				if (vec.front().first <= l - 1) odt[x].st.insert({vec.front().first, l - 1});
				if (vec.back().second >= r + 1) odt[x].st.insert({r + 1, vec.back().second});
			}
			for (auto [lx, rx] : vec) {
				chkmax(lx, l), chkmin(rx, r);
				if (lx <= rx) update(lx, rx, -1);
			}
//			for (auto [s, t] : vec) cerr << s << ' ' << t << '\n';
		}
		if (op == 3) {
			pii res = query(l, r);
			cout << res.first << ' ' << res.second << '\n';
		}
//		cerr << '\n';
	}
	return 0;
}
/*
4 7
1 1 2 1
1 2 4 2
3 1 3
2 1 2 2
1 2 3 1
3 1 2
3 1 4
*/
