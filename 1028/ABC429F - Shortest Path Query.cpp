#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const int inf = 0x3f3f3f3f, N = 200000;
struct Matr {
	int val[3][3]; bool used;
	Matr() {
		used = false;
		val[0][0] = val[0][1] = val[0][2] = inf;
		val[1][0] = val[1][1] = val[1][2] = inf;
		val[2][0] = val[2][1] = val[2][2] = inf;
	}
	void make(char* s) {
		used = true;
		for (int i = 0; i < 3; i++) {
			for (int j = i; j < 3; j++) {
				bool tag = true;
				for (int k = i; k <= j; k++) {
					if (s[k] == '#') { tag = false; break; }
				}
				val[j][i] = val[i][j] = tag ? j - i + 1 : inf;
			}
		}
	}
} st[N * 3 + 10];
Matr operator+ (const Matr& x, const Matr& y) {
	if (!x.used) return y;
	if (!y.used) return x;
	Matr z; z.used = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int x0 = x.val[i][j];
			for (int k = 0; k < 3; k++) {
				chkmin(z.val[i][k], x0 + y.val[j][k]);
			}
		}
	} return z;
}
inline void flip(char& c) { c = c == '.' ? '#' : '.'; }
int n, m, tn;
char g[N + 10][3];
int main() { ffopen();
	cin >> n;
	for (tn = 1; tn <= n + 1; tn <<= 1);
	for (int c = 0; c < 3; c++) {
		for (int i = 1; i <= n; i++)
			cin >> g[i][c];
	}
	for (int i = 1; i <= n; i++) st[i + tn].make(g[i]);
	for (int i = tn - 1; i; i--) st[i] = st[i << 1] + st[i << 1 | 1];
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y; --x;
		flip(g[y][x]);
		st[y + tn].make(g[y]);
		for (int u = (y + tn) >> 1; u; u >>= 1) st[u] = st[u << 1] + st[u << 1 | 1];
		cout << (st[1].val[0][2] > (n << 2) ? -1 : st[1].val[0][2] - 1) << '\n';
	}
	return 0;
}

