#include <bits/stdc++.h>
using namespace std;
int n;
void slove() {
	cin >> n;
	int ans = 0, ma = 0;
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		if (a <= 10 && ma < b) ma = b, ans = i;
	} cout << ans << "\n";
}
int main() {
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
