#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
const int N = 1000000;
int n, q, a[N + 10];
struct Pair { mutable int l, r; bool operator< (const Pair& b) const { return r < b.r; } } qry[N + 10];
set<Pair> st[N + 10];
vector<int> tg[N * 2 + 10];
void apply(int u, const vector<int>& vec) {
	for (const int& val : vec) tg[u].push_back(val);
}
void pushdown(int u) {
	if (!tg[u].empty()) {
		apply(u << 1, tg[u]);
		apply(u << 1 | 1, tg[u]);
		tg[u].clear();
	}
}
int query(int u) {
	u += n - 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(u >> i);
	
}
int main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= q; i++) cin >> qry[i].l >> qry[i].r;
	sort(qry + 1, qry + q + 1);
	for (int i = 1; i <= q; i++) {
		
	}
	return 0;
}
