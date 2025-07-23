#include <bits/stdc++.h>
#define mid(l, r) mid = (((l) + (r)) >> 1)
using namespace std;
template<size_t N>
struct SEGT {
	struct Segt {
		Segt *le, *ri;
		int val, tag;
		Segt() { le = ri = this, val = tag = 0; }
	} *root;
	inline static size_t psz;
	inline static Segt pool[N];
	
	void pushup(Segt* u) { u->val = u->le->val + u->ri->val; }
	void modify(Segt* u, int l, int r, int val) {
		u->val += (r - l + 1) * val;
		u->tag += val;
	}
	void pushdown(Segt* u, int l, int r) {
		if (u->tag) {
			int mid(l, r);
			modify(u->le, l, mid, u->tag);
			modify(u->ri, mid + 1, r, u->tag);
			u->tag = 0;
		}
	}
	void update(Segt*& u, int l, int r, int lf, int rt, int val) {
		if (u == pool) u = node();
		if (lf <= l && r <= rt) return modify(u, l, r, val);
		int mid(l, r); pushdown(u, l, r);
		if (lf <= mid) update(u->le, l, mid, lf, rt, val);
		if (mid < rt) update(u->ri, mid + 1, r, lf, rt, val);
		pushup(u);
	}
	int query(Segt* u, int l, int r, int lf, int rt) {
		if (u == pool) return 0;
		if (lf <= l && r <= rt) return u->val;
		int mid(l, r); pushdown(u, l, r);
		if (rt <= mid) return query(u->le, l, mid, lf, rt);
		if (mid < lf) return query(u->ri, mid + 1, r, lf, rt);
		return query(u->le, l, mid, lf, rt) + query(u->ri, mid + 1, r, lf, rt);
	}
	
public:
	SEGT() { root = pool; }
	static Segt* node() { Segt* u = pool + ++ psz; u->le = u->ri = pool; return u; }
	void update(int l, int r, int lf, int rt, int val) { update(root, l, r, lf, rt, val); }
	int query(int l, int r, int lf, int rt) { return query(root, l, r, lf, rt); }
};

const int N = 100000;
int n, m;
int main() {
	cin >> n >> m;
	SEGT<N * 4 + 10> st;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		st.update(1, n, i, i, x);
	}
	for (int i = 1; i <= m; i++) {
		int op, x, y, k; cin >> op;
		if (op == 1) {
			cin >> x >> y >> k;
			st.update(1, n, x, y, k);
		} else
		if (op == 2) {
			cin >> x >> y;
			cout << st.query(1, n, x, y) << "\n";
		}
	}
	return 0;
}
