#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define int long long
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const int N = 60;
int n, m, s[N + 10], f[N + 10][6][6];
char tbl[] = {'0', '1', '2', '*'};
bool lgl(int c1, int c2, int c3) {
	if (c1 == 0) return (c2 == 0 && c3 == 0) || (c2 == 0 && c3 == 1) || (c2 == 1 && c3 == 3);	
	if (c1 == 1) return (c2 == 0 && c3 == 0) || (c2 == 0 && c3 == 1) || (c2 == 1 && c3 == 3) || (c2 == 3 && c3 == 1) || (c2 == 3 && c3 == 2) || (c2 == 3 && c3 == 3);
	if (c1 == 2) return (c2 == 3 && c3 == 1) || (c2 == 3 && c3 == 2) || (c2 == 3 && c3 == 3);	
	if (c1 == 3) return (c2 == 1 && c3 == 0) || (c2 == 1 && c3 == 1) || (c2 == 2 && c3 == 3) || (c2 == 3 && c3 == 1) || (c2 == 3 && c3 == 2) || (c2 == 3 && c3 == 3);
	return false;
}
void slove() {
	cin >> n >> m; ++m;
	if (m > (1LL << n)) { cout << "-1\n"; return; }
	if (n == 1) {
		if (m == 1) cout << "*\n";
		if (m == 2) cout << "0\n";
		return;
	}
	if (n == 2) {
		if (m == 1) cout << "**\n";
		if (m == 2) cout << "*1\n";
		if (m == 3) cout << "00\n";
		if (m == 4) cout << "1*\n";
		return;
	}
	for (int c : {3, 0, 1}) {
		int now = 0;
		for (int c2 : {3, 0, 1, 2}) now += f[n][c][c2];
		s[n] = c;
		if (now >= m) break;
		else m -= now;
	}
	for (int c1 : (s[n] == 3 ? vector<int>{3, 1, 2} : s[n] == 0 ? vector<int>{0, 1} : s[n] == 1 ? vector<int>{3} : vector<int>{})) {
		int now = 0;
		for (int c2 : {3, 0, 1, 2}) if (lgl(s[n], c1, c2)) now += f[n - 1][c1][c2];
		s[n - 1] = c1;
		if (now >= m) break;
		else m -= now;
	}
	for (int i = n - 2; i >= 1; i--) {
		for (int c1 : {3, 0, 1, 2}) {
			if (!lgl(s[i + 2], s[i + 1], c1)) continue;
			int now = 0;
			for (int c2 : {3, 0, 1, 2}) if (lgl(s[i + 1], c1, c2)) now += f[i][c1][c2];
			s[i] = c1;
			if (now >= m) break;
			else m -= now;
		}
	}
	for (int c : {3, 0, 1, 2}) {
		if (!lgl(s[3], s[2], c)) continue;
		s[1] = c;
		if ((m--) == 1) break;
	}
	if (m) cout << "-1\n";
	else {
		for (int i = n; i >= 1; i--) cout << tbl[s[i]];
		cout << '\n';
	}
}
signed main() { ffopen();
	f[2][0][0] = f[2][1][0] = f[2][3][1] = f[2][1][3] = f[2][2][3] = f[2][3][3] = 1;
	for (int i = 3; i <= N; i++) {
		for (int c1 : {0, 1, 2, 3}) for (int c2 : {0, 1, 2, 3}) for (int c3 : {0, 1, 2, 3}) {
			if (lgl(c1, c2, c3)) f[i][c1][c2] += f[i - 1][c2][c3];
		}
	}
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
