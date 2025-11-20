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
const int N = 500000, PN = 41540;
int prm[PN + 10], pn, isnp[N + 10];
void initprm() {
	for (int i = 2; i <= N; i++) {
		if (!isnp[i]) prm[++pn] = i, isnp[i] = pn;
		for (int j = 1; j <= pn && (intl) i * prm[j] <= N; j++) {
			isnp[i * prm[j]] = j;
			if (i % prm[j] == 0) break;
		}
	}
}
vector<pii> gtprm(int x) {
	vector<pii> res;
	while (x > 1) {
		if (res.empty() || res.back().first != isnp[x]) res.emplace_back(isnp[x], 0);
		++res.back().second;
		x /= prm[isnp[x]];
	} return res;
}
int n, q, a[N + 10], ld[PN + 10];
vector<pii> qry[N + 10];
map<int, int> b[N + 10];
// for any i, b[i].size() <= 6
bool chkilg(int i) {
	if (i <= 1) return false;
	vector<int> vec;
	for (auto [p, c] : b[i - 1]) vec.push_back(p);
	for (auto [p, c] : b[i]) vec.push_back(p);
	for (int p : vec) {
		int nd = b[i][p] - b[i - 1][p];
		if (!nd) continue;
		int j = ld[p], od = b[j][p] - b[j - 1]
	}
}
int main() {
	initprm();
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		for (auto [p, c] : gtprm(a[i])) b[i][p] = c;
	}
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		qry[r].emplace_back(l, i);
	}
	memset(ld, 0x3f, sizeof ld);
	int p = 1;
	for (int i = 1; i <= n; i++) {
		
	}
	return 0;
}
