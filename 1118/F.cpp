#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const int N = 200000;
int n, fa[N + 10], cnt[N + 10];
pii seg[N + 10];
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
void merge(int u, int v) { u = find(u), v = find(v), fa[u] = v; }
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) fa[i] = i, cnt[i] = 0;
	for (int i = 1; i <= n; i++) cin >> seg[i].first >> seg[i].second;
	static int idx[N + 10];
	iota(idx + 1, idx + 1 + n, 1);
	sort(idx + 1, idx + 1 + n, [&](int i, int j) {
		return seg[i].second == seg[j].second ? seg[i].first < seg[j].first : seg[i].second < seg[j].second;
	} );
	vector<int> stk;
	for (int ii = 1; ii <= n; ii++) {
		int i = idx[ii];
		auto [li, ri] = seg[i];
		while (!stk.empty() && seg[stk.back()].second > li) {
			int j = stk.back(); stk.pop_back();
			merge(i, j), chkmin(li, seg[j].first);
		}
		stk.push_back(i);
	}
	for (int i = 1; i <= n; i++) ++cnt[find(i)];
	for (int i = 1; i <= n; i++) cout << cnt[find(i)] << " \n"[i == n];
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
