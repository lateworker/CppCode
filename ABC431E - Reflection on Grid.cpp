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
const int Len = 200000, inf = 0x3f3f3f3f;
int n, m;
struct Graph {
	int g[Len + 10];
	auto operator[] (const int& i) const { return g + (i - 1) * m; }
	auto operator[] (const int& i) { return g + (i - 1) * m; }
	auto operator[] (const pii& u) const { return (*this)[u.first][u.second]; }
	auto& operator[] (const pii& u) { return (*this)[u.first][u.second]; }
	void clear(int x = 0) { for (int i = 0; i <= n * m + 3; i++) g[i] = x; }
};
pii operator+ (const pii& u, const pii& v) { return make_pair(u.first + v.first, u.second + v.second); }
Graph g, dis[4];
pii drr[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int apply(int dn, int op) {
	if (op == 0) return dn;
	if (op > 0) {
		if (dn == 0) return 3;
		if (dn == 3) return 0;
		if (dn == 1) return 2;
		if (dn == 2) return 1;
	}
	if (op < 0) {
		if (dn == 0) return 1;
		if (dn == 1) return 0;
		if (dn == 2) return 3;
		if (dn == 3) return 2;
	}
	return -1;
}
int bfs(pair<int, pii> s, pair<int, pii> t) {
	for (int d : {0, 1, 2, 3}) dis[d].clear(inf);
	deque<pair<int, pii> > que;
	dis[s.first][s.second] = 0, que.push_front(s);
	while (!que.empty()) {
		auto [dn, u] = que.front(); que.pop_front();
		for (int d : {0, 1, 2, 3}) {
			if (d != dn && (d & 1) == (dn & 1)) continue;
			pii v = u + drr[d];
			int w = (apply(dn, g[u]) != d);
			if ((v.first < 1 || v.first > n || v.second < 1 || v.second > m) && make_pair(d, v) != t) continue;
			if (dis[dn][u] + w < dis[d][v]) {
				dis[d][v] = dis[dn][u] + w;
				w ? que.emplace_back(d, v) : que.emplace_front(d, v);
			}
		}
	}
	return dis[t.first][t.second];
}
void slove() {
	cin >> n >> m;
	g.clear();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c; cin >> c;
			if (c == 'A') g[i][j] = 0;
			if (c == 'B') g[i][j] = 1;
			if (c == 'C') g[i][j] = -1;
		}
	}
	cout << bfs({0, make_pair(1, 1)}, {0, make_pair(n, m + 1)}) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
