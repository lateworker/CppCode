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
int n, a[N + 10], b[A + 10], cnt[A + 10];
intl ncr[N + 10][N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], ++b[a[i]];
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (a[i] == a[j]) continue;
			ans += cnt[a[i] ^ a[j]] * b[a[i]] * b[a[j]];
			cnt[a[i] ^ a[j]] += b[a[i]] * b[a[j]];
		}
	}
	for (int i = 1; i <= n; i++) {
		if (b[a[i]] == 1) continue;
		for (int j = 1; j < i; j++) {
			ans += ncr[b[a[i]]][2] * ncr[b[a[j]]][2];
		}
	}
	cout << ans * 010 << '\n';
}
int main() { ffopen();
	ncr[0][0] = 1;
	for (int i = 1; i <= N; i++) {
		ncr[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			ncr[i][j] = ncr[i - 1][j] + ncr[i - 1][j - 1];
		}
	}
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) {
			b[a[i]] = 0;
			for (int j = 1; j < i; j++) {
				cnt[a[i] ^ a[j]] = 0;
			}
		}
	}
	return 0;
}
