#include <bits/extc++.h>  // 包含了 pb_ds 的所有头文件
using namespace __gnu_pbds;

struct node {
    int num = 0, sc = 0;
    string name;
};
struct cmp {
    bool operator()(const node& a, const node& b) const {
        if (a.num != b.num) return a.num > b.num;  // 胜场多者优先
        if (a.sc != b.sc) return a.sc > b.sc;      // 净胜分高者优先
        return a.name < b.name;                    // 队名字典序小者优先
    }
};

// 用自定义类型和比较器声明平衡树
tree<node, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update> tr;
// 基于 int 类型的平衡树
tree<int, null_type, std::less<int>, rb_tree_tag,
     tree_order_statistics_node_update>
    tr;
