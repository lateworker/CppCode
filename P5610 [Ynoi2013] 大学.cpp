#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 100000, A = 500000;
struct Treap { int lson, rson, idx, pri; } st[N * 20 + 10]; int psz;
#define le(u) st[u].lson
#define ri(u) st[u].rson
int node(int idx) { st[++psz] = {0, 0, idx, rand()}; return psz; }
void split(int u, int idx, int& L, int& R) {
	if (u == 0) return void(L = R = 0);
	if (st[le(u)].idx >= idx) split(le(u), idx, L, le(u)), R = u;
	else split(ri(u), idx, ri(u), R), L = u;
}
int merge(int u, int v) {
	if (u == 0 || v == 0) return u | v;
	if (st[u].pri > st[v].pri) { ri(u) = merge(ri(u), v); return u; }
	else { le(v) = merge(u, le(v)); return v; }
}
int n, m, a[N + 10], rt[int(sqrt(A)) + 10];
intl b[N + 10];
void tnumUpdate(int u, intl val) { for (; u <= n; u += u & -u) b[u] += val; }
intl tnumQuery(int u) { intl res = 0; for (; u; u -= u & -u) res += b[u]; return res; }
int dfs(int u, int x) {
	if (u == 0) return 0;
	int i = st[u].idx;
	tnumUpdate(i, - a[i]);
	tnumUpdate(i, a[i] /= x);
	int now = 0, L = le(u), R = ri(u);
	if (a[i] > 1) now = u, le(u) = ri(u) = 0;
	return merge(merge(dfs(L, x), now), dfs(R, x));
}
void print(int u) {
	if (u == 0) return ;
	print(le(u));
	cout << st[u].idx << " ";
	print(ri(u));
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; tnumUpdate(i, a[i]);
		for (intl x = 2, y; x * x <= a[i]; x++) {
			if (a[i] % x) continue;
			rt[x] = merge(rt[x], node(i));
			if (x * x == a[i]) continue;
			y = a[i] / x;
			rt[y] = merge(rt[y], node(i));
		} rt[a[i]] = merge(rt[a[i]], node(i));
	}
	for (int i = 1; i <= m; i++) {
		int op, l, r, x;
		cin >> op >> l >> r;
		if (op == 1) {
			cin >> x;
			if (x == 1) continue;
			int L, now, R;
			split(rt[x], r, L, R), split(rt[x], l - 1, L, now);
			now = dfs(now, x);
			rt[x] = merge(merge(L, now), R);
		} else if (op == 2) {
			cout << tnumQuery(r) - tnumQuery(l - 1) << "\n";
			for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
			cout << "-----\n";
			for (int i = 2; i <= 5; i++) print(i), cout << "\n";
			cout << "-----\n";
		}
	}
	return 0;
}
