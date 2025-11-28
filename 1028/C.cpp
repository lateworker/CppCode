#define MultiCase (cin >> CaseId)
#define Main(Callback) main() { int CaseId = 1; { Callback } CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else return 0
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
const int N = 100000;
int n;
bitset<N + 10> a, b;
int Main(ffopen(); MultiCase; ) {
	cin >> n;
	int c1 = 0;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		a[i] = c == '1';
		c1 += a[i];
	}
	if (min(c1, n - c1) != n >> 1) { cout << "No\n"; Return; }
	for (int i = 1; i <= n; i++) {
		if (a[i] == a[n]) {
			for (int j = 1; j < i; j++) b[j] = 0;
			for (int j = i; j <= n; j++) b[j] = 1;
			break;
		}
	}
	int sum[2] = {0, 0};
	for (int i = 1; i <= n; i++) {
		sum[a[i]] += b[i];
	}
	cout << (abs(sum[0] - sum[1]) > 1 ? "No" : "Yes") << '\n';
} Return; }

