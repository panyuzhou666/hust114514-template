ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) return x = 1, y = 0, a;
    ll t = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return t;
}
ll inv(ll x, ll m) {
    ll a, b;
    exgcd(x, m, a, b);
    return (a % m + m) % m;
}

/**
 * @brief 求解 ax + by = c，返回 x 的最小非负整数解和对应的 y
 * @return 返回一个 pair<ll, ll>。如果方程有解，返回 {x, y}，其中 x
 * 是最小非负整数解； 如果无解，返回 {-1, -1}。
 */
std::pair<ll, ll> exgcd(ll a, ll b, ll c) {
    assert(a || b);
    // 迭代基：如果 b=0，方程为 ax=c，解为 x=c/a, y=0 (y可为任意值，取0)
    if (!b) return {c / a, 0};

    ll d = std::gcd(a, b);
    if (c % d) return {-1, -1};  // c 不是 gcd(a,b) 的倍数，无整数解

    // p, q 保存原始的 a, b 值
    ll x = 1, x1 = 0, p = a, q = b, k;

    // 用于计算最后 x 的模数
    ll mod = std::abs(b / d);

    // 循环结束后，求得的 x 是满足 a*x + b*y = gcd(a,b) 的一个解
    while (b) {
        k = a / b;
        x -= k * x1;
        a -= k * b;
        std::swap(x, x1);
        std::swap(a, b);
    }

    // 将 ax + by = d 的解 x 扩展为 ax + by = c 的解
    // 通解为 x' = x * (c/d) + k * (b/d)，我们要求最小非负整数解
    // 所以先对 b/d 取模
    x = x * (c / d) % mod;

    // 保证 x 是最小非负整数
    if (x < 0) x += mod;

    // 根据求得的 x，计算出对应的 y
    return {x, (c - p * x) / q};
}
