/* 
 * 1238 파티
 * 다익스트라
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1238
 * etc.) 변형된 코드(line 88, 90)가 살짝 헷갈림
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define endl "\n"
#define INF 987654321
#define MAX_N 1000

int V, E, X; // 정점의 개수, 간선의 개수, 중심지

struct Link // 간선의 정보들 (도착지 및 도착지까지의 비용)
{
    int end_vertex, cost; // 도착지, 비용
};

struct _greater
{
    bool operator()(Link a, Link b)
    {
        return a.cost > b.cost; // 비용 오름차순 (비용이 낮은 값을 먼저 탐색하도록 함)
    }
};

vector<int> Dijkstra(const vector<Link> arr[])
{
    vector<int> dist(V, INF); // 정점 V개만큼 INF로 초기화
    dist[X] = 0;              // 기준은 X이며, 자기 자신까지의 거리는 0

    priority_queue<Link, vector<Link>, _greater> pq;
    Link start = {X, 0}; // 시작점
    pq.push(start);

    while (!pq.empty())
    {
        int curr_vertex = pq.top().end_vertex; // 현재 위치
        int curr_cost = pq.top().cost;         //현재 위치까지의 비용
        pq.pop();

        for (int i = 0; i < arr[curr_vertex].size(); i++) // auto로
        {
            int next_vertex = arr[curr_vertex][i].end_vertex; // i번쨰 다음 위치 (현재 위치와 인접)
            int next_cost = arr[curr_vertex][i].cost;         // 다음 위치까지의 비용

            if (dist[next_vertex] > curr_cost + next_cost) // 만약 저장된 비용이 더 큰 경우 (= 갱신 가능)
            {
                dist[next_vertex] = curr_cost + next_cost; // 갱신
                pq.push({next_vertex, dist[next_vertex]}); // 탐색을 추가
            }
        }
    }

    return dist; // 구한 최단 거리를 반환
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> V >> E >> X; // 1 <= 1k, 1 <= 10k
    X--;

    vector<Link> arr[MAX_N];     // i → X
    vector<Link> ret_arr[MAX_N]; // X → i
    for (int i = 0; i < E; i++)
    {
        int start_vertex, end_vertex, cost;
        cin >> start_vertex >> end_vertex >> cost;

        // 밑의 두 줄은 쪼끔 복잡함.
        // 기존 코드는 i에서 출발하여 ~V까지(여러 개)의 최단 거리를 구하기 위함이었음. (= ret_arr)
        // 이는 역으로 생각해본다면, 단방향 링크들을 전부 뒤집게 될 시 X에서 i로 가는 최단 거리를 구할 수 있게 된다. (= arr)

        // 기존 코드: 기준 노드에서부터 여러 개의 정점 노드까지의 최단 거리
        // 변형 코드: 기준 노드까지 가는 여러 가지 노드들 각각의 최단 거리

        // 되돌아가는 거리. 즉, i까지의 거리(X → i)를 구하기 위한 값을 저장
        ret_arr[start_vertex - 1].push_back({end_vertex - 1, cost}); // 기존의 다익스트라 문제 풀이와 같은 코드
        // X까지의 거리(i → X)를 구하기 위한 값을 저장 (단방향 링크들을 뒤집어 i로부터 ~V까지의 최단 거리가 아닌, i까지 ~V들의 최단 거리를 구하게 함)
        arr[end_vertex - 1].push_back({start_vertex - 1, cost});
    }

    vector<int> dist = Dijkstra(arr);         // i → X
    vector<int> ret_dist = Dijkstra(ret_arr); // X → i

    int answer = 0;
    for (int i = 0; i < V; i++)
        answer = max(answer, dist[i] + ret_dist[i]); // (i → X) + (X → i)값들 중 최댓값을 찾음

    cout << answer;
}