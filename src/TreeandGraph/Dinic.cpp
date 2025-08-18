const ll INF = 1e9;
int nn, mm, s, t, cnt = 1, h[N], ans;
struct node {
    int v, nex;
    ll w;
} e[M];
void add(int u, int v, ll w) {
    e[++cnt] = {v, h[u], w};
    h[u] = cnt;
}
int d[N], now[N];
int bfs() {
    for (int i = 1; i <= nn; i++) d[i] = INF;
    queue<int> q;
    d[s] = 0;
    now[s] = h[s];
    q.push(s);
    while (q.size()) {
        int p = q.front();
        q.pop();
        for (int i = h[p]; i; i = e[i].nex) {
            int v = e[i].v;
            if (e[i].w > 0 && d[v] == INF) {
                d[v] = d[p] + 1;
                now[v] = h[v];
                q.push(v);
                if (v == t) return 1;
            }
        }
    }
    return 0;
}
ll dfs(int p, ll sum) {
    if (p == t) return sum;
    ll k = 0, flow = 0;
    for (int i = now[p]; i && sum; i = e[i].nex) {
        now[p] = i;
        ll v = e[i].v, w = e[i].w;
        if (w > 0 && d[v] == d[p] + 1) {
            k = dfs(v, min(sum, (ll)w));
            if (k == 0) d[v] = INF;
            e[i].w -= k;
            e[i ^ 1].w += k;
            sum -= k;
            flow += k;
        }
    }
    return flow;
}
void solve() {
    for (int i = 1; i <= nn; i++) h[i] = 0;
    ans = 0;
    cnt = 1;
    // add(u,v.w),add(v,u,0);
    while (bfs()) ans += dfs(s, INF);
}