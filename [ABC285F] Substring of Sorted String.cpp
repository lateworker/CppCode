#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int n, a[N + 10], now[30];
#define le (u << 1)
#define ri (u << 1 | 1)
#define mid(l, r) mid = ((l) + (r)) >> 1
struct Dat {
	int lx, rx, cnt[30]; bool chk;
} st[N * 4 + 10];
Dat merge(const Dat& u, const Dat& v) {
	Dat res; res.lx = u.lx, res.rx = v.rx, res.chk = u.chk && v.chk && u.rx <= v.lx;
	for (int c = 1; c <= 26; c++) res.cnt[c] = u.cnt[c] + v.cnt[c];
	return res;
}
void pushup(int u) { st[u] = merge(st[le], st[ri]); }
void modify(int u, int val) {
	for (int c = 1; c <= 26; c++) st[u].cnt[c] = 0;
	st[u].lx = st[u].rx = val, st[u].cnt[val] = 1, st[u].chk = true;
}
void build(int u, int l, int r) {
	if (l == r) return modify(u, a[l]);
	int mid(l, r);
	build(le, l, mid), build(ri, mid + 1, r);
}
void update(int u, int l, int r, int pos, int val) {
	if (l == r) return modify(u, val);
	int mid(l, r);
	pos <= mid ? update(le, l, mid, pos, val) : update(ri, mid + 1, r, pos, val);
	pushup(u);
}
Dat query(int u, int l, int r, int lf, int rt) {
	if (lf <= l && r <= rt) return st[u];
	int mid(l, r);
	if (rt <= mid) return query(le, l, mid, lf, rt);
	if (mid < lf) return query(ri, mid + 1, r, lf, rt);
	return merge(query(le, l, mid, lf, rt), query(ri, mid + 1, r, lf, rt));
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) { char c; cin >> c; a[i] = c - 'a' + 1; }
	build(1, 1, n);
	int q; cin >> q;
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int x; char c; cin >> x >> c;
			c = c - 'a' + 1;
			--now[a[x]], ++now[c];
			a[x] = c, update(1, 1, n, x, a[x]);
		} else
		if (op == 2) {
			int l, r; cin >> l >> r;
			Dat res = query(1, 1, n, l, r);
			int x, y;
			for (int i = 1; i <= 26; i++) if (res.cnt[i]) { x = i; break; }
			for (int i = 26; i >= 1; i--) if (res.cnt[i]) { y = i; break; }
			for (int i = x + 1; i <= y - 1; i++) if (res.cnt[i]) res.chk &= (now[i] == res.cnt[i]);
			cout << (res.chk ? "Yes" : "No") << "\n";
		}
	}
	return 0;
}
