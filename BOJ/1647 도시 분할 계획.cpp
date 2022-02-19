// 1647 도시 분할 계획
// https://www.acmicpc.net/problem/
/*
    MST, 크루스칼 알고리즘 (14,012KB, 308ms)
    시간 복잡도: ?
    풀이)
    - 크루스칼 알고리즘을 이용해 최소한의 간선을 이용해 각 정점을 이을 때의 최소 비용 ans를 구해준다.
    - 이 문제는 두 개의 도시로 만들 때의 최소 비용을 구하는 문제이다.
    하나로 이어진 간선 중 하나를 제거할 시, 두 개의 도시가 된다.
    이는 ans를 구하는 과정에서 사용한 c를 ans에서 제외시키면 된다. (간선을 하나 제거한 트리는 두 개로 나뉜다.)
    최소 비용을 구하는 문제이므로, c 중에서도 가중치가 가장 높은 c를 제거해줘야 한다.
    - 유니온 파인드 과정에서 가장 큰 c의 값을 mx에 저장해둔 후, ans를 출력하는 과정에서 mx의 값만큼 빼준 후 출력해준다.
    etc.) 배울게 많았던 문제.
    참고)
    - 개념 보충: https://www.acmicpc.net/board/view/75974 (답글 참고)
    - 트리를 두 개로 나누는 방법: https://yabmoons.tistory.com/188
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003

struct P
{
    int a, b, c; // 1 ≤ C ≤ 1,000
    friend bool operator<(const P &p1, const P &p2) { return p1.c < p2.c; }
};

struct Union_Find
{
    int parent[MAX];

    Union_Find() { iota(parent, parent + MAX, 0); }

    int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a > b ? parent[a] = b : parent[b] = a; }
};

int main()
{
    FAST_IO;

    int n, m; // 집의 개수 N(2 ≤ n ≤ 100,000), 길의 개수 M(d1 ≤ m ≤ 1,000,000)
    cin >> n >> m;
    vector<P> v(m);
    for (auto &[a, b, c] : v)
        cin >> a >> b >> c;
    sort(v.begin(), v.end());

    int ans = 0;
    Union_Find uf;
    int mx = 0;
    for (int i = 0; i < m; i++)
    {
        auto [a, b, c] = v[i];
        a = uf.find_parent(a), b = uf.find_parent(b);
        if (a != b)
        {
            ans += c, uf.union_parent(a, b);
            mx = max(mx, c);
        }
    }

    cout << ans - mx;
}