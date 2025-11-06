#include <bits/stdc++.h>
#include <unistd.h>

namespace FastIO {
	using namespace std;
	
#define IN_BUFFER_SIZE  (1 << 18)
#define OUT_BUFFER_SIZE (1 << 18)
	
	size_t in_idx, in_end;
	char in_buffer[IN_BUFFER_SIZE];
	inline char getchar() {
		if (in_idx >= in_end) {
			in_idx = 0, in_end = read(STDIN_FILENO, in_buffer, IN_BUFFER_SIZE);
			if (in_end <= 0) return EOF;
		} return in_buffer[in_idx++];
	}
	template<typename T_>
	inline void fastread(T_ &x) {
		char c; T_ b = 1;
		for (c = getchar(); !isdigit(c); c = getchar()) if (c == '-') b = -1;
		for (x = 0; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ '0');
		x *= b;
	}
	
	size_t out_idx;
	char out_buffer[OUT_BUFFER_SIZE];
	inline void putchar(const char &c) {
		out_buffer[out_idx++] = c;
		if (out_idx >= OUT_BUFFER_SIZE) write(STDOUT_FILENO, out_buffer, out_idx), out_idx = 0;
	}
	template<typename T_>
	inline void fastwrite(T_ x) {
		size_t cnt = 0;
		char str[20];
		if (x == 0) { putchar('0'); return; }
		if (x < 0) { putchar('-'); x *= -1; }
		while (x) str[cnt++] = (x % 10) + '0', x /= 10;
		for (size_t i = cnt - 1; ~i; i--) putchar(str[i]);
	}
	inline void flush() { if (out_idx > 0) write(STDOUT_FILENO, out_buffer, out_idx), out_idx = 0; }
}

#define frd FastIO::fastread
#define fwt FastIO::fastwrite
using namespace std;
using uintl = unsigned long long;
const int N = 250000, inf = 0x3f3f3f3f;
int T, n, q, a[N + 10], b[N + 10];
uintl ans[N + 10];
vector<pair<int, int>> qry[N + 10];
struct SEGT {
	struct Tag {
		uintl cx, cy, axy, ax, ay, a1;
		Tag() { cx = cy = axy = ax = ay = a1 = 0; }
		Tag(const uintl& cx, const uintl& cy, const uintl& axy, const uintl& ax, const uintl& ay, const uintl& a1) { this->cx = cx, this->cy = cy, this->axy = axy, this->ax = ax, this->ay = ay, this->a1 = a1; }
		bool operator== (const Tag& b) const { return cx == b.cx && cy == b.cy && axy == b.axy && ax == b.ax && ay == b.ay && a1 == b.a1; }
	};
	struct Val {
		uintl s, xy, x, y, l;
		Val() { s = xy = x = y = 0; l = 1; }
		Val(const uintl& s, const uintl& xy, const uintl& x, const uintl& y, const uintl& l) { this->s = s, this->xy = xy, this->x = x, this->y = y, this->l = l; }
	};
	void apply(Val& val, const Tag& tag) {
		val.s += tag.axy * val.xy + tag.ax * val.x + tag.ay * val.y + tag.a1 * val.l;
		if (tag.cx && tag.cy) {
			val.xy = tag.cx * tag.cy * val.l;
			val.x = tag.cx * val.l;
			val.y = tag.cy * val.l;
		}
		else if (tag.cx) {
			val.xy = tag.cx * val.y;
			val.x = tag.cx * val.l;
		}
		else if (tag.cy) {
			val.xy = tag.cy * val.x;
			val.y = tag.cy * val.l;
		}
	}
	void apply(Tag& u, const Tag& v) {
		if (u.cx && u.cy) {
			u.a1 += u.cx * u.cy * v.axy + u.cx * v.ax + u.cy * v.ay + v.a1;
		}
		else if (u.cx) {
			u.ay += u.cx * v.axy + v.ay;
			u.a1 += u.cx * v.ax + v.a1;
		}
		else if (u.cy) {
			u.ax += u.cy * v.axy + v.ax;
			u.a1 += u.cy * v.ay + v.a1;
		}
		else {
			u.axy += v.axy;
			u.ax += v.ax;
			u.ay += v.ay;
			u.a1 += v.a1;
		}
		if (v.cx) u.cx = v.cx;
		if (v.cy) u.cy = v.cy;
	}
	Val merge(const Val& u, const Val& v) { return Val(u.s + v.s, u.xy + v.xy, u.x + v.x, u.y + v.y, u.l + v.l); }
	Val st[N * 2 + 10]; Tag tg[N * 2 + 10];
	void pushup(int u) { if (u) st[u] = merge(st[u << 1], st[u << 1 | 1]); }
	void modify(int u, const Tag& val) { apply(st[u], val), apply(tg[u], val); }
	void pushdown(int u) {
		if (tg[u] != Tag{}) {
			modify(u << 1, tg[u]);
			modify(u << 1 | 1, tg[u]);
			tg[u] = Tag{};
		}
	}
	void update(int l, int r, const Tag& val) {
		l += n - 1, r += n;
		for (int d = __lg(n) + 1; d; d--) pushdown(l >> d), pushdown(r >> d);
		for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
			if (l & 1) u = l, modify(l++, val);
			if (r & 1) v = r, modify(--r, val);
			do pushup(u >>= 1); while (l == r && u);
			do pushup(v >>= 1); while (l == r && v);
		}
	}
	Val query(int l, int r) {
		l += n - 1, r += n;
		for (int d = __lg(n) + 1; d; d--) pushdown(l >> d), pushdown(r >> d);
		Val res;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = merge(res, st[l++]);
			if (r & 1) res = merge(res, st[--r]);
		} return res;
	}
} st;
int main() {
	frd(T), frd(n);
	for (int i = 1; i <= n; i++) frd(a[i]);
	for (int i = 1; i <= n; i++) frd(b[i]);
	frd(q);
	for (int i = 1; i <= q; i++) {
		int l, r; frd(l), frd(r);
		qry[r].emplace_back(l, i);
	}
	for (int u = n - 1; u; u--) st.pushup(u);
	vector<int> sta = {0}, stb = {0};
	a[0] = inf, b[0] = inf;
	for (int i = 1; i <= n; i++) {
		while (a[sta.back()] < a[i]) sta.pop_back();
		while (b[stb.back()] < b[i]) stb.pop_back();
		st.update(sta.back() + 1, i, SEGT::Tag(uintl(a[i]), 0, 0, 0, 0, 0));
		st.update(stb.back() + 1, i, SEGT::Tag(0, uintl(b[i]), 0, 0, 0, 0));
		st.update(1, i, SEGT::Tag(0, 0, 1, 0, 0, 0));
		sta.push_back(i), stb.push_back(i);
		for (auto [l, idx] : qry[i]) ans[idx] = st.query(l, i).s;
	}
	for (int i = 1; i <= q; i++) fwt(ans[i]), FastIO::putchar('\n');
	FastIO::flush();
	return 0;
}
