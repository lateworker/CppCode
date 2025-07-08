#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
int n, m, a[N + 10];
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n);
	int x = 0, y = 0;
	for (int i = 1; i <= n; i++) {
		if (i == 1 || a[i] - a[i - 1] > m) x = max(x, y), y = 1;
		else ++y;
	} x = max(x, y);
	cout << n - x << "\n";
}
int main() {
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
