#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 200000;
int n, t[N + 10], cnt[N + 10];

void slove() {
	cin >> n;
	vector<int> vec;
	for (int i = 1; i <= n; i++) {
		int a; cin >> a;
		if (a <= n) ++cnt[a], vec.push_back(a);
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for (int a : vec) {
		for (int b = a; b <= n; b += a) t[b] += cnt[a];
	}
	cout << *max_element(t + 1, t + 1 + n) << "\n";
	for (int i = 1; i <= n; i++) t[i] = cnt[i] = 0;
}
int main() { cin.tie(0)->sync_with_stdio(0);
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
