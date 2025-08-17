#include <vector>
using namespace std;

class BookMyShow {
    struct Node {
        int l, r;
        long long maxFree, sumFree;
        Node *left, *right;
        Node(int l, int r, int m) : l(l), r(r), maxFree(m), sumFree(1LL * (r - l + 1) * m), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int m;

    void build(Node*& node, int l, int r) {
        node = new Node(l, r, m);
        if (l == r) return;
        int mid = (l + r) / 2;
        build(node->left, l, mid);
        build(node->right, mid + 1, r);
    }

    // For gather: find leftmost row <= maxRow with maxFree >= k
    bool gather(Node* node, int k, int maxRow, int& row, int& seat) {
        if (node->l > maxRow || node->maxFree < k) return false;
        if (node->l == node->r) {
            row = node->l;
            seat = m - node->maxFree;
            node->maxFree -= k;
            node->sumFree -= k;
            return true;
        }
        bool found = gather(node->left, k, maxRow, row, seat);
        if (!found) found = gather(node->right, k, maxRow, row, seat);
        node->maxFree = max(node->left->maxFree, node->right->maxFree);
        node->sumFree = node->left->sumFree + node->right->sumFree;
        return found;
    }

    // For scatter: allocate k seats in rows <= maxRow
    long long scatter(Node* node, long long k, int maxRow) {
        if (node->l > maxRow || k == 0 || node->sumFree == 0) return k;
        if (node->l == node->r) {
            long long take = min(k, node->maxFree);
            node->maxFree -= take;
            node->sumFree -= take;
            return k - take;
        }
        k = scatter(node->left, k, maxRow);
        k = scatter(node->right, k, maxRow);
        node->maxFree = max(node->left->maxFree, node->right->maxFree);
        node->sumFree = node->left->sumFree + node->right->sumFree;
        return k;
    }

    long long sumFree(Node* node, int l, int r) {
        if (node->r < l || node->l > r) return 0;
        if (l <= node->l && node->r <= r) return node->sumFree;
        return sumFree(node->left, l, r) + sumFree(node->right, l, r);
    }

public:
    BookMyShow(int n, int m) : m(m) {
        build(root, 0, n - 1);
    }

    vector<int> gather(int k, int maxRow) {
        int row, seat;
        if (gather(root, k, maxRow, row, seat))
            return {row, seat};
        return {};
    }

    bool scatter(int k, int maxRow) {
        long long total = sumFree(root, 0, maxRow);
        if (total < k) return false;
        scatter(root, k, maxRow);
        return true;
    }
};
