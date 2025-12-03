#include <bits/stdc++.h>

using namespace std;


template <typename T> 
struct edge {
    int from;
    int to;
    T cost;
};

template <typename T>
class graph {
public: 
    int n;
    vector<vector<int>> al;
    vector<edge<T>> edges;

    graph(int _n) : n(_n) {
        al.resize(_n);
    }
};

// iterative
bool dfs(graph<int> &g, int s, vector<bool> &visited, vector<bool> &instack) {
    visited[s] = true;
    instack[s] = true;
    for (int it: g.al[s]) {
        if (!visited[it] && dfs(g, it, visited, instack)) {
            return true;
        }
        else if (instack[it]) {
            return true;
        }
    }
    instack[s] = false;
    return false;
}
bool containsCycle (graph<int>& g) {
    int n = g.n;
    vector<bool> visited(n, false), instack(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(g, i, visited, instack)) {
            return true;
        }
    }
    return false;
}
// recursive
bool dfss(graph<int> &g, int node, vector<int> &state) {
    state[node] = 1;
    for (auto it: g.al[node]) {
        if (state[it] == 0) {
            if (dfss(g, it, state)) return true; 
        }
        else if (state[it] == 1) {
            return true;
        }
    }
    state[node] = 2;
    return false;
}

bool RcontainsCycle(graph<int> &g) {
    int n = g.n;
    vector<int> state(n, 0);
    for (int i = 0; i < n; i++) {
        if (state[i] == 0 && dfss(g, i, state)) {
            return true;
        }
    } 
    return false;
}

// iterative
vector<int> topSort(graph<int> &g) {
    int n = g.n;
    vector<int> order;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            stack<pair<int, bool>> st;
            st.push({i, false});
            while (!st.empty()) {
                auto [node, done] = st.top();
                st.pop();
                
                if (done) {
                    order.push_back(node);
                    continue;
                }

                if (!visited[node]) {
                    visited[node] = true;
                    st.push({node, true});
                    for (int neigh: g.al[node]) {
                        if (!visited[neigh]) {
                            st.push({neigh, false});
                        }
                    }
                }
            }
        }
    }

    reverse(order.begin(), order.end());
    return order;
}

// dfs with cycle
bool dfsC(graph<int> &g, int node, vector<int> &state, vector<int> &order) {
    state[node] = 1; 
    for (auto it : g.al[node]) {
        if (state[it] == 0) {
            if (dfsC(g, it, state, order)) return true; 
        } else if (state[it] == 1) {
            return true; 
        }
    }
    state[node] = 2;
    order.push_back(node);
    return false;
}

vector<int> topSortCycle(graph<int> &g) {
    vector<int> order;
    vector<int> state(g.n, 0);
    for (int i = 0; i < g.n; i++) {
        if (state[i] == 0) {
            if (dfsC(g, i, state, order)) return {}; 
        }
    }
    reverse(order.begin(), order.end());
    return order;
}
