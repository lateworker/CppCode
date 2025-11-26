#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const int N = 3000;
int n[5];
char s[N + 10];
intl f[N + 10][N + 10], fr[N + 10][5], fl[N + 10][5];
int blg(int i) {
	if (0 < i && i <= n[1]) return 1;
	if (n[1] < i && i <= n[1] + n[2]) return 2;
	if (n[1] + n[2] < i && i <= n[0]) return 3;
	return 0;
}
bool in1str(int i, int j) { return blg(i) == blg(j); }
void inp();
void slove() {
	inp();
	memset(f, 0, sizeof f);
	memset(fl, 0, sizeof fl);
	memset(fr, 0, sizeof fr);
	for (int i = 1; i <= n[1]; i++) {
		for (int jj = 1; jj <= n[3]; jj++) {
			int j = n[0] - jj + 1;
			if (s[i] == s[j]) f[i][j] = 1;
		}
	}
	intl sum13 = 0;
	for (int len = n[0]; len >= 1; len--) {
		for (int i = 1; i + len - 1 <= n[0]; i++) {
			int j = i + len - 1;
			if (s[i] != s[j]) continue;
			if (in1str(i, i - 1) && in1str(j, j + 1)) f[i][j] += f[i - 1][j + 1];
			if (in1str(j, j + 1)) f[i][j] += fr[j + 1][blg(i) - 1];
			if (in1str(i, i - 1)) f[i][j] += fl[i - 1][blg(j) + 1];
			if (blg(i) == 2 && blg(j) == 2) f[i][j] += sum13;
			if (blg(i) == 1 && blg(j) == 3) sum13 += f[i][j];
			fl[i][blg(j)] += f[i][j];
			fr[j][blg(i)] += f[i][j];
		}
	}
	intl ans = 0;
	for (int i = 1; i <= n[0]; i++) {
		ans += f[i][i];
		if (in1str(i, i + 1)) ans += f[i][i + 1];
		for (int j = i + 1; j <= n[0]; j++) {
			if (blg(j) - blg(i) != 1) continue;
			ans += f[i][j];
		}
	}
	cout << ans << '\n';
}
int main() { ffopen(pali);
	int T; cin >> T;
	while (T--) {
		slove();
		n[0] = 0;
	}
	return 0;
}
void inp() {
	for (int c : {1, 2, 3}) {
		string a; cin >> a;
		n[c] = a.size();
		for (int i = 0; i < n[c]; i++) s[++n[0]] = a[i];
	}
}
/*
4
a b c
ab ba ab
ab ab ab
aa aa aa
*/
