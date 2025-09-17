#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
#define gc() (eof||(p==SIZE&&(buf[fread(buf,1,SIZE,stdin)]=EOF,(p=0)))||~buf[p]?buf[p++]:(eof=true,EOF))
#define ug(x) (eof=false,buf[--p]=(x))
#define pc(x) (buf[p++]=(x),p==SIZE?fl():p)
#define fl() (fwrite(buf,1,p,stdout),p=0)
namespace FastIn { constexpr size_t SIZE = 1 << 16; size_t p = SIZE; char buf[SIZE | 1], c; bool f, eof; inline void rd(char& x) { while(isspace(x=gc())); } inline void rd(char* s) { while(isspace(*s=gc()));if(eof){return;}for(;!isspace(*s)&&!eof;*++s=gc());ug(*s),*s='\0'; } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128>> rd(T& x) { x=f=0;while(isspace(c=gc()));if(eof){return;}if(c=='-'){f=true,c=gc();}for(;isdigit(c);c=gc()){x=(x<<1)+(x<<3)+(c^'0');}ug(c);if(f){x=-x;} } }
namespace FastOut { constexpr size_t SIZE = 1 << 18; char buf[SIZE], c[40]; size_t f, p; struct __{~__(){fl();}}__; inline void wt(char x) { pc(x); } inline void wt(const char* s) { while(*s)pc(*s++); } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128>> wt(T x) { if(!x){pc('0');return;}f=0;if(x<0)x=-x,pc('-');while(x){c[f++]=x%10^'0',x/=10;}while(f--){pc(c[f]);} } }
template<typename... Args> inline void rd(Args&... args) { using namespace FastIn; (rd(args), ...); }
template<typename... Args> inline void wtsp(const Args&... args) { using namespace FastOut; ((wt(args), wt(' ')), ...); if constexpr (!sizeof...(args)) wt(' '); }
template<typename... Args> inline void wtln(const Args&... args) { using namespace FastOut; ((wt(args), wt('\n')), ...); if constexpr (!sizeof...(args)) wt('\n'); }
template<typename Iter> std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value> rd(Iter begin, Iter end) { while (begin != end) rd(*begin++); }
template<typename Iter> std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value> wtsp(Iter begin, Iter end) { while (begin != end) wtsp(*begin++); }
template<typename Iter> std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value> wtln(Iter begin, Iter end) { while (begin != end) wtln(*begin++); }
using namespace std;
const int N = 200000, tn = 262144;
int n, m, a[N + 10], st[N * 3 + 10];
int lx[N + 10], rx[N + 10], ans[N + 10];
void pushup(int u) { if (u) st[u] = min(st[u << 1], st[u << 1 | 1]); }
void modify(int u, int val) {
	st[u += tn] = val;
	do pushup(u >>= 1); while (u);
}
int query(int l) {
	int u = 1;
	while (u < tn) {
		if (st[u <<= 1] >= l) u ^= 1;
	} return u - tn;
}
int main() {
	rd(n, m), rd(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) rd(lx[i], rx[i]);
	vector<int> idx(m); iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return rx[i] < rx[j]; } );
	auto pi = idx.begin();
	for (int i = 1; i <= n; i++) {
		modify(a[i], i);
		for (; pi != idx.end() && rx[*pi] == i; ++pi) ans[*pi] = query(lx[*pi]);
	}
	wtln(ans + 1, ans + m + 1);
	return 0;
}
