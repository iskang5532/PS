/*
    배달 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 배달)
    다익스트라 (Dijkstra)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12978/solution_groups?language=cpp&type=all
    etc.) 기본적인 다익스트라 문제인 듯 싶음.
    - 입력된 값은 양방향임.
    - 입력된 값을 [시작점] = {도착점, 거리}와 같이 arr에 저장함.
    - 시작점부터 다익스트라 시작.
     - 현재 위치에서 갈 수 있는 다음 위치를 모두 탐색.
     이전에 구한 다음 위치까지의 최소 거리보다 현재 위치까지의 거리 + 다음 위치까지의 거리가 짧은 경우 갱신.
     만약 값이 갱신되었을 경우, 다음 위치까지의 거리를 이용하여 구한 거리가 있을 수 있으므로 그 거리들을 갱신시켜주기 위해 pq에 넣음.
 */

#include <string>
#include <queue>

using namespace std;

#define INF 1234567890
typedef long long ll;

struct pii
{
    int vertex, dist; // 다음 위치, 거리
};

// 시작점 1에서부터 각 위치까지의 최단 거리 구하기
vector<int> dijkstra(const vector<pii> arr[], int n)
{

    vector<int> dist(n + 1, INF); // dist[i]일 때, 시작점 1부터 도착점 i까지의 거리
    dist[1] = 0;                  // start

    queue<pii> pq;
    pq.push(pii{1, 0}); // start

    while (!pq.empty())
    {
        auto [curr_vertex, curr_dist] = pq.front();
        pq.pop();

        for (const auto &elem : arr[curr_vertex])
        {
            auto [next_vertex, next_dist] = elem;

            if (dist[next_vertex] > dist[curr_vertex] + next_dist)
            {
                dist[next_vertex] = dist[curr_vertex] + next_dist;
                pq.push(pii{next_vertex, dist[next_vertex]});
            }
        }
    }
    return dist;
}

int solution(int N, vector<vector<int>> road, int K)
{
    int answer = 0;

    vector<pii> arr[N + 1]; // arr[a] = {b, c}일 때, a에서 b까지의 거리는 c
    for (const auto &elem : road)
    {
        int a = elem[0], b = elem[1], c = elem[2];
        arr[a].push_back({b, c}), arr[b].push_back({a, c}); // 양방향
    }

    vector<int> dist = dijkstra(arr, N); // dist[i]일 때, 시작점 1부터 도착점 i까지의 거리
    for (int i = 1; i <= N; i++)
        if (dist[i] <= K)
            answer++;

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution(5,
//                      {{1, 2, 1},
//                       {2, 3, 3},
//                       {5, 2, 2},
//                       {1, 4, 2},
//                       {5, 3, 1},
//                       {5, 4, 2}},
//                      3)
//          << endl; // 4
//     cout << solution(6,
//                      {{1, 2, 1},
//                       {1, 3, 2},
//                       {2, 3, 2},
//                       {3, 4, 3},
//                       {3, 5, 2},
//                       {3, 5, 3},
//                       {5, 6, 1}},
//                      4)
//          << endl; // 4
// }