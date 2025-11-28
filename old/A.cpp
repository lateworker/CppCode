#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 100000;
intl n, x, y, a[N + 10];
void slove() {
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) cin >> a[i];
	if (n == 1) {
		cout << "0\n";
		return;
	}
	sort(a + 1, a + 1 + n);
	sort(a + 2, a + n, [](int x, int y) { return abs(x) > abs(y); } );
//	for (int i = 1; i <= n; i++) cerr << a[i] << " \n"[i == n];
	intl ans = a[n] - a[1];
	for (int i = 1; i <= x + y && i <= n - 2; i++) {
		ans += abs(a[i + 1]);
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
