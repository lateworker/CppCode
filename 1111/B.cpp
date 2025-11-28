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
int n, a[N + 10];
void slove() {
	cin >> n;
	if (n % 3 == 0) { a[1] = 1, a[2] = 3, a[3] = 2; }
	if (n % 3 == 1) { a[1] = 1, a[2] = 3, a[3] = 2, a[4] = 4; }
	if (n % 3 == 2) { a[1] = 4, a[2] = 5, a[3] = 2, a[4] = 1, a[5] = 3; }
	for (int i = n; i >= 6; i -= 3) {
		a[i] = i, a[i - 1] = i - 1, a[i - 2] = i - 2;
		if (a[i] % 3 == 1) swap(a[i - 1], a[i - 2]);
		if (a[i - 1] % 3 == 1) swap(a[i], a[i - 2]);
		if (a[i - 2] % 3 == 1) swap(a[i], a[i - 1]);
	}
	for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
