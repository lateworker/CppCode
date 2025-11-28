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
const intl N = 500000, Mod = 998244353;
intl n, a[N + 10], pw2[N + 10];
#define pow7(x) ((x)%Mod*(x)%Mod*(x)%Mod*(x)%Mod*(x)%Mod*(x)%Mod*(x)%Mod)
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl ans = 0;
	for (int i = 2; i <= n; i++) {
		intl x = abs(a[i] - a[1]);
		ans += pow7(x) * pw2[n - i] % Mod, ans %= Mod;
	}
	cout << ans << '\n';
}
int main() { ffopen();
	pw2[0] = 1;
	for (int i = 1; i <= N; i++) pw2[i] = (pw2[i - 1] << 1) % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
