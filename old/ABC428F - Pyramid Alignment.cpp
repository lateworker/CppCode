#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
//
#include <bits/stdc++.h>
using namespace std;
const int N = 200000;
int n, q, a[N + 10];
int lx[N * 4 + 10], len[N * 4 + 10], tg[N * 4 + 10][2];
void pushup(int u) { lx[u] = lx[u << 1 | 1], len[u] = len[u << 1 | 1]; }
void modify(int u, int val, int isr) {
	lx[u] = isr ? val - len[u] + 1 : val;
	tg[u][isr] = val, tg[u][!isr] = 0;
}
void pushdown(int u) {
	int cnt = 0;
	for (int c : {0, 1}) {
		if (tg[u][c]) {
			modify(u << 1, tg[u][c], c);
			modify(u << 1 | 1, tg[u][c], c);
			tg[u][c] = 0;
			++cnt;
		}	
	}
	assert(cnt < 2);
}
void build(int u, int l, int r) {
	if (l == r) {
		lx[u] = 1, len[u] = a[l];
//		tg[u][0] = tg[u][1] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	pushup(u);
}
void update(int u, int l, int r, int lf, int rt, int val, bool isr) {
	if (lf <= l && r <= rt) return modify(u, val, isr);
	int mid = (l + r) >> 1;
	pushdown(u);
	if (lf <= mid) update(u << 1, l, mid, lf, rt, val, isr);
	if (mid < rt) update(u << 1 | 1, mid + 1, r, lf, rt, val, isr);
	pushup(u);
}
int querypos(int u, int l, int r, int pos) {
	if (l == r) return lx[u];
	int mid = (l + r) >> 1;
	pushdown(u);
	return pos <= mid ? querypos(u << 1, l, mid, pos) : querypos(u << 1 | 1, mid + 1, r, pos);
}
int queryid(int u, int l, int r, int x) {
	if (lx[u] > x || lx[u] + len[u] - 1 < x) return 0;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	pushdown(u);
	int res = queryid(u << 1, l, mid, x);
	if (!res) res = queryid(u << 1 | 1, mid + 1, r, x);
	return res;
}
int main() { ffopen();
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; // --a[i];
	}
	a[n + 1] = 1000000000;
	build(1, 1, n + 1);
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int op, x; cin >> op >> x;
		if (op == 1) {
			int p = querypos(1, 1, n + 1, x);
			update(1, 1, n + 1, 1, x, p, false);
		}
		if (op == 2) {
			int p = querypos(1, 1, n + 1, x);
			update(1, 1, n + 1, 1, x, p + a[x] - 1, true);
		}
		if (op == 3) {
			++x;
			cout << n - queryid(1, 1, n + 1, x) + 1 << '\n';
		}
	}
	return 0;
}
