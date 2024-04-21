#include <bits/stdc++.h>
#include <cmath>

using namespace std;

template<typename T>
struct Node {
    T val;
    Node* next;

    Node(const T& value, Node* ne) : val(value), next(nullptr) {
        val = value;
        next = ne;
    }
};

template<typename T>
class RegularStack {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int size = 0;

    public:
    void regularStack(Node<T>* h=nullptr) {
        head = h;
        tail = nullptr;
        size = 0;
    }
    void push(Node<T>* node) {
        if(head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        size++;
    }

    T pop() {
        if(size == 0) return -1;
        if(size == 1) {
            size--;
            int n = head->val;
            delete head;
            head = nullptr;
            tail = nullptr;
            return n;
        }
        int n = tail->val;
        Node<T>* cur = head;
        for(int i=1; i<size-1; ++i) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
        tail = cur;
        size--;
        return n;
    }

    T top() {
        return tail->val;
    }

    bool isEmpty() {
        return size > 0;
    }

    int stackSize() {
        return size;
    }

    void clear() {
        while(head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    void print() {
        Node<T>* cur = head;
        vector<T> arr;
        while(cur != nullptr) {
            arr.push_back(cur->val);
            cur = cur->next;
        }
        for(int i=size - 1; i>-1; --i) {
            cout << arr[i] << "\n";
        }
    }
};

int main() {
    RegularStack<int>* s = new RegularStack<int>();
    Node<int>* node = new Node<int>(1, nullptr);
    Node<int>* node2 = new Node<int>(2, nullptr);
    Node<int>* node3 = new Node<int>(3, nullptr);
    s->push(node);
    s->push(node2);
    s->push(node3);
    s->print();
    cout << s->pop() << "\n";
    s->clear();
    s->print();
    return 0;
}