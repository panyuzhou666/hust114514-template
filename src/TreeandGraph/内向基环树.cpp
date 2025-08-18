// 返回p所在连通块的一个环上点
int check(int p) {
    if (vis[p]) return p;
    vis[p] = 1;
    return check(ne[p]);
}

vector<int> cir;
int p = check(i);
int q = p;
while (1) {
    cir.push_back(q);
    if (ne[q] == p) break;
    q = ne[q];
}