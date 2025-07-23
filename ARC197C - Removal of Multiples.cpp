#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 3000000, L = __lg(N) + 1;
intl q, a[N + 10];
bool vis[N + 10];
void modify(intl u, intl val) { for (; u <= N; u += u & -u) a[u] += val; }
intl kth(intl k) {
	intl p = 0;
	for (intl i = L; i >= 0; i--)
		if (p + (1LL << i) <= N && a[p + (1LL << i)] < k)
			p += (1LL << i), k -= a[p];
	return p + 1;
}
int main() { cin.tie(0)->sync_with_stdio(0);
	for (intl i = 1; i <= N; i++) modify(i, 1);
	cin >> q;
	while (q--) {
		intl x, y; cin >> x >> y;
		if (x <= N && !vis[x]) for (intl i = x; i <= N; i += x)
			if (!vis[i]) vis[i] = true, modify(i, -1);
		cout << kth(y) << "\n";
	}
	return 0;
}
