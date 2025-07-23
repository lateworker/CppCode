#include <bits/stdc++.h>
using namespace std;
const int N = 114;
double mat[N][N], res[N];
int fpow(int a, int b, const int& Mod) { int c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
void mod(int& a, const int& Mod) { a = (a % Mod + Mod) % Mod; }
void gauss(vector< vector<int> > mat, vector<int>& res, int n, int Mod) {
	for (int p = 0; p < n; p++)
		for (int i = p + 1; i < n; i++) {
			if (mat[i][p] == 0) continue;
			int val = mat[i][p] * fpow(mat[p][p], Mod - 2, Mod) % Mod;
			for (int j = p; j <= n; j++) mat[i][j] -= mat[p][j] * val % Mod, mod(mat[i][j], Mod);
			mat[i][p] = 0;
		}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++)
			mat[i][n] -= mat[i][j] * res[j] % Mod, mod(mat[i][n], Mod);
		res[i] = mat[i][n] * fpow(mat[i][i], Mod - 2, Mod) % Mod;
	}
}
int main() {
//	Matrix<int> a, b;
//	gauss<int>(a, b, [](const int& a, const int& b) { return abs(a) > abs(b); } );
	int n; cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= n; ++j)
			cin >> mat[i][j];
	if (solve(n, n)) {
		cout << "No Solution";
	} else {
		for (int i = 0; i < n; ++i) printf("%.2lf\n", res[i]);
	}
	return 0;
}
