#include <bits/stdc++.h>
using namespace std;
mt19937 gen(time(0));
int randint(int l, int r) { return gen() % (r - l + 1) + l; }
int main() {
	freopen("walk.in", "w", stdout);
	int n = 5; cout << n << "\n";
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cout << randint(1, 20) << " \n"[j == n];
	return 0;
}
