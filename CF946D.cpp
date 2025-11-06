#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
const int N = 500, inf = 0x3f3f3f3f;
int n, m, k, f[N + 10][N + 10], w[N + 10][N + 10];
bool g[N + 10][N + 10];
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char x; cin >> x;
			g[i][j] = (x == '1');
		}
	memset(f, 0x3f, sizeof f);
	memset(w, 0x3f, sizeof w);
	static int vec[N + 10];
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = 1; j <= m; j++)
			if (g[i][j]) vec[++cnt] = j;
		for (int x = 0; x < cnt; x++) {
			int y = cnt - x;
			for (int j = 1; j + y - 1 <= cnt; j++)
				chkmin(w[i][x], vec[j + y - 1] - vec[j] + 1);
		}
		for (int x = cnt; x <= k; x++) w[i][x] = 0;
//		for (int x = 0; x <= k; x++) cerr << w[i][x] << " \n"[x == k];
	}
	f[0][k] = 0;
	for (int i = 1; i <= n; i++) {
		for (int x = 0; x <= k; x++) {
			for (int y = 0; y + x <= k; y++) {
				chkmin(f[i][x], f[i - 1][x + y] + w[i][y]);
			}
		}
	}
	int ans = inf;
	for (int i = 0; i <= k; i++) chkmin(ans, f[n][i]);
	cout << ans << "\n";
	return 0;
}
