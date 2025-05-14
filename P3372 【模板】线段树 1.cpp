#include <bits/stdc++.h>
#define mid(l, r) mid = (((l) + (r)) >> 1)
using namespace std;
template<class val_t, class tag_t, size_t N>
struct SEGT {
	struct Segt {
		Segt *le, *ri;
		val_t val;
		int tag;
		Segt() { le = ri = this, val = tag = 0; }
	} *root; int L, R;
	
	SEGT(int L, int R) { root = pool, this->L = L, this->R = R; }
	
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
	
	static Segt pool[N]; static size_t psz;
	Segt* node() { Segt* u = pool + ++ psz; u->le = u->ri = pool; return u; }
	void update(int lf, int rt, int val) { update(root, L, R, lf, rt, val); }
	int query(int lf, int rt) { return query(root, L, R, lf, rt); }
};
template<class val_t, class tag_t, size_t N>
SEGT<val_t, tag_t, N>::Segt SEGT<val_t, tag_t, N>::pool[N];
template<class val_t, class tag_t, size_t N>
size_t SEGT<val_t, tag_t, N>::psz = 0;

const int N = 100000;
int n, m;
int main() {
	cin >> n >> m;
	SEGT<int, int, N * 4 + 10> st(1, n);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		st.update(i, i, x);
	}
	for (int i = 1; i <= m; i++) {
		int op, x, y, k; cin >> op;
		if (op == 1) {
			cin >> x >> y >> k;
			st.update(x, y, k);
		} else
		if (op == 2) {
			cin >> x >> y;
			cout << st.query(x, y) << "\n";
		}
	}
	return 0;
}
