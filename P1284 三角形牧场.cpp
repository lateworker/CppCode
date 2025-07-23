#include <bits/stdc++.h>
using namespace std;
const int N = 40;
using doublel = long double;
int n, a[N + 10];
bool dp[N * N + 10][N * N + 10];
bool check(vector<int> b) { sort(b.begin(), b.end()); return b[0] + b[1] > b[2]; }
doublel S(doublel a, doublel b, doublel c) {
	doublel p = (a + b + c) / 2;
	return sqrtl(p * (p - a) * (p - b) * (p - c));
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	dp[0][0] = true;
	for (int i = 1; i <= n; i++) {
		for (int x = a[n]; x >= 0; x--)
			for (int y = a[n]; y >= 0; y--) {
				int z = a[i] - x - y;
				if (z < 0) continue;
				bool last = dp[x][y]; dp[x][y] = false;
				if (x - a[i] + a[i - 1] >= 0) dp[x][y] |= dp[x - a[i] + a[i - 1]][y];
				if (y - a[i] + a[i - 1] >= 0) dp[x][y] |= dp[x][y - a[i] + a[i - 1]];
				if (z - a[i] + a[i - 1] >= 0) dp[x][y] |= last;
			}
	}
	int ans = -1;
	for (int x = 0; x <= a[n]; x++)
		for (int y = 0; y <= a[n]; y++) {
			int z = a[n] - x - y;
			if (z < 0 || !dp[x][y] || !check({x, y, z})) continue;
			ans = max(ans, int(S(x, y, z) * 100));
		}
	cout << ans << "\n";
	return 0;
}
