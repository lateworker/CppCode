#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 100000000;
int a, b, now[15];
bitset<N + 3> isnp;
vector<int> pms, pdr;
void dfs(int i, int t) {
	if (i > (t + 1) >> 1) {
		int res = 0;
		for (int i = 1; i <= t; i++) (res *= 10) += now[i];
		pdr.push_back(res);
		return;
	}
	for (int x = (i == 1); x <= 9; x++) {
		now[i] = now[t - i + 1] = x;
		dfs(i + 1, t);
	}
}
int main() { ffopen();
	cin >> a >> b;
	isnp[0] = isnp[1] = true;
	for (int i = 2; i <= b; i++) {
		if (!isnp[i]) pms.push_back(i);
		for (int j : pms) {
			if ((intl) i * j > b) continue;
			isnp[i * j] = true;
			if (i % j == 0) break;
		}
	}
	for (int i = 1; i <= 8; i++) dfs(1, i);
	for (int x : pdr)
		if (a <= x && x <= b && !isnp[x]) cout << x << "\n";
	return 0;
}
