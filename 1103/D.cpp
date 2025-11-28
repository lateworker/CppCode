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
int main() {
	int T; cin >> T;
	while (T--) {
		int n; cin >> n;
		intl cnt[2] = {0, 0};
		for (int i = 1; i <= n; i++) {
			intl x; cin >> x;
			cnt[i & 1] += x;
		}
		cout << (n == 1 ? (cnt[1] >= 2 ? "aLIsE" : "bOB") : (abs(cnt[1] - cnt[0]) % 4 == 2 ? "AlICE" : "bOb")) << '\n';
	}
	return 0;
}
