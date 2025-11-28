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
const int N = 400000;
intl n, a[N + 10];
bool check() {
	for (int i = 1; i < n - 1; i++) {
		if (a[i] + a[n - i] != a[n]) return false;
	} return true;
}
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	int cnt = 0;
	for (int i = 1; i < n - 1; i++) {
		int x = a[n] - a[n - i] - a[i];
		a[i] += x, a[i + 1] -= x;
		cnt += bool(x);
	}
	cout << (check() ? cnt : -1) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
