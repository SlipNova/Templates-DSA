#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long double ld;
using namespace std;

const string DISTRIBUTION = "exponential";
const string FILE_NAME = "t1.txt";

class PDF {
private:
    vector<ld> data;
    ld MIN;
    ld Quartile1;
    ld MEDIAN;
    ld Quartile3;
    ld MAX;
    ld MEAN;
    ld VARIANCE;
    ld STANDARD_DEVIATION;

    ld pd(ld x) {
        if (DISTRIBUTION == "uniform") {
            return (ld) 1 / data.size();
        }
        else if (DISTRIBUTION == "exponential") {
            ld lambda = 1.0 / 1.154;
            if (x < 0) {
                return 0;
            }
            else {
                return lambda * exp(-lambda * x);
            }
        }
        return 1;
    }

    ld percentile(const vector<ld> &data, ld k) {
        ld rank = (k / 100.0) * (data.size() + 1);
        size_t rankf = static_cast<size_t>(floor(rank));
        size_t rankc = static_cast<size_t>(ceil(rank));
        ld alpha = rank - rankf;
        ld res = data[rankf - 1] + alpha * (data[rankc - 1] - data[rankf - 1]);
        return res;
    }

    void fileCheck(const string &fileName) {
        ifstream infile(fileName);
        if (!infile.is_open()) {
            cerr << "Error opening input file." << endl;
            return;
        }
        int n;
        infile >> n;
        for (int i = 0; i < n; i++) {
            ld t;
            infile >> t;
            data.push_back(t);
        }
        infile.close();
        sort(data.begin(), data.end());
        size_t size = data.size();
        MIN = data.front();
        Quartile1 = percentile(data, 25);
        MEDIAN = percentile(data, 50);
        Quartile3 = percentile(data, 75);
        MAX = data.back();
        MEAN = 0;
        for (size_t i = 0; i < size; i++) {
            MEAN += data[i] * pd(data[i]);
        }
        VARIANCE = 0;
        for (size_t i = 0; i < size; i++) {
            VARIANCE += (data[i] - MEAN) * (data[i] - MEAN) * pd(data[i]);
        }
        STANDARD_DEVIATION = sqrt(VARIANCE);
    }

public:
    PDF() {
        fileCheck(FILE_NAME);
    }

    PDF(const string &file_Name) {
        fileCheck(file_Name);
    }

    void getStuff() const {
        cout << "MIN                : " << MIN << '\n';
        cout << "25th percentile    : " << Quartile1 << '\n';
        cout << "MEDIAN             : " << MEDIAN << '\n';
        cout << "75th percentile    : " << Quartile3 << '\n';
        cout << "MAX                : " << MAX << '\n';
        cout << "MEAN               : " << MEAN << '\n';
        cout << "VARIANCE           : " << VARIANCE << '\n';
        cout << "STANDARD DEVIATION : " << STANDARD_DEVIATION << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    PDF data = PDF();
    data.getStuff();

    return 0;
}
