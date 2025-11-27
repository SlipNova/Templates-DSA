#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>

typedef long double ld;
using namespace std;

void fileCheck(string fileName, vector <ld> &a) {
    ifstream infile(fileName); 
    if (!infile) {
        cerr << "Error opening input file." << endl;
        return;
    }
    int n;
    infile >> n; 
    for (int i = 0; i < n; i++) {
        ld t;
        infile >> t;
        a.push_back(t);
    }
    sort(a.begin(), a.end());
    infile.close(); 
}

ld percentile(const vector<ld> &data, ld k) {
    ld rank = (k / 100.0) * (data.size() + 1);
    int rankf = static_cast<int>(floor(rank));
    int rankc = static_cast<int>(ceil(rank));
    ld alpha = rank - rankf;
    ld res = data[rankf - 1] + alpha * (data[rankc - 1] - data[rankf - 1]);
    return res;
}
void tellMe(const vector <ld> &data) {
    int size = data.size();
    static ld MIN = data[0];
    static ld Quartile1 = percentile(data, 25); 
    static ld MEDIAN = percentile(data, 50);
    static ld Quartile3 = percentile(data, 75);
    static ld MAX = data[size - 1];
    static ld MEAN = 0;
    static ld VARIANCE = 0;
    for (int i = 0; i < size; i++) {
        MEAN += data[i];
    } 
    MEAN /= size;
    for (int i = 0; i < size; i++) {
        VARIANCE += (data[i] - MEAN) * (data[i] - MEAN);
    }
    VARIANCE /= size;
    static ld STANDARD_DEVIATION = sqrt(VARIANCE);
    cout << "MIN                : " << MIN << '\n';
    cout << "25th percentile    : " << Quartile1 << '\n';
    cout << "MEDIAN             : " << MEDIAN << '\n';
    cout << "75th percentile    : " << Quartile3 << '\n';
    cout << "MAX                : " << MAX << '\n'; 
    cout << "MEAN               : " << MEAN << '\n';
    cout << "VARIANCE           : " << VARIANCE << '\n';
    cout << "STANDARD DEVIATION : " << STANDARD_DEVIATION << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector <ld> data;
    string fileName;
    // cin >> fileName;
    fileName = "t1.txt";
    fileCheck(fileName, data);
    tellMe(data);
    return 0;
}