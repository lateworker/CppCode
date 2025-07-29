#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
template<class T_> inline void chkmax(T_& x, const T_& y) { x = max(x, y); }
const int N = 200000;
int n, m, tn, a[N * 2 + 10];
//int f[N + 10];
vector<int> vec;
struct tnum {
	int st[N + 10];
	void modify(int u, int val) {
		u = upper_bound(vec.begin(), vec.end(), u) - vec.begin();
		for (; u <= tn; u += u & -u) chkmax(st[u], val);
	}
	int query(int u) {
		int res = 0;
		u = upper_bound(vec.begin(), vec.end(), u) - vec.begin();
		for (; u; u -= u & -u) chkmax(res, st[u]);
		return res;
	}
} st;
bool check(int lim) {
	if (lim < a[1]) return false;
	fill(st.st + 1, st.st + tn + 1, 0);
	st.modify(a[1], 1);
	for (int i = 2; i <= n; i++) {
		int f = st.query(lim - a[i]);
		st.modify(a[i], f + 1);
	}
	for (int i = 2; i <= n; i++) {
		if (a[i] + a[1] <= lim && st.query(a[i]) >= m) return true;
	}
	return false;
}
void doshift() {
	int p = min_element(a + 1, a + 1 + n) - a;
	for (int i = 1; i < p; i++) a[i + n] = a[i];
	for (int i = 1; i <= n; i++) a[i] = a[i + p - 1];
}
int main() { ffopen(seq);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		vec.push_back(a[i]);
	}
	doshift();
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	tn = vec.size();
	int l = 0, r = 100000000;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << "\n";
	return 0;
}
