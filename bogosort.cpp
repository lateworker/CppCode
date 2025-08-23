#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
const int N = 1000;

mt19937 seed(time(0));

//void mergesort(vector<int>& a) {
//	size_t n = a.size(), tn, td;
//	for (tn = 1, td = 0; tn < n; tn <<= 1, ++td);
//	a.resize(tn); vector<int> b(tn);
//	for (size_t k = 0; k < td; k++) {
//		size_t x = 1 << k, y = 1 << (k + 1);
//		for (size_t i = 0; i < tn; i += y) {
//			size_t psz = 0, px = i, py = i + x;
//			while (px < i + x || py < i + y) b[psz++] = py == i + y || (px < i + x && a[px] < a[py]) ? a[px++] : a[py++];
//			while (~--psz) a[i + psz] = b[psz];
//		}
//	} a.resize(n);
//}
//void mergesort(vector<int>& a) {
//	size_t n = a.size();
//	vector<vector<int> > b(n << 1);
//	for (size_t i = 0; i < n; i++) b[i + n].emplace_back(a[i]);
//	for (size_t i = n - 1; i; i--) {
//		size_t pl = 0, pr = 0, le = i << 1, ri = i << 1 | 1;
//		while (pl < b[le].size() || pr < b[ri].size()) 
//			b[i].emplace_back(pr == b[ri].size() || (pl < b[le].size() && b[le][pl] < b[ri][pr]) ? b[le][pl++] : b[ri][pr++]);
//		b[le].clear(), b[ri].clear();
//	} a = b[1];
//}
void mergesort(vector<int>& a) {
#define le i << 1
#define ri i << 1 | 1
	size_t n = a.size(); if (!n) return;
	vector<size_t> lf(n << 1), rt(n << 1);
	vector<int> b(n);
	for (size_t i = 0; i < n; i++) lf[i + n] = rt[i + n] = i;
	for (size_t i = n - 1; i; i--) {
		lf[i] = min(lf[le], lf[ri]), rt[i] = max(rt[le], rt[ri]);
		size_t pl = lf[le], pr = lf[ri], j = 0;
		while (pl <= rt[le] || pr <= rt[ri]) b[j++] = (pr > rt[ri] || (pl <= rt[le] && a[pl] < a[pr])) ? a[pl++] : a[pr++];
		while (~--j) a[lf[i] + j] = b[j];
	}
	for (size_t i = 1; i < (n << 1); i++)
		cout << i << " " << lf[i] << " " << rt[i] << "\n";
#undef le
#undef ri
}

void check(const vector<int>& a) {
	bool issort = true;
	for (size_t i = 1; i < a.size(); i++) if (a[i - 1] > a[i]) issort = false;
	cout << (issort ? "Sorted" : "Unfinished") << "\n";
	cout << "First: " << a.front() << " Last: " << a.back() << "\n";
	for (int x : a) cout << x << " "; cout << "\n";
}
int main() {
	int n = 10;
	vector<int> a;
	for (int i = 1; i <= n; i++) a.emplace_back(seed());
	mergesort(a);
	check(a);
	return 0;
}
