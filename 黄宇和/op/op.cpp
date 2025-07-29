#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/*
ori: 18
up:  312
down:333
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int T, p, n;
vector<int> qr;
bitset<N + 5> a;
//mt19937 gen(time(0));
void slove() {
	cin >> p >> n;
//	for (int i = 0; i < p; i++) a.reset(i);
	for (int i = 1; i <= n; i++) {
		int op, x; cin >> op >> x;
		if (op) qr.push_back(x);
		else a.set(x);
	}
//	shuffle(qr.begin(), qr.end(), gen);
	if (!a.count()) a.set(0);
	for (int x : qr) {
//		a = a | ((a << x)) | (a >> (p - x));
		bitset<N + 5> b = a;
		for (int y = b._Find_first(); y < p; y = b._Find_next(y)) {
			a.set((x + y) % p);
		}
//		if (p == (int) (a & mask).count()) break;
	}
	int ans = 0;
	for (int i = 0; i < p; i++) {
		if (!a[i]) ++ans;
	}
	cout << ans << "\n";
}
int main() {
	ffopen();
	cin >> T;
	for (int i = 1; i <= T; i++) {
		slove();
		qr.clear();
		a.reset();
	}
	return 0;
}
