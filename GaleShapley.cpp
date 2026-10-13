#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> GS(vector<vector<int>> M, vector<vector<int>> W) {
    int n = M.size();
    queue<int> fm;
    vector<int> wm (n, -1);
    vector<int> np(n, 0);
    vector<vector<int>> rank(n, vector<int> (n));
    for (int w = 0; w < n; w++) {
        for (int j = 0; j < n; j++) {
            rank[w][W[w][j]] = j + 1;
        }
    }
    for (int m = 0; m < n; m++) {
        fm.push(m);
    }
    while (!fm.empty()) {
        int cm = fm.front();
        int cw = M[cm][np[cm]++];
        if (wm[cw] == -1) {
            wm[cw] = cm;
        }
        else {
            if (rank[cw][cm] < rank[cw][wm[cw]]) {
                fm.push(wm[cw]);
                wm[cw] = cm;
            }
            else {
                fm.push(cm);
            }
        }
        fm.pop();
    }
    return wm;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> M(n, vector<int>(n)), W(n, vector<int>(n));
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (k == 0) {
                    cin >> M[i][j];
                }
                else {
                    cin >> W[i][j];
                }
            }
        }
    }
    vector<int> wm = GS(M, W);
    for (int i = 0; i < n; i++) {
        cout << wm[i] << (i != n - 1 ? ' ' : '\n');
    }
    return 0;
}