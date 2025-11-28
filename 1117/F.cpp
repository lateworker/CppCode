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
const intl N = 300000;
intl n, m, k, a[N + 10], pi[N + 10];
intl dnc(int l, int r) {
	if (l == r) return a[l];
	int mid = (l + r) >> 1;
	intl res = (dnc(l, mid) + dnc(mid + 1, r)) % m;
	pi[mid + 1] = 1;
	for (int i = mid; i >= l; i--) pi[i] = pi[i + 1] * a[i] % m;
	intl pir = 1, sum = 0;
	for (int i = l, j = mid + 1; i <= mid; i++) {
		while (j <= r && j - i + 1 <= k) pir = pir * a[j++] % m, sum += pir, sum %= m;
		if (j - i <= k) res += pi[i] * sum % m, res %= m;
	} return res % m;
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		cin >> n >> k >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		cout << dnc(1, n) << '\n';
	}
	return 0;
}
