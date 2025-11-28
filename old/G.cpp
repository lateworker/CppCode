#define MultiCase (cin >> CaseId)
#define Main(Callback) main() { int CaseId = 1; { Callback } CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else return 0
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
const intl N = 100000, PN = 200000, PA = 2000000;
int n, a[N + 10], prm[PN + 10], pn;
bitset<PA + 10> isnp;
vector<int> vec = {1};
void initprm() {
	isnp[0] = isnp[1] = true;
	for (int i = 2; i <= PA; i++) {
		if (!isnp[i]) prm[++pn] = i;
		for (int j = 1; j <= pn && (intl) i * prm[j] <= PA; j++) {
			isnp[i * prm[j]] = true;
			if (i % prm[j] == 0) break;
		}
	}
	for (int i = 1; i <= pn; i++)
		for (intl j = prm[i]; j <= PA; j *= prm[i]) vec.push_back(j);
	sort(vec.begin(), vec.end());
}
int Main(ffopen(); initprm(); MultiCase; ) {
	cin >> n;
	set<int> st;
	for (int i = 1; i <= n; i++) cin >> a[i], st.insert(a[i]);
	for (int x : vec) {
		if (!st.count(x)) {
			cout << x << '\n';
			break;
		}
	}
} Return; }

