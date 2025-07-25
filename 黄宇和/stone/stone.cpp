#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
const int N = 3000, inf = 0x3f3f3f3f;
using namespace std;
int n, a[N + 10], b[N + 10], f[N + 10][N + 10], t[N + 10];
int main() { ffopen(stone);
	cin >> n;
	for (int i = 0; i <= n + 1; i++) cin >> a[i];
	for (int i = 0; i <= n + 1; i++) cin >> b[i];
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n + 1; i++) {
		int s = 0;
		for (int j = 1; j <= n + 1; j++) {
			if (a[i] != b[j]) continue;
			int res = inf, ns = s, nt = t[j];
			for (int x = nt; x < i; x++)
				for (int y = ns; y < j; y++) {
					if (a[x] != b[y]) continue;
					int now = f[x][y] + (i - x) * (i - x) + (j - y) * (j - y);
					if (now < res) res = now, s = y, t[j] = x;
				}
			f[i][j] = res;
		}
	}
	cout << f[n + 1][n + 1] << "\n";
	return 0;
}
