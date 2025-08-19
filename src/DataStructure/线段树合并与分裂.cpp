int ln[M], rn[M], tot, cnt[M], rt[N];
// 合并 左闭右开
int merge(int u, int v, int l, int r) {
    if (!u || !v) return u + v;
    if (l == r - 1) {
        cnt[u] += cnt[v];
        return u;
    }
    int mid = (l + r) / 2;
    ln[u] = merge(ln[u], ln[v], l, mid);
    rn[u] = merge(rn[u], rn[v], mid, r);
    cnt[u] = cnt[ln[u]] + cnt[rn[u]];
    return u;
}

// 这里需要和主席树区别开，不需要共享节点
void insert(int& u, int l, int r, int x) {
    if (!u) u = ++tot;
    cnt[u]++;
    if (l == r - 1) return;
    int mid = (l + r) / 2;
    if (x < mid)
        insert(ln[u], l, mid, x);
    else
        insert(rn[u], mid, r, x);
}

// op = 0 表示前k个给x 后面的给y
// op = 1 表示后k个给x 前面的给y
void split(int x, int& y, int k, int op) {
    if (!x) return;
    y = ++tot;
    if (!op) {
        int s = cnt[ln[x]];
        if (s >= k)
            split(ln[x], ln[y], k, op), swap(rn[x], rn[y]);
        else
            split(rn[x], rn[y], k - s, op);
        cnt[y] = cnt[x] - k, cnt[x] = k;
    } else {
        int s = cnt[rn[x]];
        if (s >= k)
            split(rn[x], rn[y], k, op), swap(ln[x], ln[y]);
        else
            split(ln[x], ln[y], k - s, op);
        cnt[y] = cnt[x] - k, cnt[x] = k;
    }
}