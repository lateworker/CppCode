#include <bits/stdc++.h>
namespace std {
	
	unsigned fpow(unsigned a, unsigned b, unsigned Mod) {
		unsigned c = 1;
		for (; b; a = (unsigned long long) a * a % Mod, b >>= 1)
			if (b & 1) c = (unsigned long long) c * a % Mod;
		return c;
	}
	
#define U_1e4 (unsigned short)(10000)
	using intll_t = vector<unsigned short>;
	
	class intll {
		bool sign;
		intll_t digit;
		bool is_zero() const { return is_zero(digit); }
		
		inline static unsigned dft_mod = 469762049;
		
	protected:
		static void add_abs(const intll_t& a, const intll_t& b, intll_t& c);
		static void substract_abs(const intll_t& a, const intll_t& b, intll_t& c);
		static void multiply_abs(const intll_t& a, const intll_t& b, intll_t& c);
		static void multiply_abs_naive(const intll_t& a, const intll_t& b, intll_t& c);
		static void dft(vector<unsigned>& p, bool is_inv);
		static void convolution(vector<unsigned> a, vector<unsigned> b, vector<unsigned>& c);
		
	public:
		friend istream& operator>> (istream& cin, intll& a);
		friend ostream& operator<< (ostream& cout, const intll& a);
		
		static bool is_zero(const intll_t& a);
		static void del_zero(intll_t& a);
		static strong_ordering compare_abs(const intll_t& a, const intll_t& b);
		static void calculate_abs(const intll_t& a, const intll_t& b, intll_t& c, char op);
		
		intll() 								{ sign = false; digit = {0}; }
		intll(const string& s) 					{ this->str(s); }
		intll(const char* s) 					{ this->str(s); }
		template<class T> intll(const T& s) 	{ this->str(s); }
		
		void str(const string& s);
		void str(const char* s);
		template<class T> void str(const T& s);
		string str() const;
		
		friend bool operator== (const intll& a, const intll& b);
		friend strong_ordering operator<=> (const intll& a, const intll& b);
		
		friend intll operator+ (const intll& a);
		friend intll operator- (const intll& a);
		friend intll operator+ (const intll& a, const intll& b);
		friend intll operator- (const intll& a, const intll& b);
		friend intll operator* (const intll& a, const intll& b);
		
		friend intll& operator+= (intll& a, const intll& b) { a = a + b; return a; }
		friend intll& operator-= (intll& a, const intll& b) { a = a - b; return a; }
		friend intll& operator*= (intll& a, const intll& b) { a = a * b; return a; }
	};
	
	istream& operator>> (istream& cin, intll& a) {
		string s;
		cin >> s;
		a.str(s);
		return cin;
	}
	
	ostream& operator<< (ostream& cout, const intll& a) {
		cout << a.str();
		return cout;
	}
	
	bool intll::is_zero(const intll_t& a) {
		for (auto u = a.rbegin(); u != a.rend(); u++)
			if (*u) return false;
		return true;
	}
	
	void intll::del_zero(intll_t& a) {
		while (!a.empty() && !a.back()) a.pop_back();
		if (a.empty()) a = {0};
	}
	
	strong_ordering intll::compare_abs(const intll_t& a, const intll_t& b) {
		if ((is_zero(a) && is_zero(b)) || a == b) return strong_ordering::equal;
		bool res = false;
		if (a.size() == b.size()) {
			for (unsigned i = a.size() - 1; ~i; i--)
				if (a[i] != b[i]) { res = (a[i] > b[i]); break; }
		} else res = (a.size() > b.size());
		return res ? strong_ordering::greater : strong_ordering::less;
	}
	
	void intll::calculate_abs(const intll_t& a, const intll_t& b, intll_t& c, char op) {
		switch (op) {
			case '+': compare_abs(a, b) == strong_ordering::greater ? add_abs(a, b, c) 			: add_abs(b, a, c); break;
			case '-': compare_abs(a, b) == strong_ordering::greater ? substract_abs(a, b, c) 	: substract_abs(b, a, c); break;
			case '*': compare_abs(a, b) == strong_ordering::greater ? multiply_abs(a, b, c) 	: multiply_abs(b, a, c); break;
		}
	}
	
	void intll::add_abs(const intll_t& a, const intll_t& b, intll_t& c) {
		c.clear();
		auto u = a.begin(); bool carry = 0;
		for (auto v = b.begin(); v != b.end(); u++, v++) {
			unsigned short now = *u + *v + carry;
			carry = (now >= U_1e4);
			c.push_back(now - (carry ? U_1e4 : 0));
		}
		for (; u != a.end(); u++) {
			unsigned short now = *u + carry;
			carry = (now >= U_1e4);
			c.push_back(now - (carry ? U_1e4 : 0));
		}
		if (carry) c.push_back(carry);
		del_zero(c);
	}
	
	void intll::substract_abs(const intll_t& a, const intll_t& b, intll_t& c) {
		c.clear();
		auto u = a.begin(); bool carry = 0;
		for (auto v = b.begin(); v != b.end(); u++, v++) {
			unsigned short now = U_1e4 + *u - *v - carry;
			carry = (now < U_1e4);
			c.push_back(now - (carry ? 0 : U_1e4));
		}
		for (; u != a.end(); u++) {
			unsigned short now = U_1e4 + *u - carry;
			carry = (now < U_1e4);
			c.push_back(now - (carry ? 0 : U_1e4));
		}
		del_zero(c);
	}
	
	void intll::multiply_abs(const intll_t& a, const intll_t& b, intll_t& c) {
		auto multiply_naive_check = [](unsigned n, unsigned m) -> bool { // always n > m
			long double phi = 8; // constant cost
			unsigned lim = 64;
			return n <= lim || exp(m - phi) <= n; // phi * log2(n) < m;
		};
		if (multiply_naive_check(a.size(), b.size())) return multiply_abs_naive(a, b, c);
		
		vector<unsigned> aa, bb, cc;
		aa.reserve(a.size() << 2);
		bb.reserve(b.size() << 2);
		for (const unsigned short& now : a) aa.push_back(now % 10), aa.push_back(now / 10 % 10), aa.push_back(now / 100 % 10), aa.push_back(now / 1000);
		for (const unsigned short& now : b) bb.push_back(now % 10), bb.push_back(now / 10 % 10), bb.push_back(now / 100 % 10), bb.push_back(now / 1000);
		convolution(aa, bb, cc);
		
		c.clear(); c.reserve(cc.size());
		static unsigned short pow10[] = {1, 10, 100, 1000};
		unsigned carry = 0, n = cc.size();
		for (unsigned i = 0; i < n; i++) {
			if ((i & 3) == 0) c.push_back(0);
			unsigned now = cc[i] + carry;
			c.back() += now % 10 * pow10[i & 3];
			carry = now / 10;
		}
		del_zero(c);
	}
	
	void intll::multiply_abs_naive(const intll_t& a, const intll_t& b, intll_t& c) {// puts("NAIVE");
		unsigned n = a.size(), m = b.size();
		c.resize(n + m, 0);
		
		for (unsigned i = 0; i < n; i++) {
			unsigned short carry = 0;
			for (unsigned j = 0; j < m; j++) {
				unsigned int now = (unsigned int) c[i + j] + a[i] * b[j] + carry;
				c[i + j] = now % U_1e4;
				carry = now / U_1e4;
			} c[i + m] = carry;
		}
		del_zero(c);
	}
	
	void intll::dft(vector<unsigned>& p, bool is_inv) {
		unsigned n = p.size(); vector<unsigned> q(n);
		for (unsigned k = n >> 1; k; k >>= 1) {
			unsigned wn = fpow(3, (dft_mod - 1) / (n / k), dft_mod);
			if (is_inv) wn = fpow(wn, dft_mod - 2, dft_mod);
			for (unsigned i = 0, w = 1; i < n; i += k, w = (unsigned long long) w * wn % dft_mod) {
				for (unsigned j = 0; j < k; j++)
					q[i + j] = ((unsigned long long) w * p[(i << 1) % n + j + k] + p[(i << 1) % n + j]) % dft_mod;
			} p.swap(q);
		}
		if (is_inv) {
			unsigned inv_n = fpow(n, dft_mod - 2, dft_mod);
			for (unsigned i = 0; i < n; i++) p[i] = (unsigned long long) p[i] * inv_n % dft_mod;
		}
	}
	
	void intll::convolution(vector<unsigned> a, vector<unsigned> b, vector<unsigned>& c) {// puts("NTT");
		unsigned m = a.size() + b.size() - 1, n = 1 << (32 - countl_zero(m - 1));
		a.resize(n), b.resize(n);
		dft(a, false), dft(b, false);
		for (unsigned i = 0; i < n; i++) a[i] = (unsigned long long) a[i] * b[i] % dft_mod;
		dft(a, true);
		c = vector<unsigned>(a.begin(), a.begin() + m);
	}
	
	void intll::str(const string& s) {
		digit.clear();
		bool withsign = (s.front() == '+' || s.front() == '-');
		sign = withsign ? (s.front() == '-') : false;
		for (unsigned i = withsign, j; i < s.size(); i = j) {
			j = s.size() - ((s.size() - i - 1) >> 2 << 2);
			unsigned short now = 0;
			for (unsigned k = i; k < j; k++) (now *= 10) += s[k] ^ 48;
			digit.push_back(now);
		}
		reverse(digit.begin(), digit.end());
	}
	void intll::str(const char* s) { this->str(string(s)); }
	template<class T> void intll::str(const T& s) { this->str(to_string(s)); }
	
	string intll::str() const {
		string res;
		if (sign && !is_zero()) res.push_back('-');
		res += to_string(digit.back());
		for (auto u = next(digit.rbegin()); u != digit.rend(); u++) {
			string now = to_string(*u);
			res += string(4 - now.size(), '0') + now;
		}
		return res;
	}
	
	bool operator== (const intll& a, const intll& b) {
		return (a.is_zero() && b.is_zero()) || (a.sign == b.sign && a.digit == b.digit);
	}
	strong_ordering operator<=> (const intll& a, const intll& b) {
		if (a == b) return std::strong_ordering::equal;
		if (a.sign && !b.sign) return std::strong_ordering::less;
		if (!a.sign && b.sign) return std::strong_ordering::greater;
		bool res = (intll::compare_abs(a.digit, b.digit) == strong_ordering::greater); // res : is self greater than b?
		return a.sign ^ res ? std::strong_ordering::greater : std::strong_ordering::less;
	}
	
	intll operator+ (const intll& a) { return a; }
	intll operator- (const intll& a) {
		intll c = a;
		c.sign = !c.sign;
		return c;
	}
	
	intll operator+ (const intll& a, const intll& b) {
		intll c;
		std::strong_ordering cmp = intll::compare_abs(a.digit, b.digit);
		char op = (a.sign == b.sign ? '+' : '-');
		c.sign = cmp == std::strong_ordering::greater ?
		(intll::calculate_abs(a.digit, b.digit, c.digit, op), a.sign) : (intll::calculate_abs(b.digit, a.digit, c.digit, op), b.sign);
		return c;
	}
	
	intll operator- (const intll& a, const intll& b) {
		intll c;
		std::strong_ordering cmp = intll::compare_abs(a.digit, b.digit);
		char op = (a.sign == !b.sign ? '+' : '-');
		c.sign = cmp == std::strong_ordering::greater ?
		(intll::calculate_abs(a.digit, b.digit, c.digit, op), a.sign) : (intll::calculate_abs(b.digit, a.digit, c.digit, op), !b.sign);
		return c;
	}
	
	intll operator* (const intll& a, const intll& b) {
		intll c;
		intll::calculate_abs(a.digit, b.digit, c.digit, '*');
		c.sign = a.sign ^ b.sign;
		return c;
	}
	
}
using namespace std;
intll fpow(intll a, int b) { intll c = 1; for (; b; a *= a, b >>= 1) if (b & 1) c *= a; return c; }
int main() { cin.tie(0)->sync_with_stdio(0);
	int T; cin >> T;
	while (T--) {
		int n; cin >> n;
		intll f = 0;
		for (int i = 1; i <= n; i++)
			f = fpow(2, i) - 1 - f;
		cout << f << "\n";
	}
	return 0;
}
