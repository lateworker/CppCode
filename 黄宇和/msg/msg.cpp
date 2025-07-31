#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
template<class T_> void chkmin(T_& x, const T_& y) { x = min(x, y); }
template<class T_> void chkmax(T_& x, const T_& y) { x = max(x, y); }
using ldouble = long double;
const int N = 100;
int n, m, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
bool g[N + 10][N + 10];
ldouble tar, dj[N + 10][N + 10];
struct loc {
	int x, y;
	bool operator== (const loc& b) const { return x == b.x && y == b.y; }
	bool operator< (const loc& b) const { return make_pair(x, y) < make_pair(b.x, b.y); }
} s, t;
bool dijkstra(ldouble k) {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dj[i][j] = numeric_limits<ldouble>::max();
	priority_queue<pair<ldouble, loc>, vector<pair<ldouble, loc>>, greater<pair<ldouble, loc>>> que;
	que.emplace(dj[s.x][s.y] = 0, s);
	while (!que.empty()) {
		auto [dis, u] = que.top(); que.pop();
		if (dis > dj[u.x][u.y]) continue;
		for (int c : {0, 1, 2, 3}) {
			loc v = {u.x + dx[c], u.y + dy[c]};
			if (!g[v.x][v.y]) continue;
			ldouble w = k * abs(dy[c]) + abs(dx[c]);
			if (dj[v.x][v.y] > dj[u.x][u.y] + w) {
				que.emplace(dj[v.x][v.y] = dj[u.x][u.y] + w, v);
			}
		}
	}
	return dj[t.x][t.y] < tar;
}
int main() { ffopen(msg);
	cin >> n >> m;
	cin >> s.x >> s.y >> t.x >> t.y;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int x; cin >> x;
			g[i][j] = (x == 0);
		}
	}
	cin >> tar;
	ldouble l = 0, r = 1e8;
	while (1e-5 < r - l) {
		ldouble mid = (l + r) / 2;
		if (dijkstra(mid)) l = mid;
		else r = mid;
	}
	cout << fixed << setprecision(3) << l << "\n";
	return 0;
}
