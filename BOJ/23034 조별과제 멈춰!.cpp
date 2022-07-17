// 2022-07-16
// 23034 조별과제 멈춰!
// https://www.acmicpc.net/problem/23034
/*
    MST, dfs (7,284KB, 84ms)
    시간 복잡도: ?
    풀이)
    - MST를 이용하여 불필요한 간선을 제거.
    이때, 사용하는 간선, 즉 최소 비용 간선의 비용을 tot에 저장.
    또한 path에 사용하는 간선의 시작점과 도착점, 비용을 저장.
    - X와 Y가 팀장일 때, T의 최솟값은 X와 Y 두 사이의 간선 중 가장 큰 비용을 제거하면 구할 수 있다.
    단, 위와 같이 MST를 이용하여 불필요한 간선을 제거한 상태여야 함.
    - 정점간 이동 시 가장 큰 비용을 저장할 mx_cost을 dfs를 이용하여 구함.
    - tot에서 입력된 X, Y간 mx_cost의 값을 뺀 후 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max n

struct P
{
    int a, b, c; // 두 정점 a, b(1 ≤ a, b ≤ n), 비용 c(1 ≤ c ≤ 100,000)
    friend bool operator<(const P &p1, const P &p2) { return p1.c < p2.c; }
};

struct Union_Find
{
    int parent[MAX];
    Union_Find() { iota(parent, parent + MAX, 0); }

    int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; }
} uf;

int n, m; // 인원 n(2 ≤ n ≤ 1,000), 간선의 개수 m(n ≤ m ≤ 100,000)
vector<P> v;
vector<pii> path[MAX]; // path[st] = {{ed, c}, ...}일 경우, st에서 정점 ed까지 비용 c로 갈 수 있음
int mx_cost[MAX][MAX]; // mx_cost[st][ed] = c일 때, st에서 ed까지의 가장 큰 간선의 비용은 c

void get_mx_cost(int root, int cur, int prev = 0) // dfs
{
    for (auto [next, n_cost] : path[cur])
    {
        if (next == prev)
            continue;

        mx_cost[root][next] = max(mx_cost[root][cur], n_cost);
        get_mx_cost(root, next, cur);
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    v.resize(m);
    for (auto &[a, b, c] : v)
        cin >> a >> b >> c;

    sort(v.begin(), v.end()); // 비용을 기준으로 오름차순 정렬

    int tot = 0;
    for (int i = 0; i < v.size(); i++)
    {
        auto [a, b, c] = v[i];

        int _a = uf.find_parent(a), _b = uf.find_parent(b);
        if (_a != _b)
        {
            path[a].push_back({b, c}), path[b].push_back({a, c}); // 사용하는 간선을 path에 저장
            uf.union_parent(_a, _b), tot += c;
        }
    }

    for (int i = 1; i <= n; i++)
        get_mx_cost(i, i);

    int q; // 질문의 개수 (1 ≤ Q ≤ 10,000)
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int x, y; // 1 ≤ x, y ≤ n
        cin >> x >> y;

        cout << tot - mx_cost[min(x, y)][max(x, y)] << '\n';
    }
}