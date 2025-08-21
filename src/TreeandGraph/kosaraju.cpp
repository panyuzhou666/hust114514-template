bitset<N> e[N], re[N], vis;

// e 是原图的邻接矩阵，re 是反图的邻接矩阵
// e[i][j] = 1 表示存在一条从 i 到 j 的有向边
// re[j][i] = 1 同样表示 i 到 j 的边

vector<int> sta;
void dfs0(int x, bitset<N> e[]) {
    vis.reset(x);
    while (true) {
        int go = (e[x] & vis)._Find_first();
        if (go == N) break;
        dfs0(go, e);
    }
    sta.push_back(x);
}
// 返回一个二维向量，每个内层 vector 包含一个强连通分量的所有顶点
vector<vector<int>> solve() {  // re 需要连好反向边
    vis.set();
    for (int i = 1; i <= n; ++i)
        if (vis.test(i)) dfs0(i, e);
    vis.set();
    auto s = sta;
    vector<vector<int>> ret;
    for (int i = n - 1; i >= 0; --i)
        if (vis.test(s[i])) {
            sta.clear(), dfs0(s[i], re), ret.push_back(sta);
        }
    return ret;
}