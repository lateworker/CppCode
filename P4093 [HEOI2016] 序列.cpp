#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
const int N = 100000;
int n, m, a[N + 10], ma[N + 10], mi[N + 10], f[N + 10];
pair<int, int> now[N + 10];
struct Tnum {
	int st[N + 10], lim;
	void modify(int u, int val) { for (; u <= lim; u += u & -u) chkmax(st[u], val); }
	void clear(int u) { for (; u <= lim; u += u & -u) st[u] = 0; }
	int query(int u) { int res = 0; for (; u; u -= u & -u) chkmax(res, st[u]); return res; }
} st;
void cdq(int l, int r) {
	if (l == r) { chkmax(f[l], 1); return; }
	int mid = (l + r) >> 1;
	cdq(l, mid);
	for (int i = l; i <= mid; i++) now[i] = {ma[i], a[i]};
	for (int i = mid + 1; i <= r; i++) now[i] = {a[i], mi[i]};
	vector<int> vec(r - l + 1); iota(vec.begin(), vec.end(), l);
	sort(vec.begin(), vec.end(), [&](int i, int j) {
		const int &x = now[i].first, &y = now[j].first;
		return x == y ? i < j : x < y;
	} );
	for (int i : vec) {
		if (i <= mid) st.modify(now[i].second, f[i]);
		else chkmax(f[i], st.query(now[i].second) + 1);
	}
	for (int i : vec) if (i <= mid) st.clear(now[i].second);
	cdq(mid + 1, r);
}
int main() { ffopen();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], ma[i] = mi[i] = a[i];
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		chkmax(ma[x], y);
		chkmin(mi[x], y);
	}
	st.lim = *max_element(ma + 1, ma + 1 + n);
	cdq(1, n);
	cout << *max_element(f + 1, f + 1 + n) << "\n";
	return 0;
}
