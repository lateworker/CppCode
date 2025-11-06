#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
int n, m;
long long num[maxn + 10];
bool check(int x) {
	int l = 1, cnt = 0;
	for (int i = 1; i <= n + 1; ++i) {
		if (num[i] - num[l - 1] > x) l = i, ++cnt;
	}
	return cnt <= m;
}
int main() {
	cin >> n >> m;
	int ma = 0;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		ma = max(ma, x);
		num[i] = num[i - 1] + x;
	}
	num[n + 1] = 0x3f3f3f3f3f3f3f3fLL;
	int l = ma, r = num[n];
	while (r > l) {
		int mid = l + (r - l) / 2;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << "\n";
	return 0;
}
