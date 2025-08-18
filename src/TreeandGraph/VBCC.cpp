/*
用于求解无向图的点双连通分量（V-BCCs），并能构建对应的圆方树。
圆方树是一个新图，其中包含两种类型的节点：
1. 方点：代表原始图中的一个点双连通分量。
2. 圆点：代表原始图中的一个割点。
树中的边连接一个圆点和一个方点，当且仅当该割点属于该点双连通分量。
 */
struct VBCC {
    int n;  // 原始图的节点数
    vector<vector<int>> adj;
    vector<vector<int>> col;  // 存储每个点双连通分量包含的节点
    vector<int> dfn, low;
    vector<int> stk;
    int cur, cnt;     // 时间戳计数器和点双连通分量计数器
    vector<int> cut;  // 标记每个节点是否为割点
    vector<int> bel;  // 映射：原始图节点 -> 新图节点编号

    VBCC(int n) { init(n); }

    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        col.assign(n, {});
        cut.assign(n, 0);
        bel.assign(n, -1);
        stk.clear();
        cnt = cur = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void tarjan(int x, int root) {
        low[x] = dfn[x] = cur++;
        stk.push_back(x);
        if (x == root && !adj[x].size()) {
            col[cnt++].push_back(x);
            return;
        }

        int flg = 0;
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                tarjan(y, root);

                low[x] = min(low[x], low[y]);

                if (dfn[x] <= low[y]) {
                    flg++;
                    if (x != root || flg > 1) {
                        cut[x] = 1;
                    }
                    int pre = 0;
                    do {
                        pre = stk.back();
                        col[cnt].push_back(pre);
                        stk.pop_back();
                    } while (pre != y);
                    col[cnt++].push_back(x);
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }

    void work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                tarjan(i, i);
            }
        }
    }

    // 新图（圆方树）的结构体定义
    struct Graph {
        int n;                         // 新图的节点数量
        vector<pair<int, int>> edges;  // 新图的边集
    };

    Graph compress() {
        // 节点编号规则：
        // 0 到 cnt-1 是 "方点"，代表 V-BCC
        // cnt 开始是 "圆点"，代表割点
        int m = cnt;
        bel.assign(n, -1);

        // 为所有割点分配新编号
        for (int i = 0; i < n; i++) {
            if (cut[i]) {
                bel[i] = m++;
            }
        }

        Graph g;
        g.n = m;

        // 构建新图的边
        for (int i = 0; i < cnt; i++) {
            for (auto u : col[i]) {
                if (cut[u]) {
                    g.edges.emplace_back(i, bel[u]);
                }
            }
        }

        return g;
    }
};
