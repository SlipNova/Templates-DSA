#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long double ld;
const ld PI = 3.141592653589793;
const string str = "leftSum";
const int numberOfRect = 1e9;

using namespace std;


ld F(ld x) {
    return sin(x);
}

ld partitionLen (vector <ld> &lista) {
    return lista[1] - lista[0];
}

ld midpiontRule(vector <ld> &lista) {
    return lista[0] + (lista[1] - lista[0]) / 2;
}

vector <vector <ld>> createPartition(vector <ld> &lista, int n) {
    vector <vector <ld>> partition;
    ld h = (lista[1] - lista[0] ) / n;
    for (int i = 0; i < n; i++) {
        vector <ld> arr;
        arr.push_back(lista[0] + i * h);
        arr.push_back(lista[0] + (i - 1) * h);
        partition.push_back(arr);
    }
    return partition;
}

ld integralFxReimannSum(vector <ld> &lista, int n, string stri) {
    ld k = 0;
    if (stri == "rightSum") {
        k = 1;
    }
    vector <vector <ld>> partition = createPartition(lista, n);
    ld sol = 0;
    for (int i = 0; i < partition.size(); i++) {
        sol += partitionLen(partition[i]) * F(midpiontRule(partition[i]));
    }
    return sol;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector <ld> interval;
    cin >> interval[0] >> interval[1];
    ld sol = integralFxReimannSum(interval, numberOfRect, str);
    return 0;
}