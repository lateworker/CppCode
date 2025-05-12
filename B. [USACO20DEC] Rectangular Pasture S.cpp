#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2500;
int n;
struct Pos { int x, y; } a[N + 10];
bitset<N + 10> g[N + 10][N + 10];
unordered_set< bitset<N + 10> > bst;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
	sort(a + 1, a + 1 + n, [&](Pos u, Pos v) { return u.y < v.y; } );
	for (int i = 1; i <= n; i++) a[i].y = i;
	sort(a + 1, a + 1 + n, [&](Pos u, Pos v) { return u.x < v.x; } );
	for (int i = 1; i <= n; i++) {
		a[i].x = i, g[a[i].x][a[i].y].set(i);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] |= g[i - 1][j] | g[i][j - 1];
	for (int i = 1; i <= n; i++) {
		vector<int> vec;
		for (int j = i - 1; j >= 1; j--) {
			vec.push_back(a[j].y);
			for (int y : vec) {	
				int x1, y1, x2, y2;
				x1 = a[j].x, x2 = a[i].x;
				y1 = min(y, a[i].y), y2 = max(y, a[i].y);
				bst.insert(~ (g[x1 - 1][y2] | g[x2][y1 - 1]) & g[x2][y2]);
			}
		}
	}
	cout << bst.size() + n + 1 << "\n";
	return 0;
}
/*
- 1 2
- 1 3
1 2 3
1 2 3 4
- 2 3
- 2 3 4
- 3 4
- 1 3 4

*/
