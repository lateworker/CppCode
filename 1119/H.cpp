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
const int N = 300000, Mod = 1000000007;
int n, a[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x; ++a[x];
	}
	intl cnt = 0, ans = 1;
	for (int i = n; i >= 1; i--) {
		if (a[i] > 2) { cout << "0\n"; return; }
		if (a[i] == 2) (ans <<= 1) %= Mod, ++cnt;
		if (a[i] == 0) {
			if (!cnt) { cout << "0\n"; return; }
			ans = ans * cnt % Mod * cnt % Mod, --cnt;
		}
		if (a[i] == 1) {
			ans = ans * (cnt << 1 | 1) % Mod;
		}
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) a[i] = 0;
	}
	return 0;
}
