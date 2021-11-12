/*
    1197 최소 스패닝 트리
    유니온 파인드, MST(최소 신장 트리, 크루스칼 알고리즘) (3,236KB, 36ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1197
    풀이)
    - 가중치를 기준으로 오름차순 정렬.
    - 현재 두 정점의 부모가 서로 다른 경우, 서로 연결해주며 가중치를 저장함.
    - 현재 두 정점의 부모가 서로 같은 경우, 이는 앞서 연결해줬다는 뜻. (= 이전 가중치는 현재 가중치보다 작음)
    참고)
    - 이론: https://gmlwjd9405.github.io/2018/08/28/algorithm-mst.html
    - 이론 및 코드: https://m.blog.naver.com/ndb796/221230994142
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 10000 + 1

int parent[MAX];
struct P
{
    int a, b, c; // 두 정점 a, b와 가중치 c (|c| ≤ 1M)
};
bool cmp(const P &p1, const P &p2) { return p1.c < p2.c; } // 가중치를 기준으로 오름차순 정렬

int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); } // 부모 찾기
void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; }                 // 정점 합치기 (작은 값이 근 노드로)

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int v, e; // 정점의 개수 V(1 ≤ V ≤ 10k), 간선의 개수 E(1 ≤ E ≤ 100k)
    cin >> v >> e;

    vector<P> arr(e);
    for (auto &[a, b, c] : arr)
        cin >> a >> b >> c;
    sort(arr.begin(), arr.end(), cmp); // 가중치를 기준으로 오름차순 정렬

    for (int i = 1; i <= v; i++)
        parent[i] = i;

    int ans = 0;
    for (auto [a, b, c] : arr)
    {
        a = find_parent(a), b = find_parent(b);
        if (a != b) // 부모가 다른 경우 (= 서로 이어지지 않은 상태)
            union_parent(a, b), ans += c;
    }
    cout << ans;
}

// 7 11
// 1 7 12
// 1 4 28
// 1 2 67
// 1 5 17
// 2 4 24
// 2 5 62
// 3 5 20
// 3 6 37
// 4 7 13
// 5 6 45
// 5 7 73
// ans: 123