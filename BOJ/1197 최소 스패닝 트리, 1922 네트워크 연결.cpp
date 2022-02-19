// 1197 최소 스패닝 트리, 1922 네트워크 연결
// https://boj.kr/1197 https://boj.kr/1922
/*
    유니온 파인드, MST(최소 신장 트리, 크루스칼 알고리즘)
    시간 복잡도: ?
    풀이)
    - 가중치를 기준으로 오름차순 정렬.
    현재 두 정점의 부모가 서로 다른 경우, 서로 연결해주며 가중치를 저장함.
    현재 두 정점의 부모가 서로 같은 경우, 연결되어 있는 것이므로 다음 원소를 확인. (= 앞서 연결됨. 이전 가중치는 현재 가중치보다 작음)
    참고)
    - 이론: https://gmlwjd9405.github.io/2018/08/28/algorithm-mst.html
    - 이론 및 코드: https://m.blog.naver.com/ndb796/221230994142
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 10000 + 1 // 정점의 최대 개수

struct P
{
    int a, b, c;
    friend bool operator<(const P &p1, const P &p2) { return p1.c < p2.c; } // 가중치를 기준으로 오름차순 정렬
};

struct Union_Find
{
    int parent[MAX];
    Union_Find() { iota(parent, parent + MAX, 0); }

    int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a > b ? parent[a] = b : parent[b] = a; } // 더 작은 값이 부모가 되도록
};

int main()
{
    FAST_IO;

    int V, E;
    cin >> V >> E;

    vector<P> v;
    for (int i = 0; i < E; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a != b)
            v.push_back({a, b, c});
    }
    sort(v.begin(), v.end()); // 가중치를 기준으로 오름차순 정렬

    int ans = 0;
    Union_Find uf;
    for (int i = 0; i < v.size(); i++)
    {
        auto [a, b, c] = v[i];
        a = uf.find_parent(a), b = uf.find_parent(b);
        if (a != b)
            uf.union_parent(a, b), ans += c;
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