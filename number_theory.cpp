#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

int main() {
    vector<bool> primes = sieve(100);
    vector<int> spf = SPF(100);
    vector<int> factors = factorize(100, spf);
    vector<int> uf = uniqueFactors(100, spf);
    for (auto it : uf) {
        cout << it << ' ';
    }
    
}