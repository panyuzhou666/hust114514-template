class Magic {
   public:
    int n;                              // 树中的节点数
    std::vector<std::vector<int>> adj;  // 树的邻接表
    std::vector<int> dep;               // dep[i] 存储节点 i 的深度
    std::vector<int> pos;    // pos[i] 存储节点 i 在欧拉序中首次出现的位置
    std::vector<int> euler;  // 树的欧拉序
    int tot;                 // 欧拉序中的节点总数

   private:
    std::vector<std::vector<int>> st;  // 用于在欧拉序上进行 RMQ 的稀疏表

   public:
    /**
     * @brief 默认构造函数。
     */
    Magic() : n(0), tot(0) {}

    /**
     * @brief 构造函数，为大小为 n 的树初始化对象。
     * @param n 树中的节点数。
     */
    Magic(int n) { init(n); }

    /**
     * @brief 为大小为 n 的树初始化或重新初始化数据结构。
     * @param n 节点数。
     */
    void init(int n) {
        this->n = n;
        tot = 0;
        adj.assign(n, {});
        dep.resize(n);
        pos.resize(n);
        // 欧拉序最多有 2*n - 1 个元素
        euler.resize(n * 2);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /**
     * @brief 执行深度优先搜索以构建欧拉序和深度数组。
     * @param u 当前节点。
     * @param parent 当前节点的父节点。
     * @param d 当前节点的深度。
     */
    void dfs(int u, int parent, int d) {
        dep[u] = d;
        pos[u] = tot;
        euler[tot++] = u;
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs(v, u, d + 1);
            euler[tot++] = u;
        }
    }

    void work(int root = 0) {
        // 1. 使用 DFS 构建欧拉序和深度数组。
        tot = 0;
        dfs(root, -1, 0);

        // 2. 初始化并构建用于 RMQ 的稀疏表。
        // 表中存储节点索引，并根据它们的深度进行比较。
        int max_log = (tot > 0) ? __lg(tot) : 0;
        st.assign(max_log + 1, std::vector<int>(tot));

        st[0].assign(euler.begin(), euler.begin() + tot);

        for (int j = 1; j <= max_log; j++) {
            for (int i = 0; i + (1 << j) <= tot; i++) {
                int u1 = st[j - 1][i];
                int u2 = st[j - 1][i + (1 << (j - 1))];
                // 存储深度较小的节点。
                st[j][i] = (dep[u1] < dep[u2]) ? u1 : u2;
            }
        }
    }

    int lca(int u, int v) {
        int l = pos[u];
        int r = pos[v];
        if (l > r) {
            std::swap(l, r);
        }
        int k = __lg(r - l + 1);

        int u1 = st[k][l];
        int u2 = st[k][r - (1 << k) + 1];

        return (dep[u1] < dep[u2]) ? u1 : u2;
    }
};
