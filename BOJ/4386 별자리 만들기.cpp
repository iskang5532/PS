// 4386 별자리 만들기
// https://www.acmicpc.net/problem/4386
/*
    MST, 크루스칼 알고리즘 (2,300KB, 0ms)
    시간 복잡도: ?
    풀이)
    1. 좌표간 거리를 구해 v2에 두 좌표와 거리를 저장.
    2. v2를 거리를 기준으로 오름차순 정렬.
    3. v2에 저장된 값을 꺼내어 MST 수행.
    MST
    - 두 좌표의 부모가 다른 경우, 부모를 하나로 통일하며 거리를 ans에 저장.
    - 두 좌표의 부모가 같은 경우, 두 좌표의 최단 거리를 앞서 구했으므로 다음 값을 탐색.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <cmath>     // pow
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103
using pdd = pair<double, double>; // {x, y}

struct P
{
    int a, b; // 두 좌표 a, b
    double c; // 거리

    friend bool operator<(const P &p1, const P &p2) { return p1.c < p2.c; } // c를 기준으로 오름차순 정렬
};

struct Union_Find
{
    int parent[MAX];

    Union_Find() { iota(parent, parent + MAX, 0); };
    int find_parent(int x) { return x == parent[x] ? parent[x] : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; };
};

int main()
{
    FAST_IO;

    int n; // 별의 개수 (1 ≤ n ≤ 100)
    cin >> n;

    vector<pdd> v(n);
    for (auto &[a, b] : v)
        cin >> a >> b;

    vector<P> v2; // v2[i] = {a, b, c}일 때, a에서 b까지의 거리는 c (i번쨰로 거리가 짧음)
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) // 좌표 i와 좌표 j의 거리 구하기
        {
            auto [x1, y1] = v[i];
            auto [x2, y2] = v[j];
            v2.push_back({i, j, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))});
        }

    sort(v2.begin(), v2.end());

    double ans = 0;
    Union_Find uf;
    for (auto [a, b, c] : v2)
    {
        a = uf.find_parent(a), b = uf.find_parent(b);
        if (a != b)
            uf.union_parent(a, b), ans += c;
    }

    cout << fixed, cout.precision(2);
    cout << ans;
}