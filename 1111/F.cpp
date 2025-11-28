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
const int N = 200000, M = N << 1;
int n, m, lx[N + 10], rx[N + 10], a[M + 10];
void add(int l, int r) {
//	cerr << l << ' ' << r << " Crs\n";
	if (r < l) { add(l, m - 1), add(0, r); return; }
	++a[l], --a[r + 1];
}
void slove() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++) cin >> lx[i], --lx[i];
	for (int i = 1; i <= n; i++) cin >> rx[i], --rx[i];
	if (m & 1) {
		m <<= 1;
		for (int i = 1; i <= n; i++) {
			lx[i] <<= 1, rx[i] <<= 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (rx[i] < lx[i]) rx[i] += m;
		int hf = lx[i] + (m >> 1);
		add(lx[i], (min(rx[i], hf) + m - 1) % m);
	}
	for (int i = 1; i <= m; i++) a[i] += a[i - 1];
	int ans = 0;
	for (int i = 0; i < m >> 1; i++) {
		chkmax(ans, a[i] + a[i + (m >> 1)]);
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
//		memset(a, 0, (m + 3) * sizeof(a[0]));
		memset(a, 0, sizeof a);
	}
	return 0;
}
