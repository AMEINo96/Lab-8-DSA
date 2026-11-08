#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, h;
    Node *l, *r;
    Node(int k) : key(k), h(1), l(NULL), r(NULL) {}
};

int H(Node* n) { return n ? n->h : 0; }
void upd(Node* n) { n->h = 1 + max(H(n->l), H(n->r)); }
int bal(Node* n) { return H(n->l) - H(n->r); }

Node* rotR(Node* y) {
    Node* x = y->l;
    y->l = x->r;
    x->r = y;
    upd(y); upd(x);
    return x;
}

Node* rotL(Node* x) {
    Node* y = x->r;
    x->r = y->l;
    y->l = x;
    upd(x); upd(y);
    return y;
}

// rebalances node n only if |balance| > 1
Node* rebalance(Node* n) {
    upd(n);
    int b = bal(n);
    if (b > 1) {
        if (bal(n->l) < 0) { cout << "  [LR rotation at " << n->key << "]\n"; n->l = rotL(n->l); }
        else cout << "  [LL rotation at " << n->key << "]\n";
        return rotR(n);
    }
    if (b < -1) {
        if (bal(n->r) > 0) { cout << "  [RL rotation at " << n->key << "]\n"; n->r = rotR(n->r); }
        else cout << "  [RR rotation at " << n->key << "]\n";
        return rotL(n);
    }
    return n;
}

Node* insert(Node* n, int k) {
    if (!n) return new Node(k);
    if (k < n->key) n->l = insert(n->l, k);
    else n->r = insert(n->r, k);
    return rebalance(n);
}

Node* remove(Node* n, int k) {
    if (!n) return NULL;
    if (k < n->key) n->l = remove(n->l, k);
    else if (k > n->key) n->r = remove(n->r, k);
    else {
        if (!n->l || !n->r) {
            Node* c = n->l ? n->l : n->r;
            delete n;
            return c;
        }
        Node* s = n->r;
        while (s->l) s = s->l;          // inorder successor
        n->key = s->key;
        n->r = remove(n->r, s->key);
    }
    return rebalance(n);
}

// criterion: 'M' = max, 'm' = min, 'S' = sum
// max and sum use the k largest elements, min uses the k smallest
void collect(Node* n, bool largest, int k, vector<int>& res) {
    if (!n || (int)res.size() >= k) return;
    collect(largest ? n->r : n->l, largest, k, res);
    if ((int)res.size() < k) res.push_back(n->key);
    collect(largest ? n->l : n->r, largest, k, res);
}

vector<int> topK(Node* root, char crit, int k) {
    vector<int> res;
    collect(root, crit != 'm', k, res);
    return res;
}

void show(Node* n, int d) {
    if (!n) return;a
    show(n->r, d + 1);
    cout << string(d * 4, ' ') << n->key << "\n";
    show(n->l, d + 1);
}

Node* insertAll(Node* root, vector<int> a) {
    for (int x : a) {
        cout << "Insert " << x << ":\n";
        root = insert(root, x);
        show(root, 0);
        cout << "-----\n";
    }
    return root;
}

void query(Node* root, char crit, int k) {
    vector<int> res = topK(root, crit, k);
    cout << "Top " << k << " (" << (crit == 'M' ? "max" : crit == 'm' ? "min" : "sum") << "): ";
    for (int x : res) cout << x << " ";
    if (crit == 'S') cout << "| sum = " << accumulate(res.begin(), res.end(), 0);
    cout << "\n";
}

Node* deleteTopK(Node* root, char crit, int k) {
    vector<int> res = topK(root, crit, k);
    for (int x : res) {
        cout << "Delete " << x << ":\n";
        root = remove(root, x);
        show(root, 0);
        cout << "-----\n";
    }
    return root;
}

int main() {
    Node* root = NULL;

    root = insertAll(root, {10, 20, 30, 40, 50, 25, 5});

    query(root, 'M', 3);
    query(root, 'm', 3);
    query(root, 'S', 3);

    root = deleteTopK(root, 'M', 2);
    return 0;
}