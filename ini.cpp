#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using unit = unsigned int;
using ull = unsigned long long;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int INF = 1e9;
const ll LINF = 4e18;
const int MOD = 1e9 + 7;
const ld PI = acos((ld) - 1);

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<ll>()(((ll)p.first << 32) ^ p.second);
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        
    }
    return 0;
}


