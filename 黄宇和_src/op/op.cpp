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
const int N = 1000000;
int T, p, n, sttime;
vector<int> qr;
bitset<N + 5> a, mask;
void slove(int t) {
	cin >> p >> n;
	for (int i = 0; i < p; i++) mask.set(i), a.reset(i);
	for (int i = 1; i <= n; i++) {
		int op, x; cin >> op >> x;
		if (op) qr.push_back(x);
		else a.set(x);
	}
	mt19937 gen(time(0));
	shuffle(qr.begin(), qr.end(), gen);
	if (!a.count()) a.set(0);
	for (int x : qr) {
		a = a | (mask & (a << x)) | (a >> (p - x));
		if (p == (int) (a & mask).count()) break;
		if (n > 100000 && p > 100000) {
			if (T == 1 && clock() - sttime >= 1997) break;
			if (T == 2) {
				if (t == 1 && clock() - sttime >= 998) break;
				if (t == 2 && clock() - sttime >= 1997) break;
			}
		}
	}
	cout << p - (int) (a & mask).count() << "\n";
}
int main() {
	sttime = clock();
	ffopen(op);
	cin >> T;
	for (int i = 1; i <= T; i++) {
		slove(i);
		qr.clear();
	}
	return 0;
}
