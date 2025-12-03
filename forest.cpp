#include <bits/stdc++.h>

using namespace std;

template<typename T>
class graph {
    public:
    struct edge {
        int from;
        int to;
        T cost;
    };
    vector<edge> edges;
    vector<vector<int>> al;
    int n;

    graph(int num) : n(num) {
        al.resize(n);
    }

    virtual int add(int from, int to, T cost) = 0;
};

// using Base::member; 
// inside a derived class, it brings the member from the base class into the scope of the derived class
// After this, you can access the member directly, without this-> or specifying the base class.
// It does not create a new member; it just makes the base member visible.

template<typename T>
class forest : public graph<T> {
    public:
    using graph<T>::edges;
    using graph<T>::al;
    using graph<T>::n;

    forest(int num) : graph<T>(num) {}
    
    int add(int from, int to, T cost = 1) override {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        assert(id < n - 1);
        al[from].push_back(id);
        al[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};

template<typename T> 
class dfs_forest : public forest<T> {
    public:
    using forest<T>::edges;
    using forest<T>::al;
    using forest<T>::n;

    vector<int> pv;    // parent of each node
    vector<int> pe;    // edge id connected to parent
    vector<int> order; // dfs order of nodes
    vector<int> pos;   // pos of node in dfs order
    vector<int> end;   // last position of subforest in dfs order
    vector<int> sz;    // size of subforest
    vector<int> root;  // root of connected component
    vector<int> depth; // depth of nodes
    vector<T> dist;    // distance from dfs root basically total cost of dfs from root

    dfs_forest(int num) : forest<T>(num) {}

    void init() {
        pv = vector<int>(n, -1);
        pe = vector<int>(n, -1);
        order.clear();
        pos = vector<int>(n, -1);
        end = vector<int>(n, -1);
        sz = vector<int>(n, 0);
        root = vector<int>(n, -1);
        depth = vector<int>(n, -1);
        dist = vector<T>(n);
    }

    private:

    void do_dfs(int v) {
        pos[v] = order.size();
        order.push_back(v);
        sz[v] = 1;
        for (int id: al[v]) {
            if (id == pe[v]) continue;
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            depth[to] = depth[v] + 1;
            dist[to] = dist[v] + e.cost;
            pv[to] = v;
            pe[to] = id;
            root[to] = (root[v] != -1 ? root[v] : to);
            do_dfs(to);
            sz[v] += sz[to];
        }
        end[v] = order.size() - 1;
    }

    void do_dfs_from(int v) {
        depth[v] = 0;
        dist[v] = T{};
        root[v] = v;
        pv[v] = pe[v] = -1;
        do_dfs(v);
    }

    public:

    void dfs(int v, bool clear_order = true) {
        if (pv.empty()) init();
        else if (clear_order) order.clear();
        do_dfs_from(v);
    }

    void dfs_all() {
        init();
        for (int v = 0; v < n; v++) {
            if (depth[v] == -1) do_dfs_from(v);
        }
        assert((int) order.size() == n);
    }

};

int main() {

    dfs_forest<int> f(5);

    // Add edges (undirected)
    f.add(0, 1, 5); // edge 0
    f.add(0, 2, 3); // edge 1
    f.add(1, 3, 2); // edge 2
    f.add(1, 4, 1); // edge 3

    // Run DFS from node 0
    f.dfs(0);

    // Print DFS results
    cout << "Node : Parent | Parent Edge | Depth | Subtree Size | Distance from root\n";
    for (int i = 0; i < 5; i++) {
        cout << i << " : "
             << f.pv[i] << " | "
             << f.pe[i] << " | "
             << f.depth[i] << " | "
             << f.sz[i] << " | "
             << f.dist[i] << "\n";
    }

    // Print DFS order
    cout << "\nDFS order of nodes: ";
    for (int v : f.order) cout << v << " ";
    cout << "\n";

    // Print adjacency lists with edge IDs
    cout << "\nAdjacency lists (edge IDs):\n";
    for (int v = 0; v < 5; v++) {
        cout << v << ": ";
        for (int id : f.al[v]) cout << id << " ";
        cout << "\n";
    }

    return 0;
}