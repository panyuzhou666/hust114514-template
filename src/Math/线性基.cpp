struct LB {
    const int BASE = 16;
    vector<int> d, p;
    int cnt, flag;
    LB() {
        d.assign(BASE, 0);
        p.assign(BASE, 0);
        cnt = flag = 0;
    }
    bool insert(int val, int pos) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    p[i] = pos;
                    return true;
                }
                if (pos > p[i]) swap(pos, p[i]), swap(val, d[i]);
                val ^= d[i];
            }
        }
        flag = 1;  // 可以异或出0
        return false;
    }
    bool check(ll val) {  // 判断 val 是否能被异或得到
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    return false;
                }
                val ^= d[i];
            }
        }
        return true;
    }
    ll ask_max(ll res) {
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ d[i]) > res) res ^= d[i];
        }
        return res;
    }
    ll ask_min() {
        if (flag) return 0;  // 特判 0
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i]) return d[i];
        }
    }
    void rebuild() {  // guass 消元 保证只有该处有 1
        for (int i = BASE - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (d[i] & (1ll << j)) d[i] ^= d[j];
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i]) p[cnt++] = d[i];
        }
    }
    ll kth(ll k) {      // 查询能被异或得到的第 k 小值, 如不存在则返回 -1
        if (flag) k--;  // 特判 0, 如果不需要 0, 直接删去
        if (!k) return 0;
        ll res = 0;
        if (k >= (1ll << cnt)) return -1;
        for (int i = BASE - 1; i >= 0; i--) {
            if (k & (1LL << i)) res ^= p[i];
        }
        return res;
    }
};