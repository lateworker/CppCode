#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000;
int n, m, q, cnt[N + 10], col[N + 10], tag[N + 10];
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
bool ans[N + 10];
vector<int> g[N + 10];
void dfs(int u, int c) {
	tag[u] = c;
	for (int v : g[u]) if (!tag[v]) dfs(v, c);
}
void cdq(int u, int l, int r, const vector<pair<int, int> >& cst) {
	vector<int> vec;
	
	for (int x : pnt[u]) col[x] = 0;
	for (int x : pnt[u]) if (!col[x]) col[x] = -1, vec.push_back(x);
	pnt[u].swap(vec), vec.clear();
	for (auto [x, y] : cst) if (!~col[x]) vec.push_back(col[x] = y);
	for (int c : vec) g[c].clear();
	
	for (int i : evt[u]) {
		auto [x, y] = e[i];
		if (col[x] == col[y]) continue;
		g[col[x]].push_back(col[y]);
		g[col[y]].push_back(col[x]);
	}
	for (int c : vec) tag[c] = 0;
	for (int c : vec) if (!tag[c]) dfs(c, c);
	
	vector<tuple<int, int, int> > cnr;
	for (int c : vec) if (cnt[c] && tag[c] != c)
		cnt[tag[c]] += cnt[c], cnr.emplace_back(c, tag[c], cnt[c]), cnt[c] = 0;
	
//	cout << u << " " << l << " " << r << " Seghere\n";
//	
//	puts("cnt1");
//	for (int c = 1; c <= n; c++) cout << c << " " << cnt[c] << "\n";
//	
//	puts("cnr");
//	for (auto [x, y, z] : cnr) cout << x << " " << y << " " << z << "\n";
//	
//	puts("x->tag");
//	vector<int> pp = pnt[u];
//	sort(pp.begin(), pp.end()); pp.erase(unique(pp.begin(), pp.end()), pp.end());
//	for (int x : pp) cout << x << " " << col[x] << " " << tag[col[x]] << "\n";
	
	auto check = [&]() {
		int c = tag[col[pnt[u].front()]];
		for (int x : pnt[u]) {
			if (c != tag[col[x]]) return false;
		} return cnt[c] == n;
	};
	
//	cout << u << " " << l << " " << r << "\n";
	if (l == r) {
		ans[l] = check();
	} else {
		vector<pair<int, int> > now;
		for (int x : pnt[u]) now.emplace_back(x, tag[col[x]]);
		
		int mid = (l + r) >> 1;
		cdq(u << 1, l, mid, now);
		cdq(u << 1 | 1, mid + 1, r, now);
	}
	
	for (auto [c, tc, y] : cnr) {
		cnt[c] += y, cnt[tc] -= y;
	}
}
//void print(int u, int l, int r) {
//	cout << u << " " << l << " " << r << "\n";
//	for (int x : pnt[u]) cout << x << " "; puts("pnt");
//	for (int i : evt[u]) cout << i << " "; puts("evt");
//	if (l == r) return;
//	int mid = (l + r) >> 1;
//	print(u << 1, l, mid);
//	print(u << 1 | 1, mid + 1, r);
//}
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
//	print(1, 1, q);
	vector<pair<int, int> > now;
	for (int i = 1; i <= n; i++) now.emplace_back(i, i), cnt[i] = 1;
	cdq(1, 1, q, now);
	for (int i = 1; i <= q; i++) cout << (ans[i] ? "Connected" : "Disconnected") << "\n";
	return 0;
}
