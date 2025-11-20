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
const int N = 1000000;
int n, q, a[N + 10], f[N + 10];
int query(int l, int r) {
	for (int i = l; i <= r; i++) {
		f[i] = 0;
		for (int j = l; j <= i >> 1; j++) {
			int w = 0;
			for (int k = l; k <= j; k++) {
				if (a[k] == a[k + j - l + 1]) {
					w = 1; break;
				}
			}
			chkmax(f[i], f[j] + w);
		}
//		cerr << f[i] << " \n"[i == r];
	}
	return f[r];
}
int main() { ffopen();
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		cout << query(l, r) << '\n';
	}
	return 0;
}
