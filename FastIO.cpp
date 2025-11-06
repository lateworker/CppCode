#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cctype>
#include <cstddef>
#undef stdin
#undef stdout
#define stdin FastIO::in_fd
#define stdout FastIO::out_fd
#define IN_BUFFER_SIZE (1 << 16)
#define OUT_BUFFER_SIZE (1 << 18)
namespace FastIO {
	int in_fd = STDIN_FILENO, out_fd = STDOUT_FILENO;
	void freopen(const char* filename, const char* mode, int& file) {
		if (mode[0] == 'r') file = open(filename, O_RDONLY);
		if (mode[0] == 'w') file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1) perror("Failed to open file"), exit(1);
	}
	size_t in_idx, in_end, out_idx;
	char in_buffer[IN_BUFFER_SIZE], out_buffer[OUT_BUFFER_SIZE];
	inline char getchar() {
		if (in_idx >= in_end) {
			in_idx = 0, in_end = read(in_fd, in_buffer, IN_BUFFER_SIZE);
			if (in_end <= 0) return EOF;
		} return in_buffer[in_idx++];
	}
	inline void putchar(const char &c) {
		out_buffer[out_idx++] = c;
		if (out_idx >= OUT_BUFFER_SIZE) write(out_fd, out_buffer, out_idx), out_idx = 0;
	}
	inline void flush() { if (out_idx > 0) write(out_fd, out_buffer, out_idx), out_idx = 0; }
	struct CIO { ~CIO() { flush(); } } cio;
	template<typename T_>
	CIO& operator>> (CIO& cio, T_& x) {
		char c; bool f;
		for (c = getchar(), f = false; isspace(c); c = getchar());
		if (c == '-') f = true, c = getchar();
		for (x = 0; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ '0');
		if (f) { x = -x; } if (!isspace(c)) { --in_idx; } return cio;
	}
	CIO& operator>> (CIO& cio, char& c) { for (c = getchar(); isspace(c); c = getchar()); return cio; }
	CIO& operator>> (CIO& cio, char* str) {
		char c; size_t len;
		for (c = getchar(); isspace(c); c = getchar());
		for (len = 0; !isspace(c); c = getchar()) str[len++] = c;
		str[len] = '\0'; return cio;
	}
	template<typename T_>
	CIO& operator<< (CIO& cio, T_ x) {
		if (!x) { putchar('0'); return cio; }
		if (x < 0) putchar('-'), x = -x;
		static char stk[21]; size_t top;
		for (top = 0; x; x /= 10) stk[top++] = x % 10;
		for (size_t i = top - 1; ~i; --i) putchar(stk[i] ^ '0');
		return cio;
	}
	CIO& operator<< (CIO& cio, char c) { putchar(c); return cio; }
	CIO& operator<< (CIO& cio, char* str) { for (size_t i = 0; str[i]; ++i) putchar(str[i]); return cio; }
	CIO& operator<< (CIO& cio, const char* str) { for (size_t i = 0; str[i]; ++i) putchar(str[i]); return cio; }
} using FastIO::cio; using FastIO::freopen;

#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;

int main() {
	ffopen();
	int x; cio >> x << x;
	return 0;
}
