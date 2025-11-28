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
int n, m, vec[N + 10], pos[N + 10], pv;
string s, t;
void slove() {
	cin >> n >> m >> s >> t;
	s = '#' + s + '#', t = '#' + t + '#';
	if (s == t) {
		cout << "0\n";
		return;
	}
	int ma = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		if (t[i] != t[i + 1]) {
			++pv, vec[pv] = i - j + 1, pos[pv] = i, j = i + 1;
			chkmax(ma, vec[pv]);
		}
	}
//	for (int i = 1; i <= pv; i++) {
//		cerr << vec[i] << ' ' << pos[i] << '\n';
//	}
	if (ma < m) {
		cout << "-1\n";
		return;
	}
	int p = 0;
	for (int i = 1; i <= pv; i++) {
		if (vec[i] == ma) { p = i; break; }
	}
	vector<pair<int, char> > ans;
	for (int i = 1; i < p; i++) {
		for (int j = pos[i] - vec[i] + 1; j <= pos[i] && j + m - 1 <= n; j++) {
			ans.emplace_back(j, t[j]);
		}
	}
	for (int i = pv; i > p; i--) {
		for (int j = max(pos[i] - vec[i] + 1, m); j <= pos[i]; j++) {
			ans.emplace_back(j - m + 1, t[j]);
		}
	}
	for (int j = pos[p] - vec[p] + 1; j + m - 1 <= pos[p]; j++) {
		ans.emplace_back(j, t[j]);
	}
	cout << ans.size() << '\n';
	for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		pv = 0;
	}
	return 0;
}
