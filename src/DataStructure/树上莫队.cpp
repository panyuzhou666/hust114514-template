// 预处理部分
void dfs2(int u, int t) {
    top[u] = t;
    a[++tim] = u, in[u] = tim;
    if (son[u]) dfs2(son[u], t);
    for (auto v : e[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    a[++tim] = u, out[u] = tim;
}

// 处理询问部分
int lc = lca(x, y);
q[++tot].t = t;
q[tot].id = tot;
if (in[x] > in[y]) swap(x, y);  // 先x后y
if (lca == x) {                 // 直链情况
    q[tot].l = in[x];
    q[tot].r = in[y];
} else {  // 折链情况
    q[tot].l = out[x];
    q[tot].r = in[y];
    q[tot].lca = lc;  // 以便补偿
}