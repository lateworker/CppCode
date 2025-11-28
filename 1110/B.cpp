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
intl n, a[N + 10], b[N + 10];
bool check() {
	if (a[n] != b[n]) return false;
	multiset<int> st1, st2;
	for (int i = 1; i < n; i += 2) {
		st1.insert(a[i]);
		st2.insert(b[i]);
	}
	if (st1 != st2) return false;
	st1.clear(), st2.clear();
	for (int i = 2; i < n; i += 2) {
		st1.insert(a[i]);
		st2.insert(b[i]);
	}
	return st1 == st2;
}
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	for (int i = 1; i <= n; i++) cin >> b[i], b[i] += b[i - 1];
	cout << (check() ? "yeS" : "nO") << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
