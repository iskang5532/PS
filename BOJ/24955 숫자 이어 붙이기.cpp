// 2022-06-18
// 24955 숫자 이어 붙이기
// https://www.acmicpc.net/problem/24955
/*
    BFS (2,184KB, 112ms)
    시간 복잡도: O(QN)
    풀이)
    - BFS를 이용하여 인접한 집을 거쳐 도착지까지 감.
    - i번째 집까지 놀이를 수행한 결과를 저장할 dist[]. (dist[i] = k일 때, 집 st에서 집 i까지의 놀이 결과는 k)
    - 두 정수를 붙이는 작업은 문자열로 변환하여 붙인 후, 다시 정수로 변환.
    변환된 정수는 int형의 범위를 넘으므로 주의해야 하며, ll 또한 넘음에 주의.
    - ull로 변환된 문자열의 나머지 연산을 한 값을 dist[]에 저장.
    etc.)
    - ll은 10^19보다 작음
    - 이런 종류의 문제를 풀 떄마다 st와 ed를 -1씩 해줘야 함을 항상 까먹는듯
    참고)
    - 시간복잡도: https://book.acmicpc.net/contest/795
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
#define endl "\n"
#define MAX 1'003
#define MOD 1'000'000'007

int a[MAX];           // 집 대문에 쓰여 있는 수 (1 ≤ a[i] ≤ 10^9)
vector<int> adj[MAX]; // adj[st] = {ed1, ed2}일 때, st에서 ed1과 ed2로 갈 수 있음

int get_dist(int cur, int next) { return stoull((to_string(cur) + to_string(next))) % MOD; }

int bfs(int st, int ed)
{
    queue<int> q;
    q.push(st);
    int dist[MAX]{}; // dist[i] = k일 때, 집 st에서 집 i까지의 놀이 결과는 k
    dist[st] = a[st];

    while (q.size())
    {
        int cur = q.front();
        q.pop();

        for (int next : adj[cur])
            if (!dist[next])
            {
                q.push(next);
                dist[next] = get_dist(dist[cur], a[next]);

                if (next == ed)
                    return dist[ed];
            }
    }

    return dist[ed];
}

int main()
{
    FAST_IO;

    int n, q; // 집의 개수 n(2 ≤ n ≤ 1k), 놀이 횟수 q(1 ≤ q ≤ 1k)
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n - 1; i++)
    {
        int st, ed;
        cin >> st >> ed;
        adj[st - 1].push_back(ed - 1), adj[ed - 1].push_back(st - 1);
    }
    for (int i = 0; i < q; i++)
    {
        int st, ed;
        cin >> st >> ed;

        cout << bfs(st - 1, ed - 1) << endl;
    }
}