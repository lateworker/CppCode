#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
using intl = long long;
const intl N = 200000, LN = __lg(N) + 1, Mod = 1000000007;
int n, tn, ls[N + 10], rs[N + 10], st[LN + 3][N + 10];
int build() {
	vector<int> stk;
	for (int i = 1; i <= n; i++) {
		int lf = 0;
		while (!stk.empty() && st[0][stk.back()] < st[0][i]) lf = stk.back(), stk.pop_back();
		if (!stk.empty()) rs[stk.back()] = i;
		ls[i] = lf, stk.push_back(i);
	} return stk[0];
}
int querygcd(int l, int r) {
	int d = __lg(r - l + 1);
	return __gcd(st[d][l], st[d][r - (1 << d) + 1]);
}
intl ans;
pair<int, int> bsleft(int l, int r, int p) {
	int val = querygcd(r, p);
	while (l < r) {
		int mid = (l + r) >> 1;
		if (querygcd(mid, p) < val) l = mid + 1;
		else r = mid;
	} return {l, val};
}
pair<int, int> bsright(int l, int r, int p) {
	int val = querygcd(p, l);
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (querygcd(p, mid) < val) r = mid - 1;
		else l = mid;
	} return {l, val};
}
void dfs(int i, int l, int r) {
	if (r < l) return;
	if (l == r) {
		ans += (intl) st[0][i] * st[0][i] % Mod, ans %= Mod;
		return;
	}
	vector<pair<int, int> > lvec, rvec;
	for (int j = i, k, val; j >= l; j = k - 1) {
		tie(k, val) = bsleft(l, j, i);
		lvec.emplace_back(val, j - k + 1);
	}
	for (int j = i, k, val; j <= r; j = k + 1) {
		tie(k, val) = bsright(j, r, i);
		rvec.emplace_back(val, k - j + 1);
	}
	for (auto [lval, llen] : lvec)
		for (auto [rval, rlen] : rvec) {
			ans += (intl) st[0][i] * __gcd(lval, rval) % Mod * llen % Mod * rlen % Mod, ans %= Mod;
		}
	dfs(ls[i], l, i - 1), dfs(rs[i], i + 1, r);
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> st[0][i];
	}
	tn = __lg(n);
	for (int j = 1; j <= tn; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	dfs(build(), 1, n);
	cout << ans << "\n";
	return 0;
}
