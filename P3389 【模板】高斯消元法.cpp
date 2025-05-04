#include <bits/stdc++.h>
using namespace std;
const int N = 114;
double mat[N][N], res[N];
const double eps = 1e-9;
template<class T>
struct Matrix {
	int R, C;
	vector< vector<T> > val;
};
template<class T>
pair<Matrix<T>, bool> gauss(Matrix<T> A, const Matrix<T>& B, auto cmp) {
	if (A.R != B.R) return make_pair(Matrix<T>(), true);
	for (int p = 0; p < A.R; p++) {
		A.val[p].swap(*max_element(A.val.begin() + p + 1, A.val.end(),
			[&](const vector<T>& x, const vector<T>& y) { return cmp(x[p], y[p]); } ) );
		for (int i = p + 1; i < A.R; i++) {
			if (A.val[i][p] == 0) continue;
			T k = A.val[i][p] / A.val[p][p]; B.val[i][0] -= B.val[p][0] * k;
			for (int j = p; j < A.C; j++) A.val[i][j] -= A.val[p][j] * k;
			A.val[i][p] = 0;
		}
	}
	for ()
}
int solve(int n, int m) {
	for (int p = 0; p < n; p++) {
		int R = p;
		for (int i = p + 1; i < n; ++i)
			if (abs(mat[i][p]) > abs(mat[R][p])) R = i;
		if (R != p) swap(mat[p], mat[R]);
		for (int i = p + 1; i < n; ++i) if (abs(mat[i][p]) > eps) {
				double k = mat[i][p] / mat[p][p];
				for (int j = p; j < m + 1; ++j) mat[i][j] -= mat[p][j] * k;
				mat[i][p] = 0;
			}
	}
	for (int i = n; i < m; ++i)
		if (abs(mat[i][n]) > eps) return -1;
	for (int i = m - 1; i >= 0; --i) {
		for (int j = i + 1; j < m; ++j) mat[i][m] -= mat[i][j] * res[j];
		res[i] = mat[i][m] / mat[i][i];
	}
	return 0;
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
