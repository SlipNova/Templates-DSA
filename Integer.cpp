#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Integer {
    vector<int> digits;
    bool negative;

public:
    Integer() : negative(false) {}

    Integer(string num) {
        negative = (num[0] == '-');
        int left = (negative ? 1 : 0);
        for (int i = num.size() - 1; i >= left; i--) {
            digits.push_back(num[i] - '0');
        }
    }
    Integer operator+(const Integer& num) const {
        if (this->negative != num.negative) {
            if (this->negative) {
                return num - (*this);
            } 
            else {
                return (*this) - num;
            }
        }
        Integer result;
        int carry = 0;
        int maxSize = max(digits.size(), num.digits.size());
        for (int i = 0; i < maxSize; i++) {
            int digit1 = (i < num.digits.size() ? num.digits[i] : 0);
            int digit2 = (i < digits.size() ? digits[i] : 0);
            int sum = digit1 + digit2 + carry;
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry != 0) {
            result.digits.push_back(carry);
        }
        result.negative = this->negative;
        return result;
    }

    Integer operator-(const Integer& other) const { // complete this
        if (this->negative != other.negative) {
            if (this->negative) {
                Integer temp = other;
                temp.negative = true;
                return (*this) + temp;
            }
            else {
                return (*this) + other;
            }
        }

    }


    Integer operator*(const Integer& num) const {
        Integer result;
        result.digits.resize(digits.size() + num.digits.size(), 0);

        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < num.digits.size() || carry; j++) {
                int mul =
                    result.digits[i + j] +
                    digits[i] * (j < num.digits.size() ? num.digits[j] : 0) +
                    carry;
                result.digits[i + j] = mul % 10;
                carry = mul / 10;
            }
        }
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }
        result.negative = (negative != num.negative);
        return result;
    }

    void operator+=(const Integer& other) { *this = *this + other; }

    bool operator==(const Integer& other) const {
        if (negative != other.negative) {
            return false;
        }
        if (digits.size() != other.digits.size()) {
            return false;
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator>=(const Integer& other) const {
        if (negative && !other.negative) {
            return false;
        } else if (!negative && other.negative) {
            return true;
        }
        if (digits.size() > other.digits.size()) {
            return !negative;
        } else if (digits.size() < other.digits.size()) {
            return negative;
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] > other.digits[i]) {
                return !negative;
            } else if (digits[i] < other.digits[i]) {
                return negative;
            }
        }
        return true;
    }

    bool operator<=(const Integer& other) const { return !(*this > other); }

    bool operator>(const Integer& other) const {
        if (negative && !other.negative) {
            return false;
        } else if (!negative && other.negative) {
            return true;
        }
        if (digits.size() > other.digits.size()) {
            return !negative;
        } else if (digits.size() < other.digits.size()) {
            return negative;
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] > other.digits[i]) {
                return !negative;
            } else if (digits[i] < other.digits[i]) {
                return negative;
            }
        }
        return false;
    }

    bool operator<(const Integer& other) const { return other > *this; }

    void operator++() { *this += Integer("1"); }
    
    void operator--() { *this += Integer("-1"); }

    friend ostream& operator<<(ostream& os, const Integer& num) {
        if (num.negative)
            os << '-';
        for (int i = num.digits.size() - 1; i >= 0; i--) {
            os << num.digits[i];
        }
        return os;
    }
};

Integer Factorial(int n) {
    Integer a("1");
    for (int i = 2; i < n + 1; i++) {
        string str = to_string(i);
        Integer b(str);
        a = a * b;
    }
    return a;
}

void fibo(int n) {
    Integer a("0");
    Integer b("1");
    cout << "0: " << a << '\n';
    cout << "1: " << b << '\n';
    for (int i = 2; i < n + 1; i++) {
        Integer c = a + b;
        cout << i << ": " << c << '\n';
        a = b;
        b = c;
    }
}

void fib(int n) {
    Integer a("0");
    Integer b("1");
    Integer c;
    for (int i = 2; i < n + 1; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    cout << n << ": " << c << '\n';
}
