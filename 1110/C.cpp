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
const int N = 2000;
int n, dis[N + 10], ans[N + 10], stk[N + 10], cnt1, cnt2;
vector<int> g[N + 10];
void dfs(int u, int p) {
	dis[u] = dis[p] + 1;
	for (int v : g[u]) if (v != p) dfs(v, u);
}
void fil(int u, int p, int d, const int& y) {
	stk[d] = u;
	if (u == y) {
		for (int i = 1; i <= d >> 1; i++) ans[stk[i]] = 1, ++cnt1;
		for (int i = d; i > d >> 1; i--) ans[stk[i]] = 2, ++cnt2;
		return;
	}
	for (int v : g[u]) if (v != p) {
		fil(v, u, d + 1, y);
	}
}
void slove() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	int x = 0, y = 0;
	for (int i = 1; i <= n; i++) {
		if (dis[i] > dis[x]) x = i;
	}
	dfs(x, 0);
	for (int i = 1; i <= n; i++) {
		if (dis[i] > dis[y]) y = i;
		ans[i] = 0;
	}
	fil(x, 0, 1, y);
	for (int i = 1; i <= n; i++) {
		if (cnt1 == n >> 1) {
			for (; i <= n; i++) {
				if (!ans[i]) ans[i] = 2;
			} break;
		}
		if (!ans[i]) ans[i] = 1, ++cnt1;
	}
	for (int i = 1; i <= n; i++) cout << (ans[i] & 1 ? "R" : "B");
	cout << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) g[i].clear();
		cnt1 = cnt2 = 0;
	}
	return 0;
}
