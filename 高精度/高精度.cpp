#include <bits/stdc++.h>

namespace std {

#define U_1e8 unsigned(1e8)
using intll_t = basic_string<unsigned>;
	
	class intll {
		bool sign;
		intll_t digit;
		bool is_zero() const { return is_zero(digit); }

	public:
		friend istream& operator>> (istream& cin, intll& a);
		friend ostream& operator<< (ostream& cout, const intll& a);

		static bool is_zero(const intll_t& a);
		static strong_ordering compare_abs(const intll_t& a, const intll_t& b);
		static void calculate_abs(const intll_t& a, const intll_t& b, intll_t& c, char op);
		static void add_abs(const intll_t& a, const intll_t& b, intll_t& c);
		static void substract_abs(const intll_t& a, const intll_t& b, intll_t& c);
		static void multiply_abs(const intll_t& a, const intll_t& b, intll_t& c);

		intll() { sign = false; digit = {0}; }
		intll(const string& s) { this->str(s); }
		intll(const char* s) { this->str(s); }
		template<class T> intll(const T& s) { this->str(s); }

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

	strong_ordering intll::compare_abs(const intll_t& a, const intll_t& b) {
		if ((is_zero(a) && is_zero(b)) || a == b) return strong_ordering::equal;
		bool res = false;
		if (a.size() == b.size()) {
			for (size_t i = a.size() - 1; ~i; i--)
				if (a[i] != b[i]) { res = (a[i] > b[i]); break; }
		} else res = (a.size() > b.size());
		return res ? strong_ordering::greater : strong_ordering::less;
	}
	
	void intll::calculate_abs(const intll_t& a, const intll_t& b, intll_t& c, char op) {
		switch (op) {
			case '+': intll::add_abs(a, b, c); break;
			case '-': intll::substract_abs(a, b, c); break;
		}
	}

	void intll::add_abs(const intll_t& a, const intll_t& b, intll_t& c) {
		c.clear();
		auto u = a.begin(); bool carry = 0;
		for (auto v = b.begin(); v != b.end(); u++, v++) {
			unsigned now = *u + *v + carry;
			carry = (now >= U_1e8);
			c.push_back(now - (carry ? U_1e8 : 0));
		}
		for (; u != a.end(); u++) {
			unsigned now = *u + carry;
			carry = (now >= U_1e8);
			c.push_back(now - (carry ? U_1e8 : 0));
		}
		if (carry) c.push_back(carry);
	}

	void intll::substract_abs(const intll_t& a, const intll_t& b, intll_t& c) {
		c.clear();
		auto u = a.begin(); bool carry = 0;
		for (auto v = b.begin(); v != b.end(); u++, v++) {
			unsigned now = U_1e8 + *u - *v - carry;
			carry = (now < U_1e8);
			c.push_back(now - (carry ? 0 : U_1e8));
		}
		for (; u != a.end(); u++) {
			unsigned now = U_1e8 + *u - carry;
			carry = (now < U_1e8);
			c.push_back(now - (carry ? 0 : U_1e8));
		}
		while (!c.empty() && !c.back()) c.pop_back();
		if (c.empty()) c = {0};
	}
	
	void intll::multiply_abs(const intll_t& a, const intll_t& b, intll_t& c) {
		size_t n = a.size(), m = b.size();
		c.resize(n + m - 1, 0);
//		if (n < m) {
//			for (size_t j = 0; j < m; j++) {
//				for (size_t i = 0; i < n; i++) {
//					ans[i + j] += a[i] * b[j];
//				}
//			}
//		} else {
//			for (size_t i = 0; i < n; i++) {
//				for (size_t j = 0; j < m; j++) {
//					ans[i + j] += a[i] * b[j];
//				}
//			}
//		}
	}

	void intll::str(const string& s) {
		digit.clear();
		bool withsign = (s.front() == '+' || s.front() == '-');
		sign = withsign ? (s.front() == '-') : false;
		for (size_t i = withsign, j; i < s.size(); i = j) {
			j = s.size() - ((s.size() - i - 1) >> 3 << 3);
			unsigned now = 0;
			for (size_t k = i; k < j; k++) (now *= 10) += s[k] ^ 48;
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
			res += string(8 - now.size(), '0') + now;
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
	
}

using namespace std;

random_device seed;
mt19937 randx(114514);

void gen(string& s) {
	s.clear();
	int m = randx() % 18 + 1;
	s.push_back(randx() % 9 + '1');
	for (int i = 1; i < m; i++) s.push_back(randx() % 10 + '0');
}

int main() {
	intll a, b;
	cin >> a >> b;
	cout << a - b << "\n";
	return 0;
}
