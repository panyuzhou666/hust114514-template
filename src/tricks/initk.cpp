int n, l[N][60], r[N][60], a[N], k;
/*
l[i][j] 表示 i 左边第 j 个 比 a[i] 大的数。
r[i][j] 同理
*/
vector<int> stk[60], tmp;
void init() {
    for (int i = 1; i <= n; i++) l[i][0] = r[i][0] = i;
    for (int i = n; i; i--) {
        for (int j = k; j; --j) {
            tmp.clear();
            while (!stk[j].empty() && a[i] > a[stk[j].back()]) {
                l[stk[j].back()][j] = i;
                tmp.push_back(stk[j].back());
                stk[j].pop_back();
            }
            if (j + 1 <= k)
                stk[j + 1].insert(stk[j + 1].end(), tmp.rbegin(), tmp.rend());
        }
        stk[1].push_back(i);
    }
    for (int i = 1; i <= k; i++) stk[i].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = k; j; --j) {
            tmp.clear();
            while (!stk[j].empty() && a[i] > a[stk[j].back()]) {
                r[stk[j].back()][j] = i;
                tmp.push_back(stk[j].back());
                stk[j].pop_back();
            }
            if (j + 1 <= k)
                stk[j + 1].insert(stk[j + 1].end(), tmp.rbegin(), tmp.rend());
        }
        stk[1].push_back(i);
    }
}
