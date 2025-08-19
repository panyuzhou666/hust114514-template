#include<bits/stdc++.h>

template <class Info>
struct SegmentTree {
    int n;

    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    template <class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) +
               rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }

    /**
     * @brief 在线段树上二分，查找区间 [x, y) 中第一个满足 pred 条件的元素位置。
     * * @tparam F 谓词函数类型，应当是 bool(const Info&)
     * @param pred 谓词函数，如果当前区间的合并信息满足条件，则返回 true
     * @return int 第一个满足条件的位置索引，如果不存在则返回 -1
     */
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        // 如果当前区间 [l, r) 与查询区间 [x, y) 没有交集，直接返回
        if (l >= y || r <= x) {
            return -1;
        }
        // 如果当前区间被查询区间完全包含，并且整个区间的信息都不满足谓词，
        // 说明这个区间内不可能有答案，进行剪枝
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        // 如果到达叶子节点，说明找到了一个满足条件的最小单位，返回其位置
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        // 优先在左子树中查找，因为要找 "第一个"
        int res = findFirst(2 * p, l, m, x, y, pred);
        // 如果左子树没找到，再去右子树中查找
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }

    /**
     * @brief 在线段树上二分，查找区间 [x, y) 中最后一个满足 pred
     * 条件的元素位置。
     * * @tparam F 谓词函数类型，应当是 bool(const Info&)
     * @param pred 谓词函数，如果当前区间的合并信息满足条件，则返回 true
     * @return int 最后一个满足条件的位置索引，如果不存在则返回 -1
     */
    template <class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred) {
        // 如果当前区间 [l, r) 与查询区间 [x, y) 没有交集，直接返回
        if (l >= y || r <= x) {
            return -1;
        }
        // 如果当前区间被查询区间完全包含，并且整个区间的信息都不满足谓词，
        // 说明这个区间内不可能有答案，进行剪枝
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        // 如果到达叶子节点，说明找到了一个满足条件的最小单位，返回其位置
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        // 优先在右子树中查找，因为要找 "最后一个"
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        // 如果右子树没找到，再去左子树中查找
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int x = 0;
};

// 区间最大值
Info operator+(const Info &a, const Info &b) { return {std::max(a.x, b.x)}; }

int main() {

    std::vector<Info> a = {{1}, {5}, {2}, {8}, {6}, {7}, {4}, {9}};
    SegmentTree<Info> tr(a);

    // 在一个子区间 [0, 5) 中查找第一个值 >= 6 的元素
    int val = 6;
    int pos = tr.findFirst(0, 5, [&](const Info& v) {
        return v.x >= val;
    });

    return 0;
}
