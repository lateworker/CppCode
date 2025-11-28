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
using pii = pair<int, int>;
const int N = 10000000, PN = 670000;
int prm[PN + 10], pn, isnp[N + 10];
void gtprm(int x, set<int>& now) {
	while (x > 1) now.insert(prm[isnp[x]]), x /= prm[isnp[x]];
}
void inp(vector<int>& a) {
	int x; cin >> x;
	while (x) a.push_back(x % 10), x /= 10;
}
int mke(const vector<int>& a) {
	int res = 0;
	for (int x : a) {
		res = res * 10 + x;
		if (!res) return 0;
	} return res;
}
void slove() {
	vector<int> x, y;
	inp(x), inp(y);
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	
	set<int> px, py;
	do gtprm(mke(x), px); while (next_permutation(x.begin(), x.end()));
	do gtprm(mke(y), py); while (next_permutation(y.begin(), y.end()));
	
	for (auto u = px.rbegin(); u != px.rend(); u++) {
		if (py.count(*u)) {
			cout << *u << '\n';
			return;
		}
	} cout << "1\n";
}
int main() { ffopen();
	isnp[0] = isnp[1] = 0;
	for (int i = 2; i <= N; i++) {
		if (!isnp[i]) prm[++pn] = i;
		for (int j = 1; j <= pn && (intl) i * prm[j] <= N; j++) {
			isnp[i * prm[j]] = j;
			if (i % prm[j] == 0) break;
		}
	}
	for (int i = 1; i <= pn; i++) isnp[prm[i]] = i;
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
