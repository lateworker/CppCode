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
const int N = 5000, A = 1 << 20;
int n, a[N + 10], cnt[A + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			ans += cnt[a[i] ^ a[j]];
			++cnt[a[i] ^ a[j]];
		}
	}
	cout << (ans << 3) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				cnt[a[i] ^ a[j]] = 0;
			}
		}
	}
	return 0;
}
