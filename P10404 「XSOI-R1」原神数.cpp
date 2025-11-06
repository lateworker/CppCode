#include <bits/stdc++.h>
#define size_(x) ((x)[-1])
#define push_back_(x, y) ((x)[++size_(x)]=(y))
using namespace std;
using intl = long long;
const intl N = 200000000, M = 100000000;
intl prime_[M + 10], *prime = prime_ + 1;
bitset<N + 10> isnp;
void initPrime() {
	isnp[0] = isnp[1] = 1;
	for (intl i = 2; i <= N; i++) {
		if (!isnp[i]) push_back_(prime, i);
		for (int j = 1; j <= size_(prime) && i * prime[j] <= N; j++) {
			isnp[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}
bool isprime(intl x) {
	if (x <= N) return !isnp[x];
	for (int j = 1; j <= size_(prime) && prime[j] * prime[j] <= x; j++)
		if (x % prime[j] == 0) return false;
	return true;
}
vector<intl> gsn;
bool vis[10];
void initGsn(int i, intl now) {
	if (isprime(now)) gsn.push_back(now);
	if (i > 9) return;
	for (intl j = 0; j <= 9; j++) if (!vis[j] && !(i == 1 && j == 0))
		vis[j] = true, initGsn(i + 1, now * 10 + j), vis[j] = false;
}
int main() { cin.tie(0)->sync_with_stdio(0);
	initPrime(), initGsn(1, 0);
	sort(gsn.begin(), gsn.end());
	int q; cin >> q;
	for (int i = 1; i <= q; i++) {
		intl l, r; cin >> l >> r;
		cout << upper_bound(gsn.begin(), gsn.end(), r) - lower_bound(gsn.begin(), gsn.end(), l) << "\n";
	}
	return 0;
}
