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
const intl N = 400000, Mod = 998244353;
intl fac[N + 10], pw2[N + 10];
int n, a[N + 10], b[N + 10], pb;
bitset<N + 10> tag;
void slove() {
	cin >> n;
	for (int i = 1; i <= n << 1; i++) cin >> a[i];
	for (int i = 1; i <= n << 1; i += 2) {
		if (a[i] && a[i + 1]) tag[a[i]] = tag[a[i + 1]] = true;
	}
	for (int i = 1; i <= n << 1; i++) if (!tag[i]) b[++pb] = i;
	int cnt[3] = {0, 0, 0};
	for (int i = 1; i <= n << 1; i += 2) {
		if (a[i] && a[i + 1]) continue;
		int now = max(a[i], a[i + 1]);
		if (now) ++cnt[now <= b[pb >> 1]];
		else ++cnt[0], ++cnt[1], ++cnt[2];
	}
	cout << fac[cnt[0]] * fac[cnt[1]] % Mod * pw2[cnt[2]] % Mod << '\n';
}
int main() { ffopen();
	fac[0] = 1, pw2[0] = 1;
	for (int i = 1; i <= N; i++) {
		fac[i] = fac[i - 1] * i % Mod;
		pw2[i] = (pw2[i - 1] << 1) % Mod;
	}
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n << 1; i++) tag[i] = false;
		pb = 0;
	}
	return 0;
}
