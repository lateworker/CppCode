#include <bits/stdc++.h>
using namespace std;
char c[10][10];
void slove() {
	for (int i = 0; i < 8; i++) cin >> c[i];
	for (int j = 0; j < 8; j++) {
		string s;
		for (int i = 0; i < 8; i++) {
			if (c[i][j] != '.') s += c[i][j];
		}
		if (s != string()) {
			cout << s << "\n";
			break;
		}
	}
}
int main() {
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
