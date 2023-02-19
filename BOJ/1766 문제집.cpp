// 2023-02-16
// 1766 문제집
// https://www.acmicpc.net/problem/1766
/*
    위상정렬 (4,148KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 입력된 조건을 만족하면서 가능한 쉬운 문제를 우선적으로 출력해야 한다.
    그러므로 쉬운 문제를 먼저 탐색할 수 있도록 우선순위 큐를 사용한다.
    etc.)
    - 다른 식으로 풀다가 WA에 갇힌 문제
    - 기존 문제와 다른 점은 pq를 사용했다는 점.
    pq를 사용함으로 인해 큐에 값을 넣으면서 ret에 값을 넣는게 아닌, 큐에서 빼올 때 값을 추가해야 한다.
    참고)
    - 코드: https://blog.naver.com/jinhan814/222131303518
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 32'003 // max n

int n, m; // 문제의 수 n(1 ≤ n ≤ 32,000), 정보의 개수 m(1 ≤ m ≤ 100,000)
vector<int> adj[MAX];
int in_degree[MAX]; // in_degree[i] = k일 경우, i로 가는 정점의 개수는 k개

vector<int> bfs()
{
    vector<int> ret;

    priority_queue<int, vector<int>, greater<>> pq; // 오름차순
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            pq.push(i);

    while (pq.size())
    {
        int cur = pq.top();
        ret.push_back(cur), pq.pop();
        for (const int &nxt : adj[cur])
            if (--in_degree[nxt] == 0)
                pq.push(nxt);
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1), in_degree[b - 1]++;
    }

    for (const int i : bfs())
        cout << i + 1 << ' ';
}