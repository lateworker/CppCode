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
const intl N = 200000;
intl n, x, k, a[N + 10];
intl calc1() {
	intl x = ::x * ::k;
	int p = 0;
	for (int i = n; i >= 1; i--) {
		if (a[i] < x) { p = i; break; }
	}
	int res = 0;
	for (int i = 1; i <= p; i++) {
		if (a[i] != a[i - 1]) ++res;
	} return res;
}
intl calc2() {
	static intl vf[N + 10];
	static int vs[N + 10], f[N + 10];
	int pv = 0;
	for (int i = 1; i <= n; i++) {
		if (!pv || vf[pv] != a[i]) ++pv, vf[pv] = a[i], vs[pv] = 0;
		++vs[pv];
	}
	intl ma = 0, cnt = 0;
	for (int i = 1; i <= pv; i++) f[i] = f[i - 1] + (vs[i] > 1 || vf[i] >= x);
	for (int i = 1; i <= pv; i++) {
		if (vf[i] >= x) break;
		int j = lower_bound(vf + 1, vf + pv + 1, vf[i] * k) - vf - 1;
		if (i <= j) chkmax(ma, (intl) f[j] - f[i - 1]);
		++cnt;
	} return ma + cnt;
}
void slove() {
	cin >> n >> x >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n), a[0] = -1;
	cout << max(calc1(), calc2()) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
