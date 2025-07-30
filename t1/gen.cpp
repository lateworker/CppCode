#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
int n;
mt19937 gen(time(0));
int randint(int l, int r) { return gen() % (r - l + 1) + l; }
int main() {
	n = 5;
	for (int i = 1; i <= n; i++) cout << randint(1, 15) << " \n"[i == n];
	return 0;
}
