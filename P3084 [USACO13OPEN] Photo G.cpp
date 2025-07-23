#include <bits/stdc++.h>
using namespace std;
const int N = 200000, M = 100000, inf = 0x3f3f3f3f;
int n, m, l[M + 10], r[M + 10], a[N + 10], b[N + 10], c[N + 10];
int main() {
	cin >> n >> m;
	memset(b, 0x3f, sizeof b);
	memset(c, 0xc0, sizeof c);
	for (int i = 1; i <= m; i++) {
		cin >> l[i] >> r[i];
		b[r[i]] = min(b[r[i]], l[i]);
		c[r[i]] = max(c[r[i]], l[i]);
	}
	a[n + 1] = n + 1;
	for (int i = n; i >= 1; i--)
		a[i] = min({a[i + 1], b[i], i});
	b[0] = 0;
	for (int i = 1; i <= n + 1; i++)
		b[i] = max({b[i - 1], c[i - 1]});
//	for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
//	for (int i = 1; i <= n; i++) cout << b[i] << " \n"[i == n];
	deque<int> que;
	c[0] = 0, que.push_back(0);
	for (int i = 1, j = 1; i <= n + 1; i++) {
		for (; j < a[i]; j++) {
			if (c[j] < 0) continue;
			while (!que.empty() && c[que.back()] < c[j]) que.pop_back();
			que.push_back(j);
		}
		while (!que.empty() && que.front() < b[i]) que.pop_front();
		c[i] = que.empty() ? -inf : c[que.front()] + 1;
	}
	cout << (c[n + 1] >= 0 ? c[n + 1] - 1 : -1) << "\n";
	return 0;
}
