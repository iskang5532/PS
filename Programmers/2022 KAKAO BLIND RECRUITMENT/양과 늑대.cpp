// 양과 늑대 (코딩테스트 연습 > 2022 KAKAO BLIND RECRUITMENT > 양과 늑대)
// https://programmers.co.kr/learn/courses/30/lessons/92343
/*
    BFS (완전 탐색)
    시간 복잡도: ?
    풀이)
    - edges의 원소를 이용해 정점과 정점을 양방향으로 이어 path에 저장.
    - 각 정점의 방문 횟수를 저장할 cycle. (만약 일정 횟수 이상이 될 시, 더 이상 방문할 수 없음.)
    - 시작 정점 0에서부터 출발해 정점에서 정점까지 조건에 부합한 모든 경우의 수를 탐색.
    - 큐에는 {현재 위치, 방문 기록, 모은 양의 수, 모든 늑대의 수}가 저장됨.
    방문 기록 idx는 비트를 이용함. 만약 idx & 1 << i == true일 경우, i번째 정점의 동물을 모음. (이후 재방문 시 다시 모으지 않음)
    - 다음 정점으로 이동 시, 모인 늑대의 수가 양의 수 이상일 경우, 이동하지 않음.
    또한, 다음 정점에 도달한 횟수가 일정 횟수 이상일 경우, 이동하지 않음. (사이클의 최대치?)
    - 다음 정점으로 이동할 수 있을 시, idx에 방문 처리 및 cycle++, 양의 수 갱신.
    etc.) SPFA?
    - cycle은 왜 17^5까지인가?
    참고)
    - 문제해설: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
 */

#include <bits/stdc++.h>

using namespace std;
#define MAX 21
#define SHEEP 0
#define WOLF 1

struct P
{
    int pos, idx, sheep, wolf; // 위치, 방문 기록, 모은 양의 수, 모은 늑대의 수
    // idx & 1 << i == true일 때, i번째 정점을 방문하여 동물을 모은 적이 있음
};

vector<int> info, path[MAX];
int cycle[MAX]; // cycle[i] = k일 떄, i번째 정점의 방문 횟수는 k

int bfs(int st = 0)
{
    int ret = 1;

    queue<P> q;
    q.push({st, 1 << st, info[st] == SHEEP, info[st] == WOLF});
    cycle[st]++;

    while (q.size())
    {
        auto [cur, idx, sheep, wolf] = q.front();
        q.pop();

        for (int next : path[cur])
        {
            int next_sheep = sheep, next_wolf = wolf;
            if (!(idx & 1 << next)) // 방문한 적이 없는 경우, 해당 정점의 동물을 모음
                info[next] == SHEEP ? next_sheep++ : next_wolf++;
            if (next_wolf >= next_sheep || cycle[next] > pow(17, 5)) // 늑대의 수가 양의 수 이상이 됨 || 일정 횟수 이상을 방문
                continue;

            int next_idx = idx | 1 << next; // 다음 정점을 방문처리
            q.push({next, next_idx, next_sheep, next_wolf}), cycle[next]++;
            ret = max(ret, next_sheep);
        }
    }

    return ret;
}

int solution(vector<int> _info, vector<vector<int>> edges)
{
    info = move(_info);
    for (const auto &edge : edges)
    {
        int a = edge[0], b = edge[1];
        path[a].push_back(b), path[b].push_back(a);
    }

    return bfs();
}

// int main()
// {
//     cout << solution({0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1}, {{0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9}}) << '\n'; // 5
//     cout << solution({0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0}, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {6, 9}, {9, 10}}) << '\n';             // 5
//     cout << solution({0, 1}, {{0, 1}}) << '\n';                                                                                                                 // 1
// }