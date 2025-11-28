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
const int N = 500000, inf = 0x3f3f3f3f, Mod = 998244353;
int n, a[N + 10], f[N + 10], pow2[N + 10];
bitset<N + 10> g;
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	a[0] = a[n + 1] = inf;
	vector<int> stk = {0};
	for (int i = 1; i <= n; i++) {
		while (a[stk.back()] <= a[i]) stk.pop_back();
		if (stk.back()) g[i] = true;
		stk.push_back(i);
	}
	stk = {n + 1};
	for (int i = n; i >= 1; i--) {
		while (a[stk.back()] <= a[i]) stk.pop_back();
		if (g[i]) ++f[stk.back()];
		stk.push_back(i); 
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cout << pow2[cnt += f[i]] << " \n"[i == n];
	}
}
int main() {
	ffopen();
	pow2[0] = 1;
	for (int i = 1; i <= N; i++) pow2[i] = (pow2[i - 1] << 1) % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 0; i <= n + 1; i++) g[i] = false, f[i] = 0;
	} 
	return 0;
}

