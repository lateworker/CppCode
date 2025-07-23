#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int n; pair<int, int> a[N + 10];
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
	sort(a + 1, a + n + 1, greater<pair<int, int> >());
	int lx = n, rx = 0, cnt = 0, ans = 0;
	for (int i = 1; i <= n;) {
		int now = a[i].first;
		for (; a[i].first == now; i++, cnt++)
			lx = min(lx, a[i].second), rx = max(rx, a[i].second);
		ans = max(ans, lx == rx ? 1 : rx - lx - cnt + 3);
	}
	cout << ans << "\n";
	return 0;
}
