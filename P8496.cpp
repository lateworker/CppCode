#include <bits/stdc++.h>
using namespace std;
const int N = 500000;
struct Segt {
	struct Dat {
		int cnt, mas, pos;
		Dat operator + (const Dat& b) const {
			Dat res = {cnt + b.cnt, max(mas, b.mas), 0};
			res.pos = mas == res.mas ? pos : b.pos;
			return res;
		}
	} val;
	Segt *le, *ri;
	Segt() { val = {0, 0, 0}, le = ri = this; }
} null[N * 10]; // N * 10 ???
void pushup(Segt* u) { u->val = u->le->val + u->ri->val; }
vector<Segt*> rcy; int psz;
Segt* node() {
	Segt* u = rcy.empty() ? null + (++psz) : rcy.back();
	if (!rcy.empty()) rcy.pop_back();
	u->le = u->ri = null;
	u->val = {0, 0, 0};
	return u;
}
Segt* copy(Segt* v) { Segt* u = node(); *u = *v; return u; }
void modify(Segt*& u, int l, int r, int pos, int val) {
	if (u == null) u = node();
	if (l == r) { u->val = {1, 1, l}; return; }
	int mid = (l + r) >> 1;
	pos <= mid ? modify(u->le, l, mid, pos, val) : modify(u->ri, mid + 1, r, pos, val);
	pushup(u);
}
Segt* merge(Segt* u, Segt* v, int l, int r, bool ct) {
	if (u == null) return v;
	if (v == null) return u;
	if (ct) u = copy(u);
	if (l == r) {
		int cnt = u->val.cnt + v->val.cnt;
		u->val = {cnt, cnt, l};
//		if (!ct) rcy.push_back(v);
		return u;
	}
	int mid = (l + r) >> 1;
	u->le = merge(u->le, v->le, l, mid, ct);
	u->ri = merge(u->ri, v->ri, mid + 1, r, ct);
//	if (!ct) rcy.push_back(v);
	pushup(u); return u;
}
int n, m[N + 10], q;
list<int> a[N + 10];
Segt* root[N + 10];
int main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> m[i];
		for (int j = 1; j <= m[i]; j++) {
			int x; cin >> x;
			a[i].push_back(x);
		}
	}
	for (int i = 1; i <= q; i++) {
		int op; cin >> op;
		if (op == 1) {
			int x, y; cin >> x >> y;
			a[x].push_back(y);
			modify(root[x], 1, n + q, y, 1);
		} else
		if (op == 2) {
			int x; cin >> x;
			int y = a[x].back(); a[x].pop_back();
			modify(root[x], 1, n + q, y, -1);
		} else
		if (op == 3) {
			int r, x; cin >> r;
			Segt* now = null;
			for (int i = 1; i <= r; i++) {
				cin >> x;
				now = merge(now, root[x], 1, n + q, true);
			}
			cout << (now->val.mas * 2 > now->val.cnt ? now->val.pos : -1) << "\n";
		} else
		if (op == 4) {
			int x, y, z;
			cin >> x >> y >> z;
			a[z].insert(a[z].end(), a[x].begin(), a[x].end());
			a[z].insert(a[z].end(), a[y].begin(), a[y].end());
			a[x].clear(), a[y].clear();
			root[z] = merge(root[x], root[y], 1, n + q, false);
			root[x] = root[y] = null;
		}
	}
	return 0;
}
