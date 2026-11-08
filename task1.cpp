#include <bits/stdc++.h>
using namespace std;

struct Node {
    int freq;
    Node *left, *right;
    Node(int f) : freq(f), left(NULL), right(NULL) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void preorder(Node* root, string code, vector<string>& ans) {
    if (!root) return;
    if (!root->left && !root->right) {
        ans.push_back(code);
        return;
    }
    preorder(root->left, code + "0", ans);
    preorder(root->right, code + "1", ans);
}

vector<string> huffmanCodes(string S, vector<int> f, int N) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < N; i++)
        pq.push(new Node(f[i]));

    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* parent = new Node(l->freq + r->freq);
        parent->left = l;
        parent->right = r;
        pq.push(parent);
    }

    vector<string> ans;
    preorder(pq.top(), "", ans);
    return ans;
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    int N = S.size();

    vector<string> codes = huffmanCodes(S, f, N);
    for (string c : codes)
        cout << c << " ";
    cout << endl;
    return 0;
}