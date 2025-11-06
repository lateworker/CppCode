#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000, LN = __lg(N);
int n, tn, a[N + 10], t[N + 10], ls[N + 10], rs[N + 10], ans;
int st[LN + 2][N + 10];
int stquery(int l, int r) {
	int d = __lg(r - l + 1);
	return max(st[d][l], st[d][r - (1 << d) + 1]);
}
void solve(int u, int l, int r) {
	if (l > r) return;
	if (l == r) { ans += (a[l] == 1); return; }
	solve(ls[u], l, u - 1), solve(rs[u], u + 1, r);
	if (u - l < r - u) {
		for (int nl = u; nl >= l; nl--) {
			int nr = nl + a[u] - 1;
			if (nr < u || nr > r) continue;
			ans += (stquery(nl, nr) < nl);
		}
	} else {
		for (int nr = u; nr <= r; nr++) {
			int nl = nr - a[u] + 1;
			if (nl > u || nl < l) continue;
			ans += (stquery(nl, nr) < nl);
		}
	}
}
int build() {
	vector<int> stk;
	for (int i = 1; i <= n; i++) {
		int lf = 0;
		while (!stk.empty() && a[i] > a[stk.back()]) lf = stk.back(), stk.pop_back();
		if (!stk.empty()) rs[stk.back()] = i;
		ls[i] = lf, stk.push_back(i);
	} return stk[0];
}
int main() { ffopen();
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		st[0][i] = t[a[i]];
		t[a[i]] = i;
	} tn = __lg(n) + 1;
	for (int k = 1; k <= tn; k++)
		for (int i = 1; i + (1 << k) - 1 <= n; i++)
			st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
	solve(build(), 1, n);
	cout << ans << "\n";
	return 0;
}
