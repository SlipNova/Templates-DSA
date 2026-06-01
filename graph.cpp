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

// kahn bfs
vector<int> kahn(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> indegree(n, 0), order;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            indegree[adj[i][j]]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        order.push_back(front);
        for (auto neigh : adj[front]) {
            indegree[neigh]--;
            if (indegree[neigh] == 0) {
                q.push(neigh);
            }
        }
    }
    if (order.size() != n) order = {};
    return order;
}

