/* 
 * 11779 최소비용 구하기 2
 * 다익스트라
 * 시간 복잡도: O(n^3)
 * 문제: https://www.acmicpc.net/problem/11779
 * etc.) 72번 줄에서의 while문에서 조건을 idx != 0으로 두었을 때 계속 메모리 초과가 나서 고생함. why?
 * 추가로, priority_queue가 아닌 queue를 사용했는데 상관 없었음. 오히려 빠르고 메모리가 절약됨. why?
 */

#include <iostream>
// #include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define endl "\n"
#define MAX 1000 + 1
#define INF 987'654'321

typedef pair<int, int> pii;

pair<vector<int>, vector<int>> dijkstra(const vector<pii> arr[], const int n, const int start)
{
    vector<int> dist(n + 1, INF); // 출발점 기준 각 지점까지의 비용
    vector<int> prev(n + 1, 0);   // 출발점에서부터 도착점까지 도달하기까지 방문한 지점들 저장
    queue<pii> q;                 // pq가 아니여도 되는가?
    q.push(pii{start, 0});
    while (!q.empty())
    {
        auto [pos, cost] = q.front();
        q.pop();

        if (dist[pos] < cost) // 현재 비용이 pos까지의 비용이 더 작은 경우 (= 갱신할 필요가 없는 경우)
            continue;

        for (auto [next_pos, next_cost] : arr[pos]) // 현재 지점(pos)에서부터 이동할 수 있는 지점과 비용을 뽑음
            if (cost + next_cost < dist[next_pos])  // 현재까지의 비용 및 다음 거리까지의 비용이 더 작은 경우 (= 갱신 가능)
            {
                dist[next_pos] = cost + next_cost;
                prev[next_pos] = pos; // 다음 지점의 이전 지점(= pos) 저장
                q.push(pii{next_pos, dist[next_pos]});
            }
    }

    return {dist, prev};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 1 <= n <= 1k, 1 <= m <= 100k
    cin >> n >> m;

    vector<pii> arr[MAX];
    for (int i = 0; i < m; i++)
    {
        int l, r, c; // 0 <= c <= 100k
        cin >> l >> r >> c;

        arr[l].push_back(pii{r, c});
    }
    int start, end;
    cin >> start >> end;

    auto [dist, prev] = dijkstra(arr, n, start); // 출발점 기준 각 지점까지의 비용 dist와 도착점까지의 방문 지점을 저장한 prev

    vector<int> answer;  // 방문한 지점들을 저장할 공간
    int idx = end;       // 역추적을 위해 시작 지점은 도착점으로
    while (idx != start) // 출발점이 될 때까지
    {
        answer.push_back(idx); // 위치를 넣어 줌
        idx = prev[idx];       // 현재 위치의 이전 지점
    }
    answer.push_back(idx);                 // 시작점을 넣어 줌
    reverse(answer.begin(), answer.end()); // 도착점부터 시작점까지 저장되어 있으니, 순서룰 바꿔줌

    cout << dist[end] << endl;      // 도착점까지의 비용
    cout << answer.size() << endl;  // 시작점부터 도착점까지 방문한 지점의 개수
    for (const auto &elem : answer) // 시작점부터 도착점까지 방문한 지점들을 출력
        cout << elem << " ";
}

/* the problem..
    vector<int> answer{end};
    int idx = prev[end];
    while (idx != 0)
    {
        answer.push_back(idx);
        idx = prev[idx];
    }
    // answer.push_back(idx);
*/