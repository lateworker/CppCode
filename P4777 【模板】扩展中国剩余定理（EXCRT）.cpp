#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
namespace std {
	inline void __int128_input(__int128 &a) {
		__int128 x = 0, f = 1, c = getchar();
		while (c < '0' || c > '9') {if (c == '-')f = -1; c = getchar();}
		while ('0' <= c && c <= '9') {x = (x << 1) + (x << 3) + (c ^ 48); c = getchar();}
		a = x * f;
	}
	inline void __int128_output(__int128 a) {
		if (!a) {putchar('0'); return;}
		int t = 0, c[40];
		if (a < 0) a = -a, putchar('-');
		while (a) c[t++] = a % 10 + '0', a /= 10;
		while (t--) putchar(c[t]);
	}
	istream &operator>> (istream &input, __int128 &a) {__int128_input(a); return input;}
	ostream &operator<< (ostream &output, const __int128 &a) {__int128_output(a); return output;}
#define int __int128
}
using namespace std;
void exgcd(int a, int b, int &x, int &y) {
	if (b == 0) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= x * a / b;
}
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
int n, c, d;
signed main() {
	cin >> n >> c >> d;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		int g = gcd(a, c);
		// if ((d - b) % g) exit(1);
		int x0, y0; exgcd(a / g, c / g, x0, y0);
		y0 = x0 * ((d - b) / g) * a + b;
		c = a / g * c, d = (y0 % c + c) % c;
	}
	cout << d << "\n";
	return 0;
}
