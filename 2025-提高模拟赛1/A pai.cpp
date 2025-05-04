#include <bits/stdc++.h>
using namespace std;
int count(string s) {
	int cnt = 0;
	for (size_t i = 0; (i = s.find("2023", i) + 1) - 1 != string::npos; ++cnt);
	return cnt;
}
int ans, n, k;
void dfs(int i, string now) {
	if (i > n) {
		if (count(now) == k) ++ans;
//		cout << now << "\n";
		return;
	}
	for (int j = 0; j <= 9; j++) {
		dfs(i + 1, now + to_string(j));
	}
}
int main() {
	cin >> n >> k;
	dfs(1, "");
	cout << ans << "\n";
	return 0;
}
