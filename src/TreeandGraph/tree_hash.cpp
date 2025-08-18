using ull = unsigned long long;

/**
 * @brief 树哈希类
 *
 * 用于计算有根树和无根树的哈希值。
 * 核心思想是通过 DFS 和换根 DP
 * 来为每个节点的子树以及以每个节点为根的整棵树生成一个唯一的哈希值。
 */
class tree_hash {
   private:
    // 静态成员，用于在类的所有实例中共享
    static map<ull, ull> mp;  // 哈希值映射，确保相同的子树结构得到相同的随机值
    static mt19937_64 rng;    // 64位梅森旋转算法随机数生成器

    int n;                  // 树的节点数
    vector<vector<int>> g;  // 邻接表表示的树
    vector<ull> dp;         // dp[i] 存储以 i 为根的子树的哈希值
    vector<ull> rdp;        // rdp[i] 存储以 i 为整棵树的根时的哈希值
    ull hash_val;           // 整棵树的无根哈希值
    bool calced;            // 标记是否已执行计算

   public:
    /**
     * @brief 构造函数
     * @param ng 描述树结构的邻接表
     */
    tree_hash(const vector<vector<int>>& ng) {
        n = ng.size();
        g = ng;
        dp.resize(n, 0);
        rdp.resize(n, 0);
        hash_val = 0;
        calced = false;
    }

   private:
    /**
     * @brief 为一个子树哈希值生成一个唯一的随机映射值
     *
     * 使用 map 来记忆化，确保对于相同的输入 x，总是返回相同的随机数。
     * 这是为了保证同构的子树贡献的哈希值是相同的。
     * @param x 子树的哈希值
     * @return 映射后的唯一哈希值
     */
    static ull get(ull x) {
        if (mp.count(x)) return mp[x];
        return mp[x] = rng();
    }

    /**
     * @brief 第一次 DFS，计算每个节点的子树哈希值
     * @param p 当前节点
     * @param fa 父节点
     */
    void dfs(int p, int fa) {
        dp[p] = 1;  // 初始值，可以看作是节点自身的贡献
        for (auto s : g[p]) {
            if (s != fa) {
                dfs(s, p);
                // 将所有子节点的子树哈希值通过 get() 映射后累加
                dp[p] += get(dp[s]);
            }
        }
    }

    /**
     * @brief 第二次 DFS（换根 DP），计算以每个节点为根时整棵树的哈希值
     * @param p 当前节点
     * @param fa 父节点
     */
    void rdfs(int p, int fa) {
        if (fa == -1) {
            // 如果是根节点，其换根哈希值就是它的子树哈希值
            rdp[p] = dp[p];
        } else {
            // 否则，它的换根哈希值 = 它的子树哈希值 + 从父节点那边传来的哈希值
            // 父节点传来的值 = (父节点的换根哈希值 - 当前子树对父节点的贡献)
            ull parent_contribution = rdp[fa] - get(dp[p]);
            rdp[p] = dp[p] + get(parent_contribution);
        }

        for (auto s : g[p]) {
            if (s != fa) {
                rdfs(s, p);
            }
        }
    }

   public:
    /**
     * @brief 执行计算
     * @param root 任意指定的根节点，默认为 0
     */
    void calc(int root = 0) {
        dfs(root, -1);
        rdfs(root, -1);

        // 计算无根树哈希值，通常用所有节点的有根哈希值的异或和
        // 也可以用和，但异或可以避免顺序问题
        hash_val = 0;
        for (int i = 0; i < n; i++) {
            hash_val ^= rdp[i];
        }
        calced = true;
    }

    /**
     * @brief 获取以节点 p 为根的有根树哈希值
     * @param p 节点编号
     * @return 哈希值
     */
    ull rooted_hash(int p) {
        assert(calced && "calc() must be called before getting hash values.");
        return rdp[p];
    }

    /**
     * @brief 获取无根树的哈希值
     * @return 哈希值
     */
    ull unrooted_hash() {
        assert(calced && "calc() must be called before getting hash values.");
        return hash_val;
    }
};

// 初始化静态成员
mt19937_64 tree_hash::rng(
    chrono::steady_clock::now().time_since_epoch().count());
map<ull, ull> tree_hash::mp;
