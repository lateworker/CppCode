#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, inf = 0x3f3f3f3f;
int n, a[N + 10], f[N + 10];
struct Segt {
	int st[N * 2 + 10];
	void modify(int u, int val) {
		for (u += n; u; u >>= 1) st[u] = max(st[u], val);
	}
	int query(int l, int r) {
		int res = 0;
		for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = max(res, st[l++]);
			if (r & 1) res = max(res, st[--r]);
		} return res;
	}
} st;
int main() { ffopen();
	vector<int> vec;
	while (cin >> a[++n]) vec.push_back(a[n]);
	n--; sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
	st.modify(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		f[i] = st.query(a[i], n + 1) + 1;
		st.modify(a[i], f[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
	cout << ans << "\n";
	vec.clear();
	for (int i = 1; i <= n; i++) {
		if (vec.empty()) { vec.push_back(a[i]); continue; }
		auto u = lower_bound(vec.begin(), vec.end(), a[i]);
		if (u == vec.end()) vec.push_back(a[i]);
		else *u = a[i];
	}
	cout << vec.size() << "\n";
	return 0;
}
