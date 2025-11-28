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
int n, b[N + 10], pb;
bitset<N + 10> a;
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		a[i] = x;
		if (i >= 2 && a[i] && a[i - 1]) b[++pb] = i;
		if (i >= 3 && a[i] && !a[i - 1] && a[i - 2]) b[++pb] = i;
	}
	sort(b + 1, b + pb + 1);
	pb = unique(b + 1, b + pb + 1) - b - 1;
	intl ans = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		while (j <= pb && b[j] <= i) ++j;
		int p = b[j - 1];
		ans += a[i];
		if (p) ans += (a[p - 1] ? p - 1 : p - 2);
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		pb = 0;
	}
	return 0;
}
