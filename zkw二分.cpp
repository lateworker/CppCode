#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, Q = 100000, inf = 0x3f3f3f3f;
int n, tn, q, st[N * 2 + 10];
vector<int> vec;
pair<int, int> qry[Q + 10];
void modify(int u, int val) { for (u += tn; u; u >>= 1) st[u] += val; }
int query(int l, int r) {
	int res = 0;
	for (l += tn, r += tn + 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += st[l++];
		if (r & 1) res += st[--r];
	} return res;
}
int fullsearch(int u, int k, int pre) {
	int d = __lg(tn) - __lg(u); u <<= d;
	for (int i = d - 1; i >= 0; i--) {
		int now = pre + st[u >> i];
		if (now < k) pre = now, u += (1 << i);
	} return u - tn;
}
int lowerbs(int l, int r, int k) {
	vector<int> lps, rps;
	for (l += tn, r += tn + 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) lps.push_back(l++);
		if (r & 1) rps.push_back(--r);
	} lps.insert(lps.end(), rps.rbegin(), rps.rend());
	int pre = 0;
	for (auto u : lps) {
		int now = pre + st[u];
		if (k <= now) return fullsearch(u, k, pre);
		pre = now;
	} return r + 1;
}
void ins(int x) { modify(lower_bound(vec.begin(), vec.end(), x) - vec.begin(), 1); }
void del(int x) { modify(lower_bound(vec.begin(), vec.end(), x) - vec.begin(), -1); }
int rnk(int x) { return query(1, lower_bound(vec.begin(), vec.end(), x) - vec.begin() - 1) + 1; }
int kth(int k) { return vec[lowerbs(1, n, k)]; }
int main() { ffopen();
	cin >> q;
	vec.push_back(-inf);
	for (int i = 1; i <= q; i++) {
		int op, x; cin >> op >> x;
		qry[i] = {op, x};
		if (op != 4) vec.push_back(x);
	}
	sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
	n = vec.size() - 1; for (tn = 1; tn <= n + 1; tn <<= 1);
	for (int i = 1; i <= q; i++) {
		auto [op, x] = qry[i];
		if (op == 1) ins(x);
		else if (op == 2) del(x);
		else if (op == 3) cout << rnk(x) << "\n";
		else if (op == 4) cout << kth(x) << "\n";
		else if (op == 5) cout << kth(rnk(x) - 1) << "\n";
		else if (op == 6) cout << kth(rnk(x + 1)) << "\n";
	}
	return 0;
}
