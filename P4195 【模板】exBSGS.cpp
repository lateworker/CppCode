#include <bits/stdc++.h>
#define C_ const
#define int long long
using namespace std;
int exGCD(int a, int b, int &x, int &y) {
	if (b == 0) return x = 1, y = 0, a;
	int d = exGCD(b, a % b, y, x);
	return y -= a / b * x, d;
}
int Inv(int a, int p) {
	int x, y;
	exGCD(a, p, x, y);
	return (x + p) % p;
}
int BSGS(int a, int b, int p) {
	unordered_map<int, int> hasx;
	int t = 1, w = 1, W; for (; t * t <= p; t++);
	W = a;
	for (int i = 0; i < t; i++, w = (long long) w * W % p) hasx[(long long) b * w % p] = i;
	W = w;
	for (int i = 1; i <= t; i++, w = (long long) w * W % p)
		if (hasx.count(w)) return (long long) i * t - hasx[w];
	return -1;
}
int exBSGS(int a, int b, int p) {
	if (b == 1 || p == 1) return 0;
	int d = __gcd(a, p);
	if (d == 1) return BSGS(a, b, p);
	if (b % d != 0) return -1;
	p /= d, b /= d;
	int ret = exBSGS(a % p, (long long) b * Inv(a / d, p) % p, p);
	if (ret != -1) ++ret;
	return ret;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int a, b, p;
	while (cin >> a >> p >> b, a + b + p > 0) {
		int ans = exBSGS(a % p, b % p, p);
		if (ans == -1) cout << "No Solution\n";
		else cout << ans << "\n";
	}
	return 0;
}
