struct TwoSat {
    int n;
    vector<vector<int>> e;
    vector<int> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}

    void add(int u, bool f, int v, bool g) {
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }

    bool work() {
        vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        vector<int> stk;
        int tot = 0, cnt = 0;
        auto tarjan = [&](auto self, int u) -> void {
            stk.push_back(u);
            dfn[u] = low[u] = tot++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = min(low[u], dfn[v]);
                }
            }

            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                cnt++;
            }
        };

        // 改为反向遍历就是字典序最大。
        for (int i = 0; i < 2 * n; i++) {
            if (dfn[i] == -1) {
                tarjan(tarjan, i);
            }
        }
        // 输出字典序最小的可行解。
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return 0;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        // 如果需要判断某个变量的取值是否唯一,需要判断由0能否到达1之类的,o(n^2)
        return 1;
    }
}