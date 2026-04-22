#include <bits/stdc++.h>
using namespace std;

namespace LIST {
    struct NODE {
        int val;
        NODE* next;
    };

    NODE* head = nullptr; // points to first node if exists
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }

    // Move to node at index i (0-based). Assumes 0 <= i < len.
    NODE* move(int i) {
        if (len == 0) return nullptr;
        NODE* cur = head;
        for (int k = 0; k < i; ++k) cur = cur->next;
        return cur;
    }

    void insert(int i, int x) {
        NODE* node = new NODE{ x, nullptr };
        if (len == 0) {
            // inserting at position 0 into empty list
            node->next = node; // circular to itself
            head = node;
        } else if (i == 0) {
            // insert before head; need tail to fix circular link
            NODE* tail = move(len - 1);
            node->next = head;
            tail->next = node;
            head = node;
        } else {
            // insert between prev(i-1) and i
            NODE* prev = move(i - 1);
            node->next = prev->next;
            prev->next = node;
        }
        ++len;
    }

    void remove(int i) {
        if (len == 0) return; // as per statement, operations valid, but guard anyway
        if (len == 1) {
            // remove the only node
            delete head;
            head = nullptr;
            len = 0;
            return;
        }
        if (i == 0) {
            // remove head: need tail to bypass head
            NODE* tail = move(len - 1);
            NODE* old = head;
            head = head->next;
            tail->next = head;
            delete old;
        } else {
            NODE* prev = move(i - 1);
            NODE* target = prev->next;
            prev->next = target->next;
            delete target;
        }
        --len;
    }

    void remove_insert(int i) {
        // remove position i and append it to the tail
        if (len <= 1 || i == len - 1) return;

        NODE* tail = move(len - 1);
        if (i == 0) {
            NODE* old_head = head;
            head = head->next;        // new head
            tail->next = head;        // bypass old head
            old_head->next = head;    // will become tail
            tail->next = old_head;    // append at tail
        } else {
            NODE* prev = move(i - 1);
            NODE* target = prev->next;
            prev->next = target->next; // detach target
            target->next = head;        // append to tail
            tail->next = target;
        }
        // length unchanged
    }

    void get_length() {
        cout << len << '\n';
    }

    void query(int i) {
        if (i < 0 || i >= len) {
            cout << -1 << '\n';
            return;
        }
        NODE* p = move(i);
        cout << p->val << '\n';
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << '\n';
            return;
        }
        int mx = INT_MIN;
        NODE* p = head;
        for (int k = 0; k < len; ++k) {
            mx = max(mx, p->val);
            p = p->next;
        }
        cout << mx << '\n';
    }

    void clear() {
        while (len > 0) {
            remove(0);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
