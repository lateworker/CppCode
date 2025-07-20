#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 1500;
int n, m;
bool g[N + 10][N + 10];
vector<pair<int, int> > h[N + 10], s[N + 10];
int ch[N + 10], cs[N + 10];
bool check(int len) {
	if (m == 1) return ch[len] >= 1 || cs[len] >= 1;
	if (ch[len] >= 2 || cs[len] >= 2) return true;
	if (!cs[len]) return ch[len * 2] >= 1;
	if (!ch[len]) return cs[len * 2] >= 1;
	pair<int, int> p1[2], p2[2], p3[2], p4[2];
	for (int i = len; i <= n; i++) {
		if (h[i].size()) {
			p1[0] = h[i].front();
			p3[0] = {p1[0].first, p1[0].second + len - 1};
			p3[1] = {p1[0].first, p1[0].second + i - 1};
			p1[1] = {p1[0].first, p3[1].second - len + 1};
		}
		if (s[i].size()) {
			p2[0] = s[i].front();
			p4[0] = {p2[0].first + len - 1, p2[0].second};
			p4[1] = {p2[0].first + i - 1, p2[0].second};
			p2[1] = {p4[1].first - len + 1, p2[0].second};
		}
	}
	for (int c1 : {0, 1})
		for (int c2 : {0, 1}) {
			if (!(p1[c1].second <= p2[c2].second && p2[c2].second <= p3[c1].second && p2[c2].first <= p1[c1].first && p1[c1].first <= p4[c2].first))
				return true;
		}
	return false;
}
int main() { //ffopen("color");
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char c; cin >> c;
			g[i][j] = (c == '.');
		}
	}
	for (int i = 1; i <= n; i++) {
		int last = 0;
		for (int j = 1; j <= n + 1; j++) {
			if (!g[i][j]) {
				int len = j - last - 1;
				h[len].push_back({i, last + 1});
				last = j;
			}
		}
	}
	for (int j = 1; j <= n; j++) {
		int last = 0;
		for (int i = 1; i <= n + 1; i++) {
			if (!g[i][j]) {
				int len = i - last - 1;
				s[len].push_back({last + 1, j});
				last = i;
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		ch[i] = ch[i + 1] + h[i].size();
		cs[i] = cs[i + 1] + s[i].size();
	}
//	for (int i = 1; i <= n; i++) {
//		cout << i << "\n";
//		for (auto [x, y] : h[i]) cout << x << " " << y << "\n";
//	}
//	for (int j = 1; j <= n; j++) {
//		cout << j << "\n";
//		for (auto [x, y] : s[j]) cout << x << " " << y << "\n";
//	}
	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l << "\n";
	return 0;
}
