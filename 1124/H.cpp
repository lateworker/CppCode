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
const intl N = 300000, M = N;
intl n, m, a[N + M + 10], b[N + M + 10], pa[N + M + 10], pb[N + M + 10], f[N + M + 10], g[N + M + 10];
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int c; cin >> c;
			if (c == 0 || c == 3) continue;
			a[i + j] += c == 1 ? -1 : 1;
			b[i - j + m + 1] += c == 1 ? -1 : 1;
		}
	}
	for (int i = 2; i <= n + m; i++) {
		pa[i] = pa[i - 1] + a[i] * i;
		a[i] += a[i - 1];
		pb[i] = pb[i - 1] + b[i] * i;
		b[i] += b[i - 1];
	}
	for (int i = 2; i <= n + m; i++) {
		f[i] = (a[i - 1] - a[n + m] + a[i]) * i - (pa[i - 1] - pa[n + m] + pa[i]);
		g[i] = (b[i - 1] - b[n + m] + b[i]) * i - (pb[i - 1] - pb[n + m] + pb[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			intl dis = f[i + j] + g[i - j + m + 1];
			cout << (abs(dis) >> 1) << " \n"[j == m];
		}
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 2; i <= n + m; i++) {
			a[i] = b[i] = pa[i] = pb[i] = f[i] = g[i] = 0;
		}
	}
	return 0;
}
