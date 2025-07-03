#include <bits/stdc++.h>

namespace std {

#define U_1e8 unsigned(1e8)

	class intll {
		bool sign;
		basic_string<unsigned> digit;
		bool is_zero() const;

	public:
		friend istream& operator>> (istream& cin, intll& a);
		friend ostream& operator<< (ostream& cout, const intll& a);

		static strong_ordering compare_abs(const intll& a, const intll& b);
		static void add_abs(const intll& a, const intll& b, intll& c);
		static void substract_abs(const intll& a, const intll& b, intll& c);
		static void calculate_abs(const intll& a, const intll& b, intll& c, char op);

		intll() { sign = false; digit = {0}; }
		intll(const string& s) { this->str(s); }
		intll(const char* s) { this->str(s); }
		template<class T> intll(const T& s) { this->str(s); }

		void str(const string& s);
		void str(const char* s);
		template<class T> void str(const T& s);
		string str() const;
		
		bool operator== (const intll& b) const;
		strong_ordering operator<=> (const intll& b) const;
		
		intll operator+ () const;
		intll operator- () const;
		intll operator+ (const intll& b) const;
		intll operator- (const intll& b) const;
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

	strong_ordering intll::compare_abs(const intll& a, const intll& b) {
		if ((a.is_zero() && b.is_zero()) || a.digit == b.digit) return strong_ordering::equal;
		bool res = false;
		if (a.digit.size() == b.digit.size()) {
			for (auto u = a.digit.rbegin(), v = b.digit.rbegin(); u != a.digit.rend(); u++, v++)
				if (*u != *v) { res = (*u > *v); break; }
		} else res = (a.digit.size() > b.digit.size());
		return res ? strong_ordering::greater : strong_ordering::less;
	}

	void intll::add_abs(const intll& a, const intll& b, intll& c) {
		c.digit.clear();
		auto u = a.digit.begin(); bool carry = 0;
		for (auto v = b.digit.begin(); v != b.digit.end(); u++, v++) {
			unsigned now = *u + *v + carry;
			carry = (now >= U_1e8);
			c.digit.push_back(now - (carry ? U_1e8 : 0));
		}
		for (; u != a.digit.end(); u++) {
			unsigned now = *u + carry;
			carry = (now >= U_1e8);
			c.digit.push_back(now - (carry ? U_1e8 : 0));
		}
		if (carry) c.digit.push_back(carry);
	}

	void intll::substract_abs(const intll& a, const intll& b, intll& c) {
		c.digit.clear();
		auto u = a.digit.begin(); bool carry = 0;
		for (auto v = b.digit.begin(); v != b.digit.end(); u++, v++) {
			unsigned now = U_1e8 + *u - *v - carry;
			carry = (now < U_1e8);
			c.digit.push_back(now - (carry ? 0 : U_1e8));
		}
		for (; u != a.digit.end(); u++) {
			unsigned now = U_1e8 + *u - carry;
			carry = (now < U_1e8);
			c.digit.push_back(now - (carry ? 0 : U_1e8));
		}
		while (!c.digit.empty() && !c.digit.back()) c.digit.pop_back();
		if (c.digit.empty()) c.digit = {0};
	}

	void intll::calculate_abs(const intll& a, const intll& b, intll& c, char op) {
		switch (op) {
			case '+': intll::add_abs(a, b, c); break;
			case '-': intll::substract_abs(a, b, c); break;
		}
	}

	bool intll::is_zero() const {
		for (auto u = digit.rbegin(); u != digit.rend(); u++)
			if (*u) return false;
		return true;
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
	
	bool intll::operator== (const intll& b) const {
		return (is_zero() && b.is_zero()) || (sign == b.sign && digit == b.digit);
	}
	strong_ordering intll::operator<=> (const intll& b) const {
		if (operator==(b)) return std::strong_ordering::equal;
		if (sign && !b.sign) return std::strong_ordering::less;
		if (!sign && b.sign) return std::strong_ordering::greater;
		bool res = false; // res : is self greater than b?
		if (digit.size() == b.digit.size()) {
			for (auto u = digit.rbegin(), v = b.digit.rbegin(); u != digit.rend(); u++, v++)
				if (*u != *v) { res = (*u > *v); break; }
		} else res = (digit.size() > b.digit.size());
		return sign ^ res ? std::strong_ordering::greater : std::strong_ordering::less;
	}
	
	intll intll::operator+ () const { return *this; }
	intll intll::operator- () const {
		intll c = *this;
		c.sign = !c.sign;
		return c;
	}
	
	intll intll::operator+ (const intll& b) const {
		intll c;
		
		std::strong_ordering cmp = compare_abs(*this, b);
		char op = (sign == b.sign ? '+' : '-');
		c.sign = cmp == std::strong_ordering::greater ?
		(calculate_abs(*this, b, c, op), sign) : (calculate_abs(b, *this, c, op), b.sign);
		
		return c;
	}
	
	intll intll::operator- (const intll& b) const {
		intll c;
		
		std::strong_ordering cmp = compare_abs(*this, b);
		char op = (sign == !b.sign ? '+' : '-');
		c.sign = cmp == std::strong_ordering::greater ?
		(calculate_abs(*this, b, c, op), sign) : (calculate_abs(b, *this, c, op), !b.sign);
		
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
	int n; cin >> n;
	intll x = 1, y = 1;
	for (int i = 2; i <= n; i++)
		tie(x, y) = make_tuple(y, x + y);
	cout << y << "\n";
	return 0;
}
