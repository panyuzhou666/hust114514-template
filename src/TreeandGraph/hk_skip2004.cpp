vector<int> E[N];  // 邻接表，E[u] 存储左侧顶点 u 连接的所有右侧顶点
vector<int> ml, mr;  // ml[i] 存储左侧顶点 i 匹配的右侧顶点，mr[i] 存储右侧顶点
                     // i 匹配的左侧顶点。0 表示未匹配。
vector<int> a, p;  // HK 算法内部使用的辅助数组，无需关心具体含义

/**
 * @brief 计算二分图的最大匹配 (Hopcroft-Karp 算法)
 * @param nl 左侧顶点的数量 (编号从 1 到 nl)
 * @param nr 右侧顶点的数量 (编号从 1 到 nr)
 */
void match(int nl, int nr) {
    ml.assign(nl + 1, 0);
    mr.assign(nr + 1, 0);
    while (true) {
        bool ok = false;
        a.assign(nl + 1, 0);
        p.assign(nl + 1, 0);
        static queue<int> q;
        while (!q.empty()) q.pop();  // 清空队列
        for (int i = 1; i <= nl; i++)
            if (!ml[i]) a[i] = p[i] = i, q.push(i);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            if (ml[a[x]]) continue;
            for (auto y : E[x]) {
                if (!mr[y]) {
                    for (ok = 1; y; x = p[x]) mr[y] = x, swap(ml[x], y);
                    break;
                } else if (!p[mr[y]])
                    q.push(y = mr[y]), p[y] = x, a[y] = a[x];
            }
            if (ok) break;  // 找到一条增广路后就跳出
        }
        if (!ok) break;  // 找不到更多增广路，算法结束
    }
}
