#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 200000;
intl n, a[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) a[i] += a[i - 1];
	intl ans = 0;
	for (intl i = 1, j = 1; i <= n; ans = max(ans, j - i), i++)
		while (j <= n && a[j] < (a[i] - a[i - 1]) * j) ++j;
	cout << ans << "\n";
}
int main() {
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
