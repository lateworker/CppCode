#include <bits/stdc++.h>
using namespace std;
int main() {
	int T; cin >> T;
	while (T--) {
		int a[3];
		cin >> a[0] >> a[1] >> a[2];
		sort(a, a + 3);
		cout << (a[1] + a[2] >= 10 ? "YES" : "NO") << "\n";
	}
	return 0;
}
