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
const int N = 200000;
int n, a[N + 10], b[N + 10], ls[N + 10], rs[N + 10];
int build() {
	vector<int> stk;
	for (int i = 1; i < n; i++) {
		int lf = 0;
		while (!stk.empty() && b[i] > b[stk.back()]) lf = stk.back(), stk.pop_back();
		if (!stk.empty()) rs[stk.back()] = i;
		ls[i] = lf, stk.push_back(i);
	} return stk[0];
}
int dfs(int i, int l, int r) {
	if (r < l) return 0;
	if (l == r) return 1;
	int res = 0;
	
}
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) b[i] = abs(a[i] - a[i + 1]);
	build();
	
}
int main() { ffopen(); 
	
	return 0;
}
