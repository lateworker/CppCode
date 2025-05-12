#include <bits/stdc++.h>
using namespace std;
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, b;
int main() {
	int* c;
	c = a + ++ b;
	c = a + ++ b;
	c = a + ++ b;
	c = a +++ b;
	cout << *c << "\n";
	return 0;
}
