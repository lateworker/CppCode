#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
int p, n;
vector<int> qr;
set<int> ans;
void slove() {
	cin >> p >> n;
	for (int i = 0; i < p; i++) ans.insert(i);
	for (int i = 1; i <= n; i++) {
		int op, x; cin >> op >> x;
		if (op) qr.push_back(x);
		else if (ans.count(x)) ans.erase(x);
	}
	sort(qr.begin(), qr.end(), greater<int>());
	if ((int) ans.size() == p) ans.erase(0);
	for (int x : qr) {
		set<int> now = ans;
		for (int y : now) {
			if (!now.count((y - x + p) % p)) ans.erase(y);
		}
	}
	cout << ans.size() << "\n";
}
int main() { ffopen(op3);
	int T; cin >> T;
	while (T--) {
		slove();
		ans.clear(), qr.clear();
	}
	return 0;
}
