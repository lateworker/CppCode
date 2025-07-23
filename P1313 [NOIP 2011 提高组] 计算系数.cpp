#include <bits/stdc++.h>
using namespace std;
const int Mod = 10007;
int fpow(int a, int b) { int c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
int inv(int a) { return fpow(a, Mod - 2); }
int fac(int n) { int c = 1; for (int i = 2; i <= n; i++) (c *= i) %= Mod; return c; }
int C(int n, int m) { return fac(n) * inv(fac(m)) % Mod * inv(fac(n - m)) % Mod; }
int a, b, k, n, m;
int main() {
	cin >> a >> b >> k >> n >> m;
	cout << fpow(a, n) * fpow(b, m) % Mod * C(k, min(n, m)) % Mod;
	return 0;
}
