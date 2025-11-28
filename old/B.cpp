#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 100000;
int n, m, a[N + 10];
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cout << a[1] << ' ';
	for (int i = 2; i <= n; i++) {
		for (int j = m / a[i]; j >= 1; j--) {
			if (__gcd(j, a[i - 1] / a[i]) == 1) {
				cout << j * a[i] << ' ';
				break;
			}
		}
	} cout << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
