#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "w", stdout);
}
mt19937 gen(time(0));
int randint(int l, int r) {
	return gen() % (r - l + 1) + l;
}
int main() {
	ffopen("ex_bulb4");
	int n, q, k;
	n = 200000;
	q = 200000;
	k = randint(1, 200000);
	cout << n << " " << q << " " << k << "\n";
	for (int i = 1; i <= n; i++) cout << randint(1, k) << " \n"[i == n];
	for (int i = 1; i <= q; i++) {
		cout << randint(1, k) << "\n";
	}
	return 0;
}
