class Solution {
public:
    struct Node {
        int l, r, lch, rch, maxlen, llen, rlen;
        char lchv, rchv;
    };
    vector<Node> tree;
    int n;
    void build(const string& s, int idx, int l, int r) {
        tree[idx].l = l; tree[idx].r = r;
        if (l == r) {
            tree[idx].maxlen = tree[idx].llen = tree[idx].rlen = 1;
            tree[idx].lchv = tree[idx].rchv = s[l];
            return;
        }
        int m = (l + r) / 2;
        tree[idx].lch = idx * 2 + 1;
        tree[idx].rch = idx * 2 + 2;
        build(s, tree[idx].lch, l, m);
        build(s, tree[idx].rch, m + 1, r);
        pull(idx);
    }
    void pull(int idx) {
        Node& t = tree[idx];
        Node& l = tree[t.lch], &r = tree[t.rch];
        t.lchv = l.lchv;
        t.rchv = r.rchv;
        t.llen = l.llen;
        if (l.llen == l.r - l.l + 1 && l.rchv == r.lchv)
            t.llen += r.llen;
        t.rlen = r.rlen;
        if (r.rlen == r.r - r.l + 1 && l.rchv == r.lchv)
            t.rlen += l.rlen;
        t.maxlen = max({l.maxlen, r.maxlen, l.rchv == r.lchv ? l.rlen + r.llen : 0});
    }
    void update(int idx, int pos, char c) {
        Node& t = tree[idx];
        if (t.l == t.r) {
            t.lchv = t.rchv = c;
            return;
        }
        if (pos <= tree[t.lch].r) update(t.lch, pos, c);
        else update(t.rch, pos, c);
        pull(idx);
    }
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        n = s.size();
        tree.resize(n * 4);
        build(s, 0, 0, n - 1);
        vector<int> res;
        for (int i = 0; i < queryIndices.size(); ++i) {
            update(0, queryIndices[i], queryCharacters[i]);
            res.push_back(tree[0].maxlen);
        }
        return res;
    }
};
