#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 200000;
int n, m, q, a[N + 10];
struct seg { mutable int l, r; };
bool operator < (const seg& u, const seg& v) { return u.l == v.l ? u.r < v.r : u.l < v.l; }
set<seg> col[N + 10];
int last[N + 10], ans[N + 10];
vector<int> evt[N * 4 + 10];
void update(int u, int l, int r, int lf, int rt, int c) {
	if (lf <= l && r <= rt) return evt[u].push_back(c);
	int mid = (l + r) >> 1;
	if (lf <= mid) update(u << 1, l, mid, lf, rt, c);
	if (mid < rt) update(u << 1 | 1, mid + 1, r, lf, rt, c);
}
set<seg> st;
void ins(seg x) {
	if (st.empty()) { st.insert(x); return; }
	auto u = st.upper_bound(x);
	if (x.r + 1 == u->l) u->l = x.l;
	else st.insert(x), --u;
	if (u == st.begin()) return;
	if (prev(u)->r + 1 == u->l) {
		int nl = prev(u)->l;
		st.erase(prev(u));
		u->l = nl;
	}
}
void solve(int u, int l, int r) {
	set<seg> bkp = st;
	for (int c : evt[u]) {
		for (seg x : col[c]) ins(x);
	}
	if (l == r) {
		ans[l] = st.size();
	} else {
		int mid = (l + r) >> 1;
		solve(u << 1, l, mid);
		solve(u << 1 | 1, mid + 1, r);
	}
	st = bkp;
}
void print(int u, int l, int r) {
	cout << u << " " << l << " " << r << "\n";
	for (int c : evt[u]) cout << c << " "; cout << "\n";
	if (l == r) return;
	int mid = (l + r) >> 1;
	print(u << 1, l, mid);
	print(u << 1 | 1, mid + 1, r);
}
int main() {
	ffopen("bulb");
	cin >> n >> q >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (col[a[i]].empty()) col[a[i]].insert({i, i});
		else {
			auto now = col[a[i]].end();
			if (now->r + 1 == i) now->r = i;
			else col[a[i]].insert({i, i});
		}
	}
//	for (int i = 1; i <= m; i++) {
//		cout << i << "\n";
//		for (auto [l, r] : col[i]) cout << l << " " << r << "\n";
//	}
	for (int i = 1; i <= q; i++) {
		int x; cin >> x;
		if (last[x]) update(1, 1, q, last[x], i - 1, x), last[x] = 0;
		else last[x] = i;
	}
	for (int i = 1; i <= m; i++) {
		if (last[i]) update(1, 1, q, last[i], q, i);
	}
//	print(1, 1, q);
	solve(1, 1, q);
	for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
	return 0;
}
