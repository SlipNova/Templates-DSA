#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Heap {
    vector<int> data;
    bool isMaxHeap;

    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parentIndex = (index - 1) / 2;
            if ((isMaxHeap && data[index] <= data[parentIndex]) ||
                (!isMaxHeap && data[index] >= data[parentIndex])) {
                break;
            }
            swap(data[index], data[parentIndex]);
            index = parentIndex;
        }
    }

    void heapifyDown(size_t index) {
        size_t size = data.size();
        while (index < size) {
            size_t leftChild = 2 * index + 1;
            size_t rightChild = 2 * index + 2;
            size_t target = index;

            if (leftChild < size && (isMaxHeap ? data[leftChild] > data[target] : data[leftChild] < data[target])) {
                target = leftChild;
            }
            if (rightChild < size && (isMaxHeap ? data[rightChild] > data[target] : data[rightChild] < data[target])) {
                target = rightChild;
            }
            if (target == index) {
                break;
            }
            swap(data[index], data[target]);
            index = target;
        }
    }

    void buildHeap() {
        // Build heap in O(n) time complexity
        for (int i = (data.size() / 2) - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

public:
    Heap(bool maxHeap) : isMaxHeap(maxHeap) {}

    void insert(int value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    int pop() {
        if (data.empty()) {
            throw runtime_error("Heap is empty");
        }

        int top = data[0];
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
        return top;
    }

    int top() const {
        if (data.empty()) {
            throw runtime_error("Heap is empty");
        }
        return data[0];
    }

    void buildFromArray(const vector<int>& elements) {
        data = elements;
        buildHeap();
    }

    bool empty() {
        return data.empty();
    }
};

int main() {
    Heap heap(false);
    vector <int> a = {0, -1,2 ,3 ,412, -23213};
    vector <int> b(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector <int> c;
    Heap h(false);
    h.buildFromArray(a);
    while (!h.empty()) {
        c.push_back(h.top());
        h.pop();
    }
    for (auto it: c) {
        cout << it << ' ';
    }
    return 0;
}
