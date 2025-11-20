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
const int N = 1 << 18;
int n, a[N + 10], f[61][N + 10];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		f[a[i]][i] = i;
	}
	int ans = 0;
	for (int x = 2; x <= 58; x++) {
		for (int i = 1; i <= n; i++) {
			int u = f[x - 1][i];
			if (u) f[x][i] = f[x - 1][u + 1];
			if (f[x][i]) chkmax(ans, x);
		}
	}
	cout << ans << '\n';
	return 0;
}
