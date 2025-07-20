#include <bits/stdc++.h>
using namespace std;
const int N = 100000, L = __lg(N) + 1, M = 5, inf = 0x3f3f3f3f;
int n, ln, m, q, a[M + 2][N + 10], rk[M + 2][N + 10];
int f[N + 10][L + 3][M + 3], g[N + 10][M + 3][M + 3];
int main() {
	cin >> n >> m;
	ln = __lg(n) + 1;
	for (int k = 1; k <= m; k++) {
		for (int i = 1; i <= n; i++)
			cin >> a[k][i], rk[k][a[k][i]] = i;
	}
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	for (int i = n; i >= 1; i--) {
		for (int x = 1; x <= m; x++)
			for (int y = 1; y <= m; y++)
				g[i][x][y] = min(g[i + 1][x][y], rk[x][a[y][i]]);
	}
	for (int i = 1; i <= n; i++) {
		for (int x = 1; x <= m; x++) {
			f[i][0][x] = n + 1;
			for (int y = 1; y <= m; y++)
				f[i][0][x] = min(f[i][0][x], g[rk[y][i] + 1][x][y]);
		}
	}
	for (int j = 1; j <= ln; j++) {
		for (int i = 1; i <= n; i++)
			for (int x = 1; x <= m; x++) {
				f[i][j][x] = n + 1;
				for (int y = 1; y <= m; y++)
					f[i][j][x] = min(f[i][j][x], f[a[y][f[i][j - 1][y]]][j - 1][x]);
			}
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int u, v;
		cin >> u >> v;
		auto check = [&]() {
			for (int x = 1; x <= m; x++)
				if (rk[x][u] < rk[x][v]) return true;
			return false;
		};
		if (check()) { cout << 1 << "\n"; continue; }
		int ans = 0, p[M + 3];
		for (int x = 1; x <= m; x++) p[x] = rk[x][u];
		for (int j = ln; j >= 0; j--) {
			int np[M + 3];
			for (int x = 1; x <= m; x++) {
				np[x] = n + 1;
				for (int y = 1; y <= m; y++)
					np[x] = min(np[x], f[a[y][p[y]]][j][x]);
			}
			auto check = [&]() {
				for (int x = 1; x <= m; x++)
					if (np[x] <= rk[x][v]) return false;
				return true;
			};
			if (check()) {
				for (int x = 1; x <= m; x++) p[x] = np[x];
				ans += (1 << j);
			}
		}
		cout << (ans > n ? -1 : ans + 2) << "\n";
	}
	return 0;
}
