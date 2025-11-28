#define MultiCase (cin >> CaseId)
#define Main(Callback) main() { int CaseId = 1; { Callback } CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else return 0
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
const int N = 100000;
int n, m, f[N + 10][2];
vector<int> g[N + 10];
int chk(bool c) {
	int ma = 0;
	for (int i = 1; i <= n; i++) {
		chkmax(ma, f[i][c]);
	}
	return ma;
}
int Main(ffopen(); MultiCase; ) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) g[i].clear();
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	memset(f, 0x3f, sizeof f);
	queue<pair<int, bool> > que;
	f[1][0] = 0, que.emplace(1, 0);
	while (!que.empty()) {
		int u; bool c;
		tie(u, c) = que.front(); que.pop();
		for (int v : g[u]) {
			if (f[u][c] + 1 < f[v][!c]) {
				f[v][!c] = f[u][c] + 1;
				que.emplace(v, !c);
			}
		}
	}
	int ans = min(chk(0), chk(1));
	cout << (ans > n ? -1 : ans) << '\n';
} Return; }

