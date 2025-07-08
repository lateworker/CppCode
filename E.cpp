#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 200000;
intl n, c, a[N + 10];
bool check(intl w) {
	intl s = 0;
	for (int i = 1; i <= n; i++) {
		s += (a[i] + (w << 1)) * (a[i] + (w << 1));
		if (s > c) return false;
	} return true;
}
void slove() {
	cin >> n >> c;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl l = 1, r = 1000000000;
	while (l < r) {
		intl mid = (l + r + 1) >> 1;
		if (check(mid)) l = mid; // check == true <=> actual <= limit
		else r = mid - 1;
	}
	cout << l << "\n";
}
int main() { cin.tie(0)->sync_with_stdio(0);
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
