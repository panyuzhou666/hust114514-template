#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

template <typename T, typename Cmp = std::less<T>>
using heap = __gnu_pbds::priority_queue<T, Cmp>;

void solve() {
    // 创建一个小根堆（默认是大根堆，std::less<int> 使其成为最大堆）
    // 使用 std::greater<int> 来创建一个最小堆
    heap<int, std::greater<int>> h1;

    // push: 插入元素
    h1.push(10);
    h1.push(5);
    h1.push(20);

    // 获取堆顶元素（最小值）
    cout << "h1 堆顶元素: " << h1.top() << endl;  // 5

    // 弹出堆顶元素
    h1.pop();
    cout << "h1 pop后堆顶元素: " << h1.top() << endl;  // 10

    // 合并操作
    heap<int, std::greater<int>> h2;
    h2.push(8);
    h2.push(10);

    cout << "合并前 h1 的大小: " << h1.size() << endl;  // 2
    cout << "合并前 h2 的大小: " << h2.size() << endl;  // 2

    // join: 将 h2 合并到 h1 中。操作后，h2 会被清空
    // 该操作复杂度为 O(1)
    h1.join(h2);

    cout << "合并后 h1 的大小: " << h1.size() << endl;  // 4
    cout << "合并后 h2 的大小: " << h2.size() << endl;  // 0
    cout << "合并后 h1 的堆顶: " << h1.top() << endl;   // 8

    // 遍历堆中元素
    // 注意：遍历顺序不保证有序
    for (int val : h1) {
        cout << val << " ";
    }
    cout << endl;

    // 修改元素
    // modify 需要一个指向元素的迭代器
    // AI 称 push 和 pop 某个元素不会使其他迭代器元素失效
    auto it = h1.push(12);  // push 会返回一个迭代器
    h1.push(30);

    cout << "修改前堆顶: " << h1.top() << endl;  // 8

    // 将值为 12 的元素修改为 2
    h1.modify(it, 2);

    cout << "修改后堆顶: " << h1.top() << endl;  // 2

    // 清空堆
    h1.clear();
}

int main() {
    solve();
    return 0;
}
