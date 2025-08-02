#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 200000;
int n, q, st[N * 3 + 10], tn;
void pushup(int u) {
	if (!u) return;
	st[u] = max(st[u << 1], st[u << 1 | 1]);
}
void modify(int u, int val) {
	st[u += tn - 1] = val;
	do pushup(u >>= 1); while (u);
}
int query(int l, int r) {
	int res = 0;
	for (l += tn - 1, r += tn; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = max(res, st[l++]);
		if (r & 1) res = max(res, st[--r]);
	} return res;
}
int sf(int u, int val, int pre) {
	int d = __lg(tn) - __lg(u); u <<= d;
	for (int i = d - 1; ~i; i--) {
		int now = max(pre, st[u >> i]);
		if (now < val) pre = now, u += 1 << i;
	} return u - tn + 1;
}
int bs(int l, int r, int val) {
	vector<int> lps, rps;
	for (l += tn - 1, r += tn; l < r; l >>= 1, r >>= 1) {
		if (l & 1) lps.push_back(l++);
		if (r & 1) rps.push_back(--r);
	} lps.insert(lps.end(), rps.rbegin(), rps.rend());
	int pre = 0;
	for (int u : lps) {
		int now = max(pre, st[u]);
		if (now >= val) return sf(u, val, pre);
		pre = now;
	} return n + 1;
}
int main() { ffopen();
	cin >> n >> q;
	for (tn = 1; tn <= n; tn <<= 1);
	for (int i = 1; i <= n; i++) cin >> st[i + tn - 1];
	for (int u = tn - 1; u; u--) st[u] = max(st[u << 1], st[u << 1 | 1]);
	for (int i = 1; i <= q; i++) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1) modify(x, y);
		else if (op == 2) cout << query(x, y) << "\n";
		else if (op == 3) cout << bs(x, n, y) << "\n";
	}
	return 0;
}
