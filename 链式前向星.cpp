#include<bits/stdc++.h>
using namespace std;

template<class dat_t, size_t M>
class Graph{
	inline static size_t psz, nxt[M];
	inline static dat_t dat[M];
	struct iterator{
		size_t now;
		dat_t operator* () const { return dat[now]; }
		bool operator== (iterator it) const { return now == it.now; }
		iterator& operator++ () { now = nxt[now]; return *this; }
	};
	size_t head;
	
public:
	Graph() { head = 0; }
	iterator begin() const { return {head}; }
	iterator end() const { return {0}; }
	void push_back(dat_t dat) { ++psz, this->dat[psz] = dat, nxt[psz] = head, head = psz; }
};

const int N = 100000;
Graph<int, N * 2 + 10> g[N + 10];

int main(){
	
	for (int v : g[0]) cout << v << "\n";
	return 0;
}
