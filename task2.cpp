#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;   // min-heap on node value
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

    for (ListNode* head : lists)
        if (head) pq.push(head);

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!pq.empty()) {
        ListNode* node = pq.top(); pq.pop();
        tail->next = node;
        tail = node;
        if (node->next) pq.push(node->next);
    }

    return dummy.next;
}

int main() {
    // lists: [1,4,5], [1,3,4], [2,6]
    vector<vector<int>> data = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
    vector<ListNode*> lists;

    for (auto& v : data) {
        ListNode dummy(0);
        ListNode* t = &dummy;
        for (int x : v) {
            t->next = new ListNode(x);
            t = t->next;
        }
        lists.push_back(dummy.next);
    }

    ListNode* res = mergeKLists(lists);
    while (res) {
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;
    return 0;
}