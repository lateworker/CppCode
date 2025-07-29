#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 300000, inf = 0x3f3f3f3f, Mod = 998244353;
using intl = long long;
int n, a[N + 10], f[N + 10], g[N + 10];
int gmex() {
	vector<int> t(N + 5, 0);
	for (int i = 1; i <= n; i++) ++t[a[i]];
	for (int i = 0; i <= n; i++) if (!t[i]) return i;
	return n + 1;
}
int main() { ffopen(divide);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int mex = gmex(); f[0] = 1;
	for (int i = 0; i <= n; i++) g[i] = 0;
	for (int i = 1; i <= n; i++) {
//		f[i] = 
	}
	cout << f[n] << "\n";
	return 0;
}
