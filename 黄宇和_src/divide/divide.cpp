#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 300000, inf = 0x3f3f3f3f, Mod = 998244353;
using intl = long long;
int n, a[N + 10], f[N + 10];
struct seg {
	mutable int l, r;
	bool operator< (const seg& b) const { return l < b.l; }
};
set<seg> st;
void insert(int x) {
	if (st.empty()) { st.insert({x, x}); return; }
	auto u = prev(st.upper_bound({x, x}));
	if (x <= u->r) return;
	if (u->r + 1 == x) u->r = x;
	else st.insert({x, x}), u = next(u);
	auto v = next(u);
	if (v == st.end()) return;
	if (u->r + 1 == v->l) u->r = v->r, st.erase(v);
}
int query() {
	auto u = next(st.begin());
	return u->l ? 0 : u->r + 1;
}
int gmex() {
	vector<int> t(N + 5, 0);
	for (int i = 1; i <= n; i++) ++t[a[i]];
	for (int i = 0; i <= n; i++) if (!t[i]) return i;
	return n + 1;
}
int main() { ffopen(divide);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int mex = gmex(); f[0] = 1;
	for (int i = 1; i <= n; i++) {
		st = {{-inf, -inf}};
		for (int j = i; j >= 1; j--) {
			insert(a[j]);
			int k = query();
			if (k > mex) break;
			if (k < mex) continue;
			f[i] = (intl) (f[i] + f[j - 1]) % Mod;
		}
	}
	cout << f[n] << "\n";
	return 0;
}
