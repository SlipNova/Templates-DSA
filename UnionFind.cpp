
template <typename T> 
class UnionFind {
    unordered_map<T, T> parent;
    unordered_map<T, int> rank;

public:
    UnionFind() {}

    void add(const T& _ele) {
        if (parent.find(_ele) == parent.end()) {
            parent[_ele] = _ele;
            rank[_ele] = 1;
        }
    }

    T find(const T& _ele) {
        if (parent[_ele] != _ele) {
            parent[_ele] = find(parent[_ele]);
        }
        return parent[_ele];
    }

    void unite(const T& P, const T& Q) {
        T rootP = find(P);
        T rootQ = find(Q);
        if (rootP != rootQ) {
            if (rank[rootP] > rank[rootQ]) {
                parent[rootQ] = rootP;
            } else if (rank[rootP] < rank[rootQ]) {
                parent[rootQ] = rootP;
            } else {
                parent[rootQ] = rootP;
                rank[rootP] += 1;
            }
        }
    }
};

