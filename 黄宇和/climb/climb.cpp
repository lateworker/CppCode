#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 1000000, inf = 0x3f3f3f3f;
int n, m, h[N + 10];
int slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> h[i];
	int ans = n - 1;
	if (n == 1) return ans;
	int kma = (m - 1) / (n - 1);
	if (m <= (intl) n * n) {
		for (int k = 0; k <= kma; k++) {
			int bma = m - k * n;
			for (int b = 1 - k; b <= bma; b++) {
				int cnt = 0;
				for (int p = 1; p <= n; p++) {
					if (h[p] == k * p + b) ++cnt;
				} ans = min(ans, n - cnt);
			}
		}
	} else {
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (h[j] < h[i] || (h[j] - h[i]) % (j - i) != 0) continue;
				int k = (h[j] - h[i]) / (j - i);
				if ((intl) k + h[j] - (intl) k * j < 1LL || (intl) k * n + h[j] - (intl) k * j > (intl) m) continue;
				int cnt = 0;
				for (int p = 1; p <= n; p++) {
					if ((intl) h[p] == (intl) k * p + h[j] - (intl) k * j) ++cnt;
				} ans = min(ans, n - cnt);
			}
		}
	} return ans;
}
int main() { ffopen(climb);
	int T; cin >> T;
	while (T--) {
		cout << slove() << "\n";
	}
	return 0;
}
