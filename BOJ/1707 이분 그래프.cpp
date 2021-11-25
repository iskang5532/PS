/*
    1707 이분 그래프
    BFS (5,856KB, 296ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1707
    풀이)
    - 정점을 둘로 분할하였을 때, 각각 '방'이라고 생각했으며, 번호는 0번과 1번이라 생각.
    각 정점의 방 번호는 visited에 저장.
    - 각 정점과 인접한 정점의 반 번호는 서로 달라야 함. (2번과 5번이 인접할 시 2번의 방 번호는 0, 5번의 방 번호는 1과 같이)
    - 정점으로 만들어진 간선은 서로 이어지지 않았을 수도 있으므로 모든 정점에 대해 조사.
    - 각 정점을 조사하며, 현재 정점과 인접한 정점은 현재 정점의 방 번호와 반대되는 방 번호를 부여한 후, 큐에 넣어 다음 인접한 정점이 있는지 확인.
    만약 정점의 방 번호가 부여되지 않았을 경우, 처음 탐색하는 간선이 되며 이 경우 첫 정점의 방 번호는 0번으로 지정해줬음.
    또한, 인접한 정점의 방 번호가 부여되었는데, 현재 정점의 방 번호와 같을 시 이분 그래프가 아니게 되므로 false를 반환시켜 NO를 출력.
    - 인접한 정점 간 방 번호가 같은 상황이 없을 시, true를 반환하여 YES를 출력.
    etc.)
    - 예전에 풀지 못했던 문제를 해결해서 기부니가 좋았음.
    참고)
    - 이분 그래프의 정의: https://gmlwjd9405.github.io/2018/08/23/algorithm-bipartite-graph.html
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890

int v, e; // 정점의 개수 v(1 ≤ v ≤ 200k), 간선의 개수 e(1 ≤ e ≤ 20k)

bool isValid(const vector<vector<int>> &arr) // bfs
{
    vector<int> visited(v + 1, INF); // 정점의 방 번호를 저장 (visited[3] = 1일 경우, 3번 정점의 방 번호는 1)

    queue<int> q;
    for (int i = 1; i <= v; i++) // 모든 정점 훑기
    {
        q.push(i);
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            if (visited[curr] == INF) // 현재 정점에 도달한 적이 없는 경우 (= 이 경우 새로운 간선을 탐색중인 것. 첫 번째 정점의 방은 0으로 맞춰줌)
                visited[curr] = 0;

            for (const auto &next : arr[curr]) // 현재 정점과 인접한 정점
            {
                if (visited[next] == INF) // 인접한 정점에 도달한 적이 없는 경우 (= 배정한 적이 없음)
                {
                    visited[next] = visited[curr] ^ 1; // 현재 정점과 반대되는 방을 배정
                    q.push(next);
                }
                else if (visited[next] == visited[curr]) // 인접한 정점의 방이 현재 정점과 같은 경우 (= 이분 그래프 아님)
                    return false;
            }
        }
    }

    return true;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        cin >> v >> e;

        vector<vector<int>> arr(v + 1);
        for (int i = 0; i < e; i++)
        {
            int a, b;
            cin >> a >> b;
            arr[a].push_back(b), arr[b].push_back(a);
        }

        isValid(arr) ? cout << "YES" << endl : cout << "NO" << endl;
    }
}

// 1
// 9 6
// 1 2
// 3 1
// 1 9
// 4 5
// 6 8
// 7 8
// ans: YES