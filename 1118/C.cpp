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
int n, a[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n), a[n + 1] = -1;
	vector<pii> vec;
	int las = 1;
	for (int i = 1; i <= n; i++) {
		if (a[i] + 1 != a[i + 1]) {
			vec.emplace_back(las, i), las = i + 1;
		}
	}
	intl ans = 0;
	for (auto [l, r] : vec) {
		intl m = r - l + 1;
		if (m < 3) continue;
		ans += (m + 3) * (m - 2) / 2 * (m + 3) - (m - 2) * (m + 1) * 2 - m * (m + 1) * (m << 1 | 1) / 6 + 5;
	}
	for (int i = 1; i < (int)vec.size(); i++) {
		if (a[vec[i].first] - 2 != a[vec[i - 1].second]) continue;
		ans += (intl) (vec[i].second - vec[i].first + 1) * (vec[i - 1].second - vec[i - 1].first + 1);
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
