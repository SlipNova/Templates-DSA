#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

using ll = long long;
using ld = long double;

const int MOD = 1e9+7;
const ld PI = acos((ld)-1);

template<class T> bool ckmin(T &a, const T &b) {return b < a ? a = b, 1 : 0;}
template<class T> bool ckmax(T &a, const T &b) {return a < b ? a = b, 1 : 0;}

string add(const string &str, char c, int pos) {
    return str.substr(0, pos) + c + str.substr(pos);
}

vector<string> perms(string str) {
    if (str.length() == 0) return {};
    else if (str.length() == 1) {
        return {str};
    }
    else {
        char first = str[0];
        string rest = str.substr(1);
        vector<string> newperms;
        newperms = perms(rest);
        vector<string> res;
        for (int i = 0; i < newperms.size(); i++) {
            for (int j = 0; j <= newperms[i].size(); j++) {
                res.push_back(add(newperms[i], first, j));
            }
        }
        return res;
    }
}

void permutations(string &str, int l, int r) {
    if (l == r) {
        cout << str << ' ';
        return;
    }
    else {
        for (int i = l; i <= r; i++) {
            swap(str[l], str[i]);
            permutations(str, l + 1, r);
            swap(str[l], str[i]);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a;
    cin >> a;
    int k = 0;
    vector<string> perm;
    perm = perms(a);
    for (auto it: perm) {
        cout << it << ' ';
    }
    cout << '\n';
    permutations(a, 0, a.size() - 1);
    cout << '\n';
    return 0;
}