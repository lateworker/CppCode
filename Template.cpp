#include <bits/stdc++.h>

//using namespace std;

template<class T_, size_t N_, T_ DEFAULT = T_()>
class Array {
	T_ val[N_]; size_t ver[N_], clk;
public:
	Array() { clk = 1; }
	T_& operator[] (size_t i) { if (ver[i] != clk) ver[i] = clk, val[i] = DEFAULT; return val[i]; }
	void clear() { ++clk; }
};

template<class T_, size_t N_>
class Graph {
	inline static size_t psz;
	inline static std::pair<T_, size_t> pool[N_];
	struct iterator {
		size_t now;
		T_& operator* () const { return pool[now].first; }
		bool operator== (iterator it) const { return now == it.now; }
		iterator& operator++ () { now = pool[now].second; return *this; }
	}; size_t head;
public:
	Graph() { head = 0; }
	iterator begin() const { return {head}; }
	iterator end() const { return {0}; }
	void push_back(const T_& val) { ++psz, this->pool[psz] = {val, head}, head = psz; }
	void clear() { psz = head = 0; }
};

int main() {
	return 0;
}
