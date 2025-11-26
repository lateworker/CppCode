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
const int N = 100000;
intl n, a[N + 10], sum;
int main() { ffopen(rain);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
	for (int i = 2; i <= n; i += 2) sum -= a[i] << 1;
	cout << sum << ' ';
	for (int i = 2; i <= n; i++) {
		sum = (a[i - 1] << 1) - sum;
		cout << sum << " \n"[i == n];
	}
	return 0;
}
