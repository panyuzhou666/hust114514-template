struct tree {
    int n, rt;
    vector<int> ln, rn;

    // 按照数组下标构成二叉搜索树
    // 按照 w 构成小根堆。
    void build(vector<int>& w) {
        this->n = w.size();
        ln.resize(n, -1), rn.resize(n, -1);

        vector<int> stk;
        for (int i = 0; i < n; i++) {
            int last = -1;
            // 如果要改成大根堆, 只需将下面的 > 改为 <
            while (!stk.empty() && w[stk.back()] > w[i])
                last = stk.back(), stk.pop_back();
            if (!stk.empty()) rn[stk.back()] = i;
            if (last != -1) ln[i] = last;
            stk.push_back(i);
        }
        rt = stk[0];
    }
};