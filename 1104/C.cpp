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
const intl N = 100000, M = 1000;
intl n, m, z, a[N + 10], f[M + 10], ff[M + 10];
void slove() {
	cin >> n >> m >> z;
	for (int i = 1; i <= n; i++) cin >> a[i];
	memset(f, 0x3f, (m + 3) * sizeof(intl)), f[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) ff[j] = f[j];
		for (int j = 0; j < m; j++) {
			int j0 = (j + a[i]) % m;
			chkmin(f[j0], ff[j] + a[i]);
		}
	}
	cout << (f[(m - z % m) % m] > intl(1e18) ? -1 : (f[(m - z % m) % m] + z) / m) << '\n';
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
