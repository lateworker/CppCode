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
const int N = 200000;
int n, m, dis[N + 10][2], frm[N + 10];
vector<int> g[N + 10];
bitset<N + 10> col;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	queue<pair<int, bool> > que;
	memset(dis, 0x3f, sizeof dis);
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		col[i] = c == 'D';
		if (!col[i]) {
			dis[i][0] = 0;
			frm[i] = i;
			que.emplace(i, 0);
		}
	}
	while (!que.empty()) {
		int u; bool c;
		tie(u, c) = que.front(); que.pop();
		for (int v : g[u]) {
			if (dis[u][c] + 1 < dis[v][c]) {
				dis[v][c] = dis[u][c] + 1;
				if (!c) frm[u] = frm[v];
				que.emplace(v, c);
			}
			if (c || frm[u] == frm[v]) continue;
			if (dis[u][0] + 1 < dis[v][1]) {
				dis[v][1] = dis[u][0] + 1;
				que.emplace(v, 1);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (col[i]) {
			cout << dis[i][0] + dis[i][1] << '\n';
		}
	}
	return 0;
}

