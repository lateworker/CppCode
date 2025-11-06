#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
namespace GenHelper {
	unsigned z1, z2, z3, z4, b;
	unsigned rand_() {
		b = ((z1 << 6)^z1) >> 13;
		z1 = ((z1 & 4294967294U) << 18)^b;
		b = ((z2 << 2)^z2) >> 27;
		z2 = ((z2 & 4294967288U) << 2)^b;
		b = ((z3 << 13)^z3) >> 21;
		z3 = ((z3 & 4294967280U) << 7)^b;
		b = ((z4 << 3)^z4) >> 12;
		z4 = ((z4 & 4294967168U) << 13)^b;
		return (z1 ^ z2 ^ z3 ^ z4);
	}
}
void srand(unsigned x) {
	using namespace GenHelper;
	z1 = x; z2 = (~x) ^ 0x233333333U; z3 = x ^ 0x1234598766U; z4 = (~x) + 51;
}
int read() {
	using namespace GenHelper;
	int a = rand_() & 32767;
	int b = rand_() & 32767;
	return a * 32768 + b;
}
using namespace std;
const int N = 20000000, TN = 4473;
int n, m, tn, a[3][N + 5], b[TN + 3][TN + 3];
unsigned long long s, sum;
int main() {
	cin >> n >> m >> s;
	srand(s); tn = (int) ceil(sqrt(n));
	for (int i = 1; i <= n; i++) {
		a[0][i] = a[1][i] = a[2][i] = read();
		int p = (i - 1) / tn;
		b[p][p] = max(b[p][p], a[0][i]);
	}
	for (int i = 0; i < tn; i++) {
		for (int j = i + 1; j < tn; j++) b[i][j] = max(b[i][j - 1], b[j][j]);
		for (int j = i * tn + 1; j < min(n, (i + 1) * tn); j++) a[1][j + 1] = max(a[1][j + 1], a[1][j]);
		for (int j = min(n, (i + 1) * tn); j > i * tn + 1; j--) a[2][j - 1] = max(a[2][j - 1], a[2][j]);
	}
	for (int i = 1; i <= m; i++) {
		int l = read() % n + 1, r = read() % n + 1, ans = 0;
		if (l > r) swap(l, r);
		auto [lp, rp] = make_pair((l - 1) / tn, (r - 1) / tn);
		if (lp == rp) {
			for (int i = l; i <= r; i++) ans = max(ans, a[0][i]);
		} else {
			ans = max({b[lp + 1][rp - 1], a[1][r], a[2][l]});
		}
		sum += (unsigned long long) ans;
	}
	cout << sum << "\n";
	return 0;
}
