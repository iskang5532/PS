/*
    1717 집합의 표현
    유니온 파인드 (6,392KB, 36ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1717
    풀이)
    - 입력 시
     - 두 정점이 주어질 경우, 서로 이어줌. (여기서 작은 값을 부모로)
     이때 두 정점의 부모가 같은 경우는 다음 값을 탐색. (이미 연결되어 있음)
    - 출력 시
     - 서로 부모가 같은 경우, 서로 같은 집합. (= YES)
     - 서로 부모가 다른 경우, 서로 다른 집합. (= NO)
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 1000000 + 1 // 값의 최댓값

int parent[MAX];
int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); }
void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; }

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 값의 범위 n(1 ≤ n ≤ 1M), 연산의 개수 m(1 ≤ m ≤ 100k)
    cin >> n >> m;
    for (int i = 0; i <= n; i++)
        parent[i] = i;
    for (int i = 0; i < m; i++) // 0번 정점 포함.
    {
        int cmd, a, b;
        cin >> cmd >> a >> b;
        a = find_parent(a), b = find_parent(b);
        if (cmd == 0 && a != b) // merge
            union_parent(a, b);
        else if (cmd == 1) // find
            a == b ? cout << "YES" << endl : cout << "NO" << endl;
    }
}

// sol.2) 구조체
// 유니온 파인드 (6,392KB, 40ms)
#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

struct Union_Find
{
    int n;
    vector<int> parent;

    Union_Find(int n) // 벡터 초기화
    {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
    int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; }
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 값의 범위 n(1 ≤ n ≤ 1M), 연산의 개수 m(1 ≤ m ≤ 100k)
    cin >> n >> m;

    Union_Find uf(n); // 유니온 파인드 선언
    for (int i = 0; i < m; i++)
    {
        int cmd, a, b;
        cin >> cmd >> a >> b;

        a = uf.find_parent(a), b = uf.find_parent(b);
        if (cmd == 0 && a != b) // merge
            uf.union_parent(a, b);
        else if (cmd == 1) // find
            a == b ? cout << "YES" << endl : cout << "NO" << endl;
    }
}