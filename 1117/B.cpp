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
int n, a[N + 10], h[N + 10];
intl ph[N + 10], m;
bool check(intl ma) {
	for (int i = 1, j = 1; i <= n; i++) {
		while (a[i] - a[j] > (m << 1)) {
			if (ph[j] > a[j]) return false;
			++j;
		}
		if (ph[i] - ph[j - 1] >= ma) return true;
	} return false;
}
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl ma = 0;
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
		ph[i] = ph[i - 1] + h[i];
		chkmax(ma, ph[i] - a[i]);
	}
	cout << (check(ma) ? "yeS" : "nO") << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
