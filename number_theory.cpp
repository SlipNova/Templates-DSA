#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;

u64 mod_pow(u64 a, u64 e, u64 mod) {
    u64 res = 1;
    while (e) {
        if (e & 1) res = (u128)res * a % mod;
        a = (u128)a * a % mod;
        e >>= 1;
    }
    return res;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<bool> sieve(int n) {
    vector<bool> a(n + 1, true);
    a[0] = false;
    a[1] = false;
    for (long long i = 2; 1ll * i * i <= n; i++) {
        if (!a[i]) continue;
        for (long long j = i * i; j <= n; j += i) {
            a[j] = false;
        }
    }
    return a;
}

vector<int> SPF(int n) {
    vector<int> a(n + 1);
    for (int i = 0; i <= n; i++) {
        a[i] = i;
    }
    for (long long i = 2; 1ll * i * i <= n; i++) {
        if (a[i] != i) continue;
        for (long long j = i * i; j <= n; j += i) {
            if (a[j] == j) a[j] = i;
        }
    }
    return a;
}

vector<int> factorize(int x, const vector<int>& spf) {
    assert(x >= 1 && x < spf.size());
    vector<int> factors;
    while (x != 1) {
        int f = spf[x];
        factors.push_back(f);
        x /= f;
    }
    return factors;
}

vector<int> uniqueFactors(int x, const vector<int>& spf) {
    assert(x >= 1 && x < spf.size());
    vector<int> uf;
    while (x != 1) {
        int f = spf[x];
        uf.push_back(f);
        while (x % f == 0) {
            x /= f;
        }
    }
    return uf;
}

vector<int> divisors(int x, const vector<int>& spf) {
    assert(x >= 1 && x < spf.size());
    vector<int> d;
    for (int i = 1; 1ll * i * i <= x; i++) {
        if (x % i == 0) {
            d.push_back(i);
            if (i != x / i) d.push_back(x / i);
        }
    }
    return d;
}

int phi(int x, const vector<int>& spf) {
    assert(x >= 1 && x < spf.size());
    int res = x;
    while (x != 1) {
        int f = spf[x];
        res -= res / f;
        while (x % f == 0) x /= f;
    }
    return res;
}

ll extGcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// x = a mod m
// x = b mod n
// make sure that lcm fits in ll before using
ll crt(ll a, ll m, ll b, ll n) {
    ll x, y, g;
    g = extGcd(m, n, x, y);
    if ((b - a) % g != 0) return -1;
    ll mod = n / g;
    ll lcm = (__int128)(m / g) * n;
    ll q = (b - a) / g;
    ll k = (__int128) (q % mod) * (x % mod) % mod;
    if (k < 0) k += mod;
    ll x0 = ((__int128)m * k + a) % lcm;
    if (x0 < 0) x0 += lcm;
    return x0;
}

// x = bi mod mi
pair<ll, ll> crtSystem(const vector<ll>& b, const vector<ll>& m) {
    assert(b.size() == m.size() && !b.empty());
    ll ans = b[0];
    ll lcm = m[0];
    for (int i = 1; i < b.size(); i++) {
        ans = crt(ans, lcm, b[i], m[i]);
        if (ans == -1) {
            return {-1, -1};
        }
        ll g = gcd(lcm, m[i]);
        lcm = (__int128)(lcm / g) * m[i];
    }
    return {ans, lcm};
}

bool witness(u64 a, u64 n) {
    u64 d = n - 1;
    int u = 0;
    while ((d & 1) == 0) { // breaking n - 1 = 2^s * d
        d >>= 1;
        u++;
    }
    u64 x = mod_pow(a, d, n);
    if (x == 1 || x == n - 1) return false; // if we start at 1, -1 then a cannot be witness
    for (int i = 1; i < u; i++) {
        x = (u128)x * x % n;
        if (x == n - 1) return false; // x0 != 1 or -1, now if we hit -1 then next must be 1 so a cannot be a witness cause rest of the sequence is juts 1
        if (x == 1) return true; // if we hit 1 means we didn't hit -1 before so n is composite, there are non trivial solutions to x^2 = 1, as we hit 1 before hitting -1 previously, so a is a witness
    }
    return true;
}

bool isPrimeMR(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    for (u64 a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (witness(a, n)) return false;
    }
    return true;
}

bool MRprime(u64 n, int rounds = 20) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if ((n & 1) == 0) return false;
    static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<u64> dist(2, n - 2);
    for (int i = 0; i < rounds; i++) {
        u64 a = dist(rng);
        if (witness(a, n)) return false;
    }
    return true; // prime i guess P(error) <= 1/2^(rounds)
}// atleast 3/4 of bases fail better than 50%
