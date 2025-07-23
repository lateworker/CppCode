#include <bits/stdc++.h>

namespace std_intl {

#define hyperdigit(x) ((x) >= 1e4 ? ((x) >= 1e6 ? ((x) >= 1e7 ? 1e8 : 1e7) : ((x) >= 1e5 ? 1e6 : 1e5) ) : ((x) >= 1e2 ? ((x) >= 1e3 ? 1e4 : 1e3) : ((x) >= 1e1 ? 1e2 : 1e1) ) )

	class intl {
		bool sign;
		std::basic_string<bool> val;
		bool is_zero() const;

	public:
		friend std::istream& operator>> (std::istream& cin, intl& a);
		friend std::ostream& operator<< (std::ostream& cout, const intl& a);
		friend std::strong_ordering compare_abs(const intl& a, const intl& b);
		friend void add_abs(const intl& a, const intl& b, intl& c);
		friend void substract_abs(const intl& a, const intl& b, intl& c);

		intl() { sign = false; val = {0}; } // maybe it should be `val = {0};` here?
		intl(const std::string& s);

		void str_dec(const std::string& s);
		std::string str_dec() const; // maybe some & should be added here.
		void str_bin(const std::string& s);
		std::string str_bin() const;

		bool operator== (const intl& b) const;
		std::strong_ordering operator<=> (const intl& b) const;

		intl operator+ () const;
		intl operator- () const;
		intl operator+ (const intl& b) const;
		intl operator- (const intl& b) const;
	};

	std::istream& operator>> (std::istream& cin, intl& a) {
		std::string s;
		cin >> s;
		a.str_dec(s);
		return cin;
	}

	std::ostream& operator<< (std::ostream& cout, const intl& a) {
		std::vector<unsigned> digit = {0};

		for (auto u = a.val.rbegin(); u != a.val.rend(); u++) {
			bool carry = *u;
			for (unsigned& x : digit) {
				x <<= 1, x |= carry;
				if ((carry = (x >= 1e8))) x -= 1e8;
			} if (carry) digit.push_back(1);
		}

		if (a.sign && !a.is_zero()) cout << '-';
		cout << std::to_string(digit.back());
		for (auto u = next(digit.rbegin()); u != digit.rend(); u++) {
			std::string now = std::to_string(*u);
			cout << std::string(8 - now.size(), '0') << now;
		}

		return cout;
	}

	std::strong_ordering compare_abs(const intl& a, const intl& b) {
		if ((a.is_zero() && b.is_zero()) || a.val == b.val) return std::strong_ordering::equal;
		bool res = false; // res : is a greater than b?
		if (a.val.size() == b.val.size()) {
			for (auto u = a.val.rbegin(), v = b.val.rbegin(); u != a.val.rend(); u++, v++)
				if (*u != *v) { res = *u; break; }
		} else res = (a.val.size() > b.val.size());
		return res ? std::strong_ordering::greater : std::strong_ordering::less;
	}

	void add_abs(const intl& a, const intl& b, intl& c) {
		c.val.clear();
		auto u = a.val.begin(); bool carry = false;
		for (auto v = b.val.begin(); v != b.val.end(); u++, v++) {
			c.val.push_back(*u ^ *v ^ carry);
			carry = (*u && *v) || ((*u || *v) && carry);
		}
		for (; u != a.val.end(); u++) {
			c.val.push_back(*u ^ carry);
			carry = (*u && carry);
		}
		if (carry) c.val.push_back(1);
	}

	void substract_abs(const intl& a, const intl& b, intl& c) {
		c.val.clear();
		auto u = a.val.begin(); bool carry = false;
		for (auto v = b.val.begin(); v != b.val.end(); u++, v++) {
			c.val.push_back(*u ^ *v ^ carry);
			carry = (*u && *v && carry) || (!*u && (*v || carry));
		}
		for (; u != a.val.end(); u++) {
			c.val.push_back(*u ^ carry);
			carry = (!*u && carry);
		}
		while (c.val.size() > 1 && !c.val.back()) c.val.pop_back();
	}

	void calculate_abs(const intl& a, const intl& b, intl& c, char op) {
		switch (op) {
			case '+': add_abs(a, b, c); break;
			case '-': substract_abs(a, b, c); break;
		}
	}

	bool intl::is_zero() const {
		for (const bool& i : val) if (i) return false;
		return true;
	}

	void intl::str_dec(const std::string& s) {
		val.clear();
		std::vector<unsigned> digit;

		bool withsign = (s.front() == '+' || s.front() == '-');
		sign = withsign ? (s.front() == '-') : false;
		for (size_t i = withsign, j; i < s.size(); i = j) {
			j = s.size() - ((s.size() - i - 1) >> 3 << 3);
			digit.push_back(stoul(s.substr(i, j - i)));
		}

		for (auto front = digit.begin(); front != digit.end(); !*front ? ++front : decltype(front)()) {
			bool carry = 0;
			for (auto u = front; u != digit.end(); u++) {
				if (carry) *u += 1e8;
				carry = *u & 1, *u >>= 1;
			} val.push_back(carry);
		}
	}

	// don't forget to modify cout function!!
	std::string intl::str_dec() const {
		std::vector<unsigned> digit = {0};

		for (auto u = val.rbegin(); u != val.rend(); u++) {
			bool carry = *u;
			for (unsigned& x : digit) {
				x <<= 1, x |= carry;
				if ((carry = (x >= 1e8))) x -= 1e8;
			} if (carry) digit.push_back(1);
		}

		std::string res = (sign && !is_zero() ? '-' : char()) + std::to_string(digit.back());
		for (auto u = next(digit.rbegin()); u != digit.rend(); u++) {
			std::string now = std::to_string(*u);
			res += std::string(8 - now.size(), '0') + now;
		}
		return res;
	}

	void intl::str_bin(const std::string& s) {
		val.clear();
		for (auto u = s.rbegin(); u != s.rend(); u++) val.push_back(bool(*u ^ 48));
	}

	std::string intl::str_bin() const {
		std::string res;
		for (auto u = val.rbegin(); u != val.rend(); u++) res += std::to_string(*u);
		return res;
	}

	intl::intl(const std::string& s) {
		this->str_dec(s);
	}

	bool intl::operator== (const intl& b) const {
		return (is_zero() && b.is_zero()) || (sign == b.sign && val == b.val);
	}

	std::strong_ordering intl::operator<=> (const intl& b) const {
		if (operator==(b)) return std::strong_ordering::equal;
		if (sign && !b.sign) return std::strong_ordering::less;
		if (!sign && b.sign) return std::strong_ordering::greater;
		bool res = false; // res : is self greater than b?
		if (val.size() == b.val.size()) {
			for (auto u = val.rbegin(), v = b.val.rbegin(); u != val.rend(); u++, v++)
				if (*u != *v) { res = *u; break; }
		} else res = (val.size() > b.val.size());
		return sign ^ res ? std::strong_ordering::greater : std::strong_ordering::less;
	}

	intl intl::operator+ () const { return *this; }
	intl intl::operator- () const {
		intl c = *this;
		c.sign = !c.sign;
		return c;
	}
	
	intl intl::operator+ (const intl& b) const {
		intl c;

		std::strong_ordering cmp = compare_abs(*this, b);
		char op = (sign == b.sign ? '+' : '-');
		c.sign = cmp == std::strong_ordering::greater ?
		         (calculate_abs(*this, b, c, op), sign) : (calculate_abs(b, *this, c, op), b.sign);

		return c;
	}
	
	intl intl::operator- (const intl& b) const {
		intl c;
		
		std::strong_ordering cmp = compare_abs(*this, b);
		char op = (sign == !b.sign ? '+' : '-');
		c.sign = cmp == std::strong_ordering::greater ?
		(calculate_abs(*this, b, c, op), sign) : (calculate_abs(b, *this, c, op), !b.sign);
		
		return c;
	}

}

/*
causion:
1. positive / negative 0
2. extra previous 0
3. parameter order of function ???_abs()
*/

using namespace std;
using namespace std_intl;

int main() {
	intl a, b;
	cin >> a >> b;
	cout << a - b << "\n";
	return 0;
}
