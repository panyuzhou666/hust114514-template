const int N = 1e3 + 10;
// 带随机化的、基于增广路搜索的启发式算法
// 该做法能在洛谷通过 70 % 的测试点 疑似没用

int n, m, vis[N];
int mat[N];  // 匹配数组。mat[i] = j 表示顶点 i 和顶点 j 匹配。若 mat[i] = 0，则
             // i 未匹配。
vector<int> E[N];
bool dfs(int tim, int x) {
    shuffle(E[x].begin(), E[x].end(), rng);
    vis[x] = tim;
    for (auto y : E[x]) {
        int z = mat[y];
        if (vis[z] == tim) continue;
        mat[x] = y, mat[y] = x, mat[z] = 0;
        if (!z || dfs(tim, z)) return true;
        mat[x] = 0, mat[y] = z, mat[z] = y;
    }
    return false;
}
int main() {  // 暗含二分图性质跑一次即可
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    for (int _ = 0; _ < 10; _++) {
        fill(vis + 1, vis + n + 1, 0);
        for (int i = 1; i <= n; ++i)
            if (!mat[i]) dfs(i, i);
    }
    int res = 0;
    for (int i = 1; i <= n; i++) res += mat[i] > 0;
    cout << res / 2 << "\n";
    for (int i = 1; i <= n; i++) cout << mat[i] << " \n"[i == n];
    return 0;
}
