#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl Mod1 = 998244353, Mod2 = 1000000007;
intl n;
namespace BF {
	bool bf() { return true; }
	int main() {
		vector<string> vec;
		for (intl i = 1; i <= n; i++) {
			vec.push_back(to_string(i));
		}
		sort(vec.begin(), vec.end());
		intl sum = 0;
		for (intl i = 1; i <= n; i++) {
			intl now = stoll(vec[i - 1]);
			sum += ((i - now) % Mod1 + Mod1) % Mod1, sum %= Mod2;
		}
		cout << sum << "\n";
		return 0;
	}
}
int main() { ffopen(sort);
	cin >> n;
	if (BF::bf()) return BF::main();
	return 0;
}
