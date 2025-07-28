#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using ldouble = long double;
const int N = 100000;
const ldouble eps = 1e-9;
int cmp(const ldouble& x, const ldouble& y) {
	if (x - y > eps) return +1;
	if (y - x > eps) return -1;
	return 0;
}
int n, psz;
struct line {
	int idx;
	ldouble k, b;
	ldouble at(ldouble x0) const { return k * x0 + b; }
	bool greater_at(const line& b, ldouble x0) const {
		if (!idx) return false;
		if (!b.idx) return true;
		return cmp(at(x0), b.at(x0)) > 0 || (cmp(at(x0), b.at(x0)) == 0 && idx < b.idx);
	}
	void conv(int x1, int y1, int x2, int y2) {
		if (x1 == x2) { k = 0, b = max(y1, y2); return; }
		k = (ldouble) (y2 - y1) / (x2 - x1);
		b = (ldouble) y1 - k * x1;
	}
};
struct segt {
	line val;
	segt *le, *ri;
	segt() { le = ri = this, val = {0, 0, 0}; }
} pool[N + 10];
segt* node() {
	segt* u = pool + (++psz);
	u->le = u->ri = pool;
	return u;
}
void insert(segt*& u, int l, int r, line val) {
	if (u == pool) { u = node(); u->val = val; return; }
	int mid = (l + r) >> 1;
	if (val.greater_at(u->val, mid)) swap(val, u->val);
	if (val.greater_at(u->val, l)) insert(u->le, l, mid, val);
	if (val.greater_at(u->val, r)) insert(u->ri, mid + 1, r, val);
}
void insert_seg(segt*& u, int l, int r, int lf, int rt, const line& val) {
	if (u == pool) u = node();
	if (lf <= l && r <= rt) return insert(u, l, r, val);
	int mid = (l + r) >> 1;
	if (lf <= mid) insert_seg(u->le, l, mid, lf, rt, val);
	if (mid < rt) insert_seg(u->ri, mid + 1, r, lf, rt, val);
}
line query(segt* u, int l, int r, int x0) {
	if (u == pool) return {0, 0, 0};
	if (l == r) return u->val;
	int mid = (l + r) >> 1;
	line res = x0 <= mid ? query(u->le, l, mid, x0) : query(u->ri, mid + 1, r, x0);
	return u->val.greater_at(res, x0) ? u->val : res;
}
int main() {
	cin >> n;
	int last = 0, c = 0;
	auto decode = [&](int& x, const int& Mod) { x = (x + last - 1) % Mod + 1; };
	segt* root = pool;
	for (int i = 1; i <= n; i++) {
		int op; cin >> op;
		if (op == 0) {
			int x0; cin >> x0;
			decode(x0, 39989);
			last = query(root, 1, 39989, x0).idx;
			cout << last << "\n";
		} else {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			decode(x1, 39989), decode(y1, 1000000000), decode(x2, 39989), decode(y2, 1000000000);
			if (x1 > x2) swap(x1, x2), swap(y1, y2);
			line now;
			now.conv(x1, y1, x2, y2), now.idx = ++c;
			insert_seg(root, 1, 39989, x1, x2, now);
		}
	}
	return 0;
}
