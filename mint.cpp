#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ull = unsigned long long;
using ll = long long;

const uint MOD = 1000000007;

template<uint mod = MOD>
struct Mint {
    uint x;

    Mint() : x(0) {};

    Mint(ll _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }

    Mint& operator+=(const Mint& a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    Mint& operator-= (const Mint& a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    Mint& operator*= (const Mint& a) {
        x = (ull)x * a.x % mod;
        return *this;
    }

    Mint operator+ (const Mint& a) const {
        return Mint(*this) += a;
    }

    Mint operator- (const Mint& a) const {
        return Mint(*this) -= a;
    }

    Mint operator* (const Mint& a) const {
        return Mint(*this) *= a;
    }

    Mint pow(ll pw) const {
        Mint ans = 1;
        Mint curr = *this;
        while (pw) {
            if (pw & 1) ans *= curr;
            curr *= curr;
            pw >>= 1;
        }
        return ans;
    }

    Mint inv() const {
        assert(x != 0 && gcd(x, mod) == 1);
        uint t = x;
        uint ans = 1;
        while (t != 1) {
            uint q = mod / t;
            ans = ull(ans) * (mod - q) % mod; 
            t = mod % t;
        }
        return Mint(ans);
    }

    Mint& operator/= (const Mint& a) {
        return *this *= a.inv();
    }

    Mint operator/ (const Mint& a) const {
        return Mint(*this) /= a;
    }

    bool operator== (const Mint& a) const {
        return x == a.x;
    }

    bool operator!= (const Mint& a) const {
        return x != a.x;
    }

    bool operator<= (const Mint& a) const {
        return x <= a.x;
    }

    bool operator< (const Mint& a) const {
        return x < a.x;
    }

    bool operator>= (const Mint& a) const {
        return x >= a.x;
    }

    bool operator> (const Mint& a) const {
        return x > a.x;
    }

    bool sqrt(Mint& a) const {
        return true;
    }
};

template<uint mod = MOD>
struct Factorials {
    using M = Mint<mod>;
    vector<M> fact, ifact;
    Factorials () {};
    Factorials (int n) {
        init(n);
    }
    void init(int n) {
        fact.assign(n + 1, 1);
        ifact.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        ifact[n] = fact[n].inv();
        for (int i = n - 1; i > 1; i--) {
            ifact[i] = ifact[i + 1] * (i + 1);
        }
    }

    M factorial(int n) {
        return fact[n];
    }

    M invFactorial(int n) {
        return ifact[n];
    }

    M C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * ifact[r] * ifact[n - r];
    }

    M P(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * ifact[n - r];
    }
};