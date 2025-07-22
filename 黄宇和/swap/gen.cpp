#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
freopen((string(s) + ".in").c_str(), "w", stdout);
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000;
mt19937 gen(time(0));
int randint(int l, int r) { return gen() % (r - l + 1) + l; }
int main() {
	ffopen("swap5");
	int n = 100000;
	int m = 200000;
	cout << n << " " << m << "\n";
	for (int i = 1; i <= m; i++) {
		int z = randint(1, n - 1);
		int x = randint(1, z);
		int y = randint(z + 1, n);
		cout << x << " " << y << "\n";
	}
	return 0;
}
