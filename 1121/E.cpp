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
const int N = 300000;
int n, m, f[N + 10];
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		f[i] = f[i - 1] + (c == '1' ? 1 : -1);
	}
	if (f[n] < 0) for (int i = 1; i <= n; i++) f[i] = -f[i];
	int ans = (n - f[n]) >> 1;
	multiset<int> st; st.insert(f[0]);
	for (int i = 1, j = 0; i <= n; i++) {
		while (j < i - m) st.erase(st.find(f[j++]));
		auto it = st.upper_bound(f[i] - (f[n] >> 1));
		int d = 0;
		if (it != st.end()) {  
			d = f[n] - ((f[i] - *it) << 1);
			chkmax(ans, (n - abs(d)) >> 1);
		}
		if (it != st.begin()) {
			--it;
			d = f[n] - ((f[i] - *it) << 1);
			chkmax(ans, (n - abs(d)) >> 1);
		}
		st.insert(f[i]);
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
