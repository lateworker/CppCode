#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 100000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m;
intl a[N + 10], b[N + 10], dp[N + 10];
struct Segt {
	intl val, mindp, ans;
	Segt() { val = 0, mindp = inf, ans = inf; }
	Segt(intl val, intl mindp, intl ans) { this->val = val, this->mindp = mindp, this->ans = ans; }
} st[N * 4 + 10];
intl tgv[N * 4 + 10];
#define le (u << 1)
#define ri (u << 1 | 1)
Segt operator + (const Segt& a, const Segt& b) { return Segt(max(a.val, b.val), min(a.mindp, b.mindp), min(a.ans, b.ans)); }
void pushup(int u) { st[u] = st[le] + st[ri]; }
void modify(int u, intl val) { st[u].val = val, st[u].ans = st[u].mindp + val, tgv[u] = val; }
void pushdown(int u) {
	if (tgv[u]) {
		modify(le, tgv[u]);
		modify(ri, tgv[u]);
		tgv[u] = 0;
	}
}
void updateVal(int u, int l, int r, int L, int R, intl val) { // fill
	if (L <= l && r <= R) return modify(u, val);
	int mid = (l + r) >> 1; pushdown(u);
	if (L <= mid) updateVal(le, l, mid, L, R, val);
	if (mid < R) updateVal(ri, mid + 1, r, L, R, val);
	pushup(u);
}
void updateAns(int u, int l, int r, int pos, int dpval) {
	if (l == r) {
		st[u].mindp = dpval;
		st[u].ans = dpval + st[u].val;
		return;
	} int mid = (l + r) >> 1; pushdown(u);
	if (pos <= mid) updateAns(le, l, mid, pos, dpval);
	else updateAns(ri, mid + 1, r, pos, dpval);
	pushup(u);
}
Segt query(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) return st[u];
	int mid = (l + r) >> 1; pushdown(u);
	if (R <= mid) return query(le, l, mid, L, R);
	if (mid < L) return query(ri, mid + 1, r, L, R);
	return query(le, l, mid, L, R) + query(ri, mid + 1, r, L, R);
}
int findposSum(int i) {
	int l = 1, r = i;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (b[i] - b[mid - 1] <= m) r = mid;
		else l = mid + 1;
	} return l;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], b[i] = b[i - 1] + a[i];
	memset(dp, 0x3f, sizeof dp), dp[0] = 0, updateAns(1, 1, n, 1, 0);
	vector<int> stk; stk.push_back(0), a[0] = inf;
	for (int i = 1; i <= n; i++) {
		while (!stk.empty() && a[stk.back()] < a[i]) stk.pop_back();
		updateVal(1, 1, n, stk.back() + 1, i, a[i]);
		dp[i] = query(1, 1, n, findposSum(i), i).ans;
		updateAns(1, 1, n, i + 1, dp[i]);
		stk.push_back(i);
	}
	cout << dp[n] << "\n";
	return 0;
}
