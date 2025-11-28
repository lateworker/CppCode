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
const intl N = 5000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m, f[N + 10], g[N + 10];
bitset<N + 10> s;
vector<int> vec[2];
void slove() {
	cin >> n >> m;
	vec[0].clear(), vec[1].clear();
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		s[i] = c == '1';
		vec[s[i]].push_back(i);
	}
	int s0 = vec[0].size(), s1 = vec[1].size();
	if (s0 <= m || s1 <= m) { cout << "0\n"; return; }
	int cnt[2] = {0, 0}, l = 1, r = 0;
	intl ans = inf, cur = 0;
	for (int i = 0, j = s0 - m - 1; i < s1 && j < s0; ++i, ++j) {
		int lf = vec[1][i], rt = vec[0][j];
		while (r < rt) {
			if (!s[++r]) cur += cnt[1];
			++cnt[s[r]];
		}
		while (l < lf) {
			--cnt[s[l]];
			if (s[l++]) cur -= cnt[0];
		}
		chkmin(ans, cur);
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
