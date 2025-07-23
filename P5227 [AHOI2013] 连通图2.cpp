#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000;
int n, m, q, col[N + 10], down[N + 10];
vector<int> tim[M + 10], pnt[N * 4 + 10], evt[N * 4 + 10];
pair<int, int> e[M + 10];
void update(int u, int l, int r, int lf, int rt, int i) {
	pnt[u].push_back(e[i].first);
	pnt[u].push_back(e[i].second);
	if (lf <= l && r <= rt) { evt[u].push_back(i); return; }
	int mid = (l + r) >> 1;
	if (lf <= mid) update(u << 1, l, mid, lf, rt, i);
	if (mid < rt) update(u << 1 | 1, mid + 1, r, lf, rt, i);
}
bool adj[N + 10];
void adjust(int u, int l, int r) {
	vector<int> vec;
	for (int x : pnt[u]) adj[x] = false;
	for (int x : pnt[u]) if (!adj[x]) adj[x] = true, vec.push_back(x);
	pnt[u].swap(vec);
	if (l == r) { down[l] = u; return; }
	int mid = (l + r) >> 1;
	adjust(u << 1, l, mid), adjust(u << 1 | 1, mid + 1, r);
}
void unik(vector<int>& vec) {
	vector<int> res;
	for (int x : vec) adj[x] = false;
	for (int x : vec) if (!adj[x]) adj[x] = true, res.push_back(x);
	vec.swap(res);
}
bool ans[N * 4 + 10];

int ffind(int u) { return col[u] == u ? u : col[u] = ffind(col[u]); }

void cdq(int u, int l, int r) {
	unik(pnt[u]);
	
	if (u != 1) {
		
	} else ans[u] = true;
	
//	vector<int> vec;
//	for (int x : pnt[u])

	for (int i : evt[u]) {
		auto [x, y] = e[i];
		if (col[x] == col[y]) continue;
		col[col[x]] = col[y];
	}

	if (l == r) {
		auto check = [&]() {
			if (pnt[u].empty()) return true;
			int c = tag[col[pnt[u].front()]];
			for (int x : pnt[u]) {
				if (c != tag[col[x]]) return false;
			} return true;
		}; ans[u] &= check();
	} else {
		int mid = (l + r) >> 1;
		cdq(u << 1, l, mid);
		cdq(u << 1 | 1, mid + 1, r);
	}
}
int query(int i) {
	for (int u = down[i]; u; u >>= 1)
		if (!pnt[u].empty()) return ans[u];
	return false;
}
int main() { // cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> e[i].first >> e[i].second;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int c; cin >> c;
		for (int j = 1; j <= c; j++) {
			int x; cin >> x;
			tim[x].push_back(i);
		}
	}
	for (int i = 1; i <= m; i++) tim[i].push_back(q + 1);
	for (int i = 1; i <= m; i++) {
		int la = 0;
		for (int j : tim[i]) {
			if (la + 1 <= j - 1) update(1, 1, q, la + 1, j - 1, i);
			la = j;
		}
	}
	for (int i = 1; i <= n; i++) col[i] = i;
	adjust(1, 1, q), cdq(1, 1, q);
	for (int i = 1; i <= q; i++) cout << (query(i) ? "Connected" : "Disconnected") << "\n";
	return 0;
}
