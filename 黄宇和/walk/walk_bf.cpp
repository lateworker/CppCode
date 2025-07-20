#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 500, inf = 0x3f3f3f3f;
int n, a[N + 10][N + 10];
namespace Task1 {
	bool match() {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (a[i][j] > 1) return false;
		return true;
	}
	int main() {
		cout << 0 << "\n";
		return 0;
	}
}
namespace Task2 {
	bool match() {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (a[i][j] > 2) return false;
		return true;
	}
	int main() {
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cnt += a[i][j] - 1;
		cout << (cnt == n * n || cnt == 0 ? 0 : 1) << "\n";
		return 0;
	}
}
namespace Task3 {
	bool match() { return n <= 20; }
	int ma[2][N + 10][N + 10], mi[2][N + 10][N + 10];
	vector<int> now;
	int calc() {
		int res = 0, x, y;
		x = -inf, y = inf; // max, min
		for (int j = 1; j < (int) now.size(); j++) {
			int i = now[j];
			x = max(x, ma[0][i][j]);
			y = min(y, mi[1][i + 1][j]);
		}
		res = max(res, abs(x - y));
		x = inf, y = -inf;
		for (int j = 1; j < (int) now.size(); j++) {
			int i = now[j];
			x = min(x, mi[0][i][j]);
			y = max(y, ma[1][i + 1][j]);
		}
		res = max(res, abs(y - x));
		return res;
	}
	int ans = inf;
	void dfs(int i) {
		if (i > n) {
			ans = min(ans, calc());
			return;
		}
		for (int j = now.back(); j <= n; j++) {
			now.push_back(j);
			dfs(i + 1);
			now.pop_back();
		}
	}
	int main() {
		for (int j = 1; j <= n; j++) {
			ma[0][0][j] = -inf, mi[0][0][j] = inf;
			ma[1][0][j] = -inf, mi[1][0][j] = inf;
			for (int i = 1; i <= n; i++) {
				ma[0][i][j] = max(ma[0][i - 1][j], a[i][j]);
				mi[0][i][j] = min(mi[0][i - 1][j], a[i][j]);
			}
			ma[0][n + 1][j] = -inf, mi[0][n + 1][j] = inf;
			ma[1][n + 1][j] = -inf, mi[1][n + 1][j] = inf;
			for (int i = n; i >= 1; i--) {
				ma[1][i][j] = max(ma[1][i + 1][j], a[i][j]);
				mi[1][i][j] = min(mi[1][i + 1][j], a[i][j]);
			}
		}
		now.push_back(0);
		dfs(1);
		cout << ans << "\n";
		return 0;
	}
}

int main() {
	ffopen("walk");
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) cin >> a[i][j];
	if (Task1::match()) return Task1::main();
	if (Task2::match()) return Task2::main();
	if (Task3::match()) return Task3::main();
	return 0;
}
