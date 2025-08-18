// 轻重链剖分的性质保证每个点只会被加入和删除 log 次

struct HLD {
    vector<vector<int>> e;
    vector<int> sz, son;
    int hson;  // 不需要被添加的重子树
    HLD(int n) {
        e.resize(n + 1);
        sz.resize(n + 1);
        son.resize(n + 1);
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }

    void dfs1(int u, int f) {
        sz[u] = 1;
        for (auto v : e[u]) {
            if (v == f) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    void add(int u, int f) {
        /*
        加点逻辑
        */
        for (auto v : e[u]) {
            if (v == f || v == hson) continue;
            add(v, u);
        }
    }

    void sub(int u, int f) {
        /*
        删点逻辑。
        */
        for (auto v : e[u]) {
            if (v == f) continue;
            sub(v, u);
        }
    }

    void dfs2(int u, int f, int op) {
        for (auto v : e[u]) {
            if (v == f || v == son[u]) continue;
            dfs2(v, u, 0);
        }
        if (son[u]) {
            dfs2(son[u], u, 1);
        }
        hson = son[u];
        add(u, f);

        /*
        获取该点的答案。
        */

        if (!op) {
            sub(u, f);
        }
    }

    void work(int rt = 1) {
        dfs1(rt, 0);
        dfs2(rt, 0, 0);
    }
};