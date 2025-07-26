#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "w", stdout); \
//if (*#s) freopen(#s ".in", "r", stdin); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 3000;
mt19937 gen(time(0));
int randint(int l, int r) { return gen() % (r - l + 1) + l; }
int a[N + 10], b[N + 10];
int main() { ffopen(stone);
//	int n = randint(1000, 3000);
//    int n = randint(2500, 3000);
//	a[0] = b[0] = randint(0, n + 1);
//	a[n + 1] = b[n + 1] = randint(0, n + 1);
//	for (int i = 1; i <= n; i++)
//		a[i] = randint(0, n + 1), b[i] = randint(0, n + 1);
//	cout << n << "\n";
//	for (int i = 0; i <= n + 1; i++) cout << a[i] << " \n"[i == n + 1];
//	for (int i = 0; i <= n + 1; i++) cout << b[i] << " \n"[i == n + 1];
	int n = randint(2000, 3000);
	cout << n << "\n0 ";
	for (int i = 1; i <= n; i++) cout << i << ' ';
	cout << n + 1 << "\n0 ";
	for (int i = 1; i <= n; i++) cout << n - i + 1 << ' ';
	cout << n + 1 << "\n";
	return 0;
}
