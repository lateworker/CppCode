#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "w", stdout); \
//if (*#s) freopen(#s ".in", "r", stdin); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
mt19937 gen(time(0));
int randint(int l, int r) { return gen() % (r - l + 1) + l; }
int main() { ffopen(op4);
	int T = 1;
	int p = N;
	int n = N;
	cout << T << " " << p << " " << n << "\n";
	for (int i = 1; i <= n; i++) {
		int op = randint(0, 1);
		int x = randint(0, p - 1);
		cout << op << " " << x << "\n";
	}
	return 0;
}
