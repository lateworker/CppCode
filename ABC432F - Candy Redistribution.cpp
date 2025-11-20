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
const int N = 20;
int n, a[N + 10], f[(1 << N) + 10];
intl b[(1 << N) + 10];
int main() {
	cin >> n;
	intl sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	if (sum % n) { cout << "-1\n"; return 0; }
	sum /= n;
	for (int i = 1; i <= n; i++) a[i] -= sum;
	int ALL = (1 << n) - 1;
	memset(f, 0xc0, sizeof f), f[0] = 0;
	for (int S = 0; S <= ALL; S++) {
		for (int i = 1; i <= n; i++) {
			if (S >> (i - 1) & 1) b[S] += a[i];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int S = 0; S <= ALL; S++) {
			if (S >> (i - 1) & 1) continue;
			int T = S | (1 << (i - 1));
			chkmax(f[T], f[S] + (b[T] == 0));
		}
	}
	cout << n - f[ALL] << '\n';
	
	return 0;
}
