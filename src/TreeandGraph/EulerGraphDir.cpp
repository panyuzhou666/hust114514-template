/**
 * @brief 有向图欧拉路/回路求解类
 *
 * 使用 Hierholzer 算法（逐步插入回路法）寻找欧拉通路。
 * 核心思想是从一个节点开始DFS，将经过的边删除，直到无法前进时将节点入栈。
 * 最终栈中逆序的节点序列即为一条欧拉路。
 */
class EulerGraphDir {
public:
    int n;                 // 图的节点数
    vector<vector<int>> g; // 邻接表
    vector<int> din, dout; // 节点的入度和出度
    vector<int> path;      // 存储找到的欧拉路

private:
    vector<int> cur; // 当前弧优化：记录每个节点当前访问到了哪条边

    /**
     * @brief Hierholzer 算法核心
     * @param u 当前节点
     */
    void dfs(int u) {
        // 使用引用和后置++实现当前弧优化，遍历u的所有出边
        for (int& i = cur[u]; i < g[u].size(); ) {
            int v = g[u][i];
            i++; // 移动到下一条边（这条边被"删除"）
            dfs(v);
        }
        path.push_back(u); // 回溯时将节点加入路径
    }

public:
    /**
     * @brief 构造函数
     * @param n_ 节点数量
     */
    EulerGraphDir(int n_) : n(n_) {
        g.resize(n);
        din.assign(n, 0);
        dout.assign(n, 0);
        cur.assign(n, 0);
    }

    /**
     * @brief 添加一条有向边
     * @param u 起点
     * @param v 终点
     */
    void add_edge(int u, int v) {
        g[u].push_back(v);
        dout[u]++;
        din[v]++;
    }
    
    /**
     * @brief 检查是否存在欧拉回路
     * @return 如果所有点的入度都等于出度，则返回 true
     */
    bool has_euler_circuit() {
        for (int i = 0; i < n; i++) {
            if (din[i] != dout[i]) {
                return false;
            }
        }
        // 注意：还需要检查图的连通性，这里省略，假设图是连通的
        return true;
    }

    /**
     * @brief 检查是否存在欧拉路
     * @return 如果满足欧拉路条件，返回 true
     */
    bool has_euler_path() {
        int start_node = -1, end_node = -1;
        int odd_count = 0;
        for (int i = 0; i < n; i++) {
            if (din[i] != dout[i]) {
                odd_count++;
                if (dout[i] == din[i] + 1) {
                    if (start_node != -1) return false; // 超过一个起点
                    start_node = i;
                } else if (din[i] == dout[i] + 1) {
                    if (end_node != -1) return false; // 超过一个终点
                    end_node = i;
                } else {
                    return false; // 度数差不为1
                }
            }
        }
        // 要么所有点入度=出度，要么恰好一个起点一个终点
        return odd_count == 0 || odd_count == 2;
    }

    /**
     * @brief 求解欧拉路/回路
     * @return 如果不存在则返回 false
     */
    bool solve() {
        int start_node = -1;
        int odd_out = 0, odd_in = 0;

        for (int i = 0; i < n; i++) {
            if (dout[i] > din[i]) {
                odd_out++;
                if (dout[i] - din[i] > 1) return false;
                start_node = i;
            } else if (din[i] > dout[i]) {
                odd_in++;
                if (din[i] - dout[i] > 1) return false;
            }
        }

        // 判断是否存在欧拉路或回路
        if (!((odd_out == 0 && odd_in == 0) || (odd_out == 1 && odd_in == 1))) {
            return false;
        }

        // 如果是欧拉回路，从第一个有出度的点开始
        if (start_node == -1) {
            for (int i = 0; i < n; i++) {
                if (dout[i] > 0) {
                    start_node = i;
                    break;
                }
            }
            // 如果是个空图或者只有孤立点，也算合法
            if (start_node == -1) return true;
        }
        
        dfs(start_node);
        reverse(path.begin(), path.end());
        
        // 检查是否所有边都被访问
        int edge_count = 0;
        for(int i = 0; i < n; ++i) edge_count += dout[i];
        return path.size() == edge_count + 1;
    }

    /**
     * @brief 对邻接表排序以获得字典序最小的欧拉路
     */
    void min_lexicographical() {
        for (auto& vec : g) {
            sort(vec.begin(), vec.end());
        }
    }
};
