struct Q {
    int l, r, id;
} q[N];
bool cmp(Q x, Q y) {
    if (pos[x.l] == pos[y.l])
        return x.r < y.r;
    else
        return pos[x.l] < pos[y.l];
}
sort(q + 1, q + 1 + m);
for (int i = 1, l = 1, r = 0; i <= m; ++i) {
    while (l > q[i].l) add(a[--l]);  // 左扩展
    while (r < q[i].r) add(a[++r]);  // 右扩展
    while (l < q[i].l) del(a[l++]);  // 左删除
    while (r > q[i].r) del(a[r--]);  // 右删除
}