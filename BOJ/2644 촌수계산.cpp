// 2644 촌수계산
// https://www.acmicpc.net/problem/2644
/*
    BFS (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 번호(= 촌수)에서 다른 번호로 갈 수 있는 경우를 arr에 저장.
    이후 시작점(a 혹은 b)에서부터 도착점(시작점이 아닌 a 혹은 b)까지 갈 수 있는지 확인. (확인하면서 거쳐간 번호마다 +1씩 저장. (= dist))
    또한, 거리는 최단 거리여야 하므로 이전에 구했더라도 현재 구한 값이 더 빠른 경우, 갱신.
    만약 갈 수 없을 경우, -1 출력.
    etc.) 문제를 이해하기가 어려워 그림으로 그려봤더니 쉽게 이해되었음.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX 100 + 1

vector<int> arr[MAX]; // arr[i] = {p, q}일 경우, i에서 p와 q로 갈 수 있음
int bfs(int st, int ed)
{
    vector<int> dist(MAX, INF);
    dist[st] = 0;

    queue<int> q;
    q.push(st);

    while (q.size())
    {
        int curr = q.front();
        q.pop();

        for (const auto &next : arr[curr])
            if (dist[curr] + 1 < dist[next])
            {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
    }

    return dist[ed];
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 전체 사람의 수 (1 ≤ n ≤ 100)
    cin >> n;
    int a, b; // 촌수를 계산할 두 번호
    cin >> a >> b;
    int m; // 부모 자식들 간의 관계의 개수 m
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y; // 부모 자식간의 관계를 나타내는 두 번호 x,y (y의 부모는 x)
        cin >> x >> y;
        arr[x].push_back(y), arr[y].push_back(x);
    }

    int ans = bfs(a, b);
    ans == INF ? cout << -1 : cout << ans;
}