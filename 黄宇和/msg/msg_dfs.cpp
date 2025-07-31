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
bool g[N + 10][N + 10], vis[N + 10][N + 10];
ldouble dis, ans = numeric_limits<long double>::max();
struct loc {
	int x, y;
	bool operator== (const loc& b) const { return x == b.x && y == b.y; }
} s, t;
int cut[N + 10];
void dfs(loc u, loc delt) {
	if (delt.y < cut[delt.x]) return;
	chkmax(cut[delt.x], delt.y);
	vis[u.x][u.y] = true;
	if (u == t) {
		cout << delt.x << " " << delt.y << "\n";
		chkmin(ans, (dis - delt.x) / delt.y);
		return;
	}
	for (int c : {0, 1, 2, 3}) {
		loc v = {u.x + dx[c], u.y + dy[c]};
		if (!g[v.x][v.y] || vis[v.x][v.y]) continue;
		dfs(v, {delt.x + abs(dx[c]), delt.y + abs(dy[c])});
	}
	vis[u.x][u.y] = false;
}
int main() { ffopen(msg2);
	cin >> n >> m;
	cin >> s.x >> s.y >> t.x >> t.y;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int x; cin >> x;
			g[i][j] = (x == 0);
		}
	}
	cin >> dis;
	dfs(s, {0, 0});
	cout << fixed << setprecision(3) << ans << "\n";
	return 0;
}
