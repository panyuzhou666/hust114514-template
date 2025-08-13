#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
struct node {
    int a, b;
};
struct cmp {
    bool operator()(const node& a, const node& b) const {
        if (a.a != b.a) return a.a < b.a;
        return a.b < b.b;
    }
};
// 基于自定义类型的平衡树
tree<node,                              // 元素类型
     null_type,                         // 无映射值
     cmp,                               // 比较策略
     rb_tree_tag,                       // 底层使用红黑树
     tree_order_statistics_node_update  // 支持排名更新
     >
    pbds;

// 基于 int 类型的平衡树
tree<int, null_type, std::less<int>, rb_tree_tag,
     tree_order_statistics_node_update>
    tr;
void solve() {
    // 插入
    pbds.insert({1, 1});
    pbds.insert({1, 2});
    pbds.insert({2, 2});

    // 访问
    for (auto [a, b] : pbds) cout << a << ' ' << b << endl;

    // 删除
    pbds.erase({1, 0});  // 无用
    pbds.erase({1, 1});

    // 获取元素的排名
    // 注意，返回值为 0base
    cout << pbds.order_of_key({2, 2}) + 1 << endl;  // 2
    cout
        << pbds.order_of_key({1, 0}) + 1
        << endl;  // 1
                  // (元素可以不在集合中，但仍然可以查找排名，此时可当作其在集合)

    // 查找排名第k小（注意，这里同样为 0base)
    auto no = pbds.find_by_order(2 - 1);
    cout << no->a << ' ' << no->b << endl;  //(2,2)

    // 存在性
    auto it = pbds.find({1, 0});
    cout << (it != pbds.end()) << endl;  // 0

    // 二分
    auto itt = pbds.lower_bound({2, 1});
    cout << itt->a << ' ' << itt->b << endl;  //(2,2)

    // 清空
    pbds.clear();
}
int main() {
    solve();
    return 0;
}
