#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 100000;
int n, tn, q, a[N + 10], suf[N + 10], prf[N + 10];
int main() {
	ffopen("coloring");
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		a[i] = c - 'A';
	}
	vector<int> stk;
	for (int i = 1; i <= n; i++) {
		while (!stk.empty() && stk.back() > a[i]) stk.pop_back();
		if (!stk.empty() && stk.back() == a[i]) continue;
		stk.push_back(a[i]), ++prf[i];
	} for (int i = 1; i <= n; i++) prf[i] += prf[i - 1];
	stk.clear();
	for (int i = n; i >= 1; i--) {
		while (!stk.empty() && stk.back() > a[i]) stk.pop_back();
		if (!stk.empty() && stk.back() == a[i]) continue;
		stk.push_back(a[i]), ++suf[i];
	} for (int i = n; i >= 1; i--) suf[i] += suf[i + 1];
	for (int i = 1; i <= q; i++) {
		int x, y; cin >> x >> y;
		cout << prf[x - 1] + suf[y + 1] << "\n";
	}
	return 0;
}
