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
const int Len = 300000, inf = 0x3f3f3f3f;
int n, m, dis[Len + 10];
bitset<Len + 10> g;
inline int gid(int i, int j) { return (i - 1) * m + j; }
inline int gid(pii u) { return gid(u.first, u.second); }
pii drr[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
pii operator+ (const pii& x, const pii& y) { return make_pair(x.first + y.first, x.second + y.second); }
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c; cin >> c;
			g[gid(i, j)] = c == '1';
		}
	}
	for (int i = 1; i <= n * m; i++) dis[i] = inf;
	deque<pii> que;
	for (int i = 1; i <= n; i++) {
		int u = gid(i, 1); dis[u] = 0;
		g[u] ? que.emplace_back(i, 1) : que.emplace_front(i, 1);
	}
	for (int i = 1; i <= n; i++) {
		int u = gid(i, m); dis[u] = 0;
		g[u] ? que.emplace_back(i, m) : que.emplace_front(i, m);
	}
	for (int j = 2; j < m; j++) {
		int u = gid(1, j); dis[u] = 0;
		g[u] ? que.emplace_back(1, j) : que.emplace_front(1, j);
	}
	for (int j = 2; j < m; j++) {
		int u = gid(n, j); dis[u] = 0;
		g[u] ? que.emplace_back(n, j) : que.emplace_front(n, j);
	}
	while (!que.empty()) {
		pii u = que.front(); que.pop_front();
		for (int c : {0, 1, 2, 3}) {
			pii v = u + drr[c];
			if (v.first < 1 || v.first > n || v.second < 1 || v.second > m) continue;
			if (dis[gid(u)] + g[gid(u)] < dis[gid(v)]) {
				dis[gid(v)] = dis[gid(u)] + g[gid(u)];
				g[gid(v)] ? que.emplace_back(v) : que.emplace_front(v);
			}
		}
	}
	int ma = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (g[gid(i, j)]) continue;
			chkmax(ma, dis[gid(i, j)]);
		}
	}
	cout << ma << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
