#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int long long
using namespace std;
using intl = long long;
const int N = 30;
intl n, f[N + 5][N + 5];
string s; char tb[] = "()[]{}<>";
bool isleft(char c) { return c == tb[0] || c == tb[2] || c == tb[4] || c == tb[6]; }
bool ismatch(char x, char y) { return (x == tb[0] && y == tb[1]) || (x == tb[2] && y == tb[3]) || (x == tb[4] && y == tb[5]) || (x == tb[6] && y == tb[7]); }
intl wval(int i, int j) {
	if (s[i] == '?' && s[j] == '?') return 4;
	if ((s[i] == '?' && !isleft(s[j])) || (isleft(s[i]) && s[j] == '?')) return 1;
	return ismatch(s[i], s[j]);
}
vector<int> now;
intl res;
void dfs(int i, int x, int y, const vector<int>& vec) {
	intl pi = 1, last = x;
	for (int p : now) pi *= f[last][vec[p]], last = vec[p] + 1;
	pi *= f[last][y];
	res += (now.size() & 1 ? 1 : -1) * pi;
	for (int j = i + 1; j < (int) vec.size(); j++) {
		now.push_back(j);
		dfs(j, x, y, vec);
		now.pop_back();
	}
}
signed main() { //ffopen(bracket);
	cin >> s;
	n = s.size(), s = ' ' + s;
	if (n & 1) return cout << 0 << "\n", 0;
	for (int i = 2; i <= n; i++) f[i][i - 1] = 1;
	for (int k = 2; k <= n; k += 2) {
		for (int i = 1; i + k - 1 <= n; i++) {
			int j = i + k - 1;
			if (k > 2) {
				vector<int> vec; res = 0;
				for (int x = i + 1; x < j - 1; x += 2) vec.push_back(x);
				for (int c = 0; c < (int) vec.size(); c++) {
					now = {c};
					dfs(c, i, j, vec);
				}
				f[i][j] += res;
			}
			f[i][j] += f[i + 1][j - 1] * wval(i, j);
		}
	}
//	for (int i = 1; i <= n; i++)
//		for (int j = 1; j <= n; j++) {
//			cout << f[i][j] << " \n"[j == n];
//		}
	cout << f[1][n] << "\n";
	return 0;
}
