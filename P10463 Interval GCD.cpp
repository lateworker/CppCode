#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 500000;
intl n, m, a[N + 10], st[N * 3 + 10], sm[N * 3 + 10], tn;
#define le (u << 1)
#define ri (u << 1 | 1)
void pushup(int u) { st[u] = gcd(st[le], st[ri]); }
void modifySm(int u, intl val) { for (; u <= n; u += u & -u) sm[u] += val; }
void modify(int u, intl val) {
	modifySm(u, val);
	st[u += tn] += val;
	for (u >>= 1; u; u >>= 1) pushup(u);
}
intl query(int l, int r) {
	intl res = 0;
	for (int u = l; u; u -= u & -u) res += sm[u];
	for (l += tn, r += tn + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~ l & 1) res = gcd(res, st[l ^ 1]);
		if (r & 1) res = gcd(res, st[r ^ 1]);
	} return res;
}
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (tn = 1; tn <= n + 1; tn <<= 1);
	for (int i = 1; i <= n; i++) cin >> a[i], modify(i, a[i] - a[i - 1]);
	for (int i = 1; i <= m; i++) {
		char c; int l, r;
		cin >> c >> l >> r;
		if (c == 'C') {
			intl d; cin >> d;
			modify(l, d), modify(r + 1, -d);
		} else if (c == 'Q') cout << query(l, r) << "\n";
	}
	return 0;
}
