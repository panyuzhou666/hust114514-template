int dfn[N];
int h[N], m, a[N << 1], len;  // 存储关键点

bool cmp(int x, int y) {
    return dfn[x] < dfn[y];  // 按照 dfs 序排序
}

void build() {
    sort(h + 1, h + m + 1, cmp);  // 把关键点按照 dfs 序排序
    for (int i = 1; i < m; ++i) {
        a[++len] = h[i];
        a[++len] = lca(h[i], h[i + 1]);  // 插入 lca
    }
    a[++len] = h[m];
    sort(a + 1, a + len + 1, cmp);  // 把所有虚树上的点按照 dfs 序排序
    len = unique(a + 1, a + len + 1) - a - 1;  // 去重
    for (int i = 1, lc; i < len; ++i) {
        lc = lca(a[i], a[i + 1]);
        conn(lc, a[i + 1]);  // 连边 lc -> a[i+1]
    }
}