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
const int N = 200000;
intl n, x, a[N + 10], s, t, ans[N + 10];
bool check(intl y) {
	s = a[1] - y, t = a[1] + y;
	for (int i = 2; i <= n; i++) {
		t += x;
		chkmax(s, a[i] - y);
		chkmin(t, a[i] + y);
		if (t < s) return false;
	} return true;
}
void slove() {
	cin >> n >> x;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl l = 0, r = 2000000000;
	while (l < r) {
		intl mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << '\n';
	check(l);
	ans[n] = s;
	for (int i = n - 1; i >= 1; i--) {
		ans[i] = max(a[i] - l, ans[i + 1] - x);
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
