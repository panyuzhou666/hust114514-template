struct SAM {
    static constexpr int M = 26;  // 字符集大小
    struct Node {
        int len;            // 该状态代表的最长字符串的长度
        int link;           // 后缀链接
        array<int, M> nxt;  // 转移边
        Node() : len{}, link{}, nxt{} {}
    };
    vector<Node> t;  // 状态节点数组
    int last = 1;    // 指向上一个完整字符串对应的状态节点

    SAM() { init(); }

    void init() {
        t.assign(2, Node());
        t[0].len = -1;  // 虚空节点，方便处理
        t[0].nxt.fill(1);
        // t[1] 是初始状态节点，代表空串""
    }

    int newNode() {
        t.push_back(Node());
        return t.size() - 1;
    }

    void extend(int x) {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while (p != 0 && t[p].nxt[x] == 0) {
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if (p == 0) {
            t[cur].link = 1;
        } else if (t[q].len == t[p].len + 1) {
            t[cur].link = q;
        } else {
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while (p != 0 && t[p].nxt[x] == q) {
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    int nxt(int p, int x) { return t[p].nxt[x]; }
    int link(int p) { return t[p].link; }
    int len(int p) { return t[p].len; }
    int size() { return t.size(); }

    static inline int num(int x) { return x - 'a'; }
    SAM(string &s) {
        init();
        build(s);
    }

    // 完整构建 SAM
    void build(string &s) {
        for (auto &c : s) {
            extend(num(c));
        }
        get_out_linktree();
    }

    // ---- 可选部分 ---- //
    vector<vector<int>> ot;  // out-link-tree, parent 树
    vector<int> endpos_size;

    // 构建 parent 树
    void get_out_linktree() {
        ot.assign(t.size(), {});
        for (int i = 2; i < t.size(); i++) {
            ot[t[i].link].push_back(i);
        }
    }

    // 计算每个状态的 endpos 集合大小
    void calc_endpos_size(string &s) {
        endpos_size.resize(t.size());
        int p = 1;
        for (auto c : s) {
            p = t[p].nxt[num(c)];
            endpos_size[p]++;
        }
        auto dfs = [&](auto &&self, int p) -> void {
            for (auto s : ot[p]) {
                self(self, s);
                endpos_size[p] += endpos_size[s];
            }
        };
        dfs(dfs, 1);
        endpos_size[1] = 1;
    }
};
