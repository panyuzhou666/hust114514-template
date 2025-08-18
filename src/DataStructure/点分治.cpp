vector<int>e[N];
int vis[N], s[N], maxs[N] = {(int)1e9};
void getrt(int p, int fa, int siz, int &rt) {
    s[p] = 1;
    maxs[p] = 0;
    for (auto [v, c] : e[p]) {
        if (v == fa || vis[v]) continue;
        s[p] += s[v];
        maxs[p] = max(maxs[p], s[v]);
    }
    maxs[p] = max(maxs[p], siz - s[p]);
    if (maxs[p] < maxs[rt]) rt = p;
}
void cal(int p, int siz) {
    int rt = 0;
    getrt(p, 0, siz, rt);
    for (auto [v, c] : e[rt]) {
        if (vis[v]) continue;
        // 计算相关贡献
    }
    vis[rt] = 1;
    for (auto [v, c] : e[rt]) {
        if (vis[v]) continue;
        if (s[v] > s[rt]) s[v] = siz - s[rt];
        cal(v, s[v]);
    }
}
// 调用：cal(1,n);