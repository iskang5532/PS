// 2022-05-07
// 등산코스 정하기 (코딩테스트 연습 > 2022 KAKAO TECH INTERNSHIP > 등산코스 정하기)
// https://school.programmers.co.kr/learn/courses/30/lessons/118669
/*
    BFS
    시간 복잡도: ?
    풀이)
    - 출입구 - 산봉우리 - 출입구이 아닌, 산봉우리 - 출입구를 구함.
    산봉우리에서 시작점까지의 시간은 시작점에서 산봉우리의 시간과 동일하다.
    - bfs를 이용하여 각 산봉우리에서 시작점까지의 시간을 구함.
    - 각 위치까지의 시간을 저장할 dist[], 정답이 될 출입구 번호를 저장할 ans, 최소 시간을 저장할 mn.
    - 이 문제는 이동 간 거리나 시간의 합이 아닌, 이동하면서 걸린 시간 중 최댓값을 저장해야 하는 문제이다.
    그러므로, 이동 간에 이전에 구한 시간과 비교하며 값을 저장한다. (= max(t, _t))
    - 탐색을 중단해야 하는 경우 (= 다른 위치로 이동해야 하는 경우; 더 이상 볼 필요 없을 경우)
    - 현재까지의 시간 t가 mn보다 클 경우
    - 현재까지의 시간 t가 다음 위치 next까지의 시간 dist[next]보다 클 경우
    - 다음 위치가 산봉우리인 경우 (이 경우, 산봉우리인지를 dist에 표시하였을 경우 제외해도 됨. 그러나 이 풀이에서는 없음)
    - 출입구에 도달했을 경우, 저장한 시간과 이전에 구한 최소 시간 mn과 비교 후 출입구를st를 ans에, 시간을 mn에 저장한다.
    헷갈리지 말아야 할 점은, 이동 간 시간은 최댓값을 저장해야 하지만, 출력할 답은 그 중에서 가장 작은 값이어야 한다.
    만약 두 수가 같은 경우, ans에 더 작은 출입구를 저장한다.
    참고)
    - 해설: https://tech.kakao.com/2022/07/13/2022-coding-test-summer-internship/
 */

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
#define INF 0x3f3f3f3f
#define MAX 50'003 // max n

vector<pii> path[MAX];
bool ed[MAX], peak[MAX]; // ed[i] = true일 경우, i는 출입구, peak[i] = true일 경우, i는 산봉우리

void bfs(const int st, int &ans, int &mn)
{
    queue<pii> q;
    q.push({st, 0});

    int dist[MAX]; // dist[i] = k일 때, i까지의 시간은 k
    fill(dist, dist + MAX, INF);

    while (q.size())
    {
        auto [cur, t] = q.front(); // {현재 위치, cur까지의 최대 시간}
        q.pop();
        for (const auto &[next, _t] : path[cur]) // {다음 위치, cur to next의 시간}
        {
            int nt = max(t, _t); // next까지의 최대 시간
            if (ed[next])
            {
                if (nt < mn) // 이전에 구한 시간보다 짧은 경우
                    ans = st, mn = nt;
                else if (nt == mn) // 이전에 구한 시간과 같은 경우 (= 더 작은 값을 저장)
                    ans = min(ans, st);

                continue;
            }
            if (mn < nt) // cur까지의 최대 시간이 이전에 구한 시간보다 오래 걸리는 경우 (더 볼 필요 없음)
                continue;

            if (nt < dist[next] && !peak[next]) // next까지 시간 갱신이 가능하면서 산봉우리가 아닌 경우 (만약 dist에 산봉우리를 표시했을 경우 제거해도 됨)
                dist[next] = nt, q.push({next, nt});
        }
    }
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits)
{
    for (const auto &v : paths)
        path[v[0]].push_back({v[1], v[2]}), path[v[1]].push_back({v[0], v[2]});
    for (const auto &i : gates)
        ed[i] = true;
    for (const auto &i : summits)
        peak[i] = true;

    int ans = 0, mn = INF;         // {출입구의 번호, intensity의 최솟값}
    for (const auto &st : summits) // 산봉우리에서부터 출발
        bfs(st, ans, mn);

    return {ans, mn};
}

// template <typename T>
// void print_ans(const vector<T> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << '\n';
// }
// int main()
// {
//     print_ans(solution(6, {{1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4}, {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}},
//                        {1, 3}, {5})); //{5, 3}
//     print_ans(solution(7, {{1, 4, 4}, {1, 6, 1}, {1, 7, 3}, {2, 5, 2}, {3, 7, 4}, {5, 6, 6}},
//                        {1}, {2, 3, 4})); //{3, 4}
//     print_ans(solution(7, {{1, 2, 5}, {1, 4, 1}, {2, 3, 1}, {2, 6, 7}, {4, 5, 1}, {5, 6, 1}, {6, 7, 1}},
//                        {3, 7}, {1, 5})); //{5, 1}
//     print_ans(solution(5, {{1, 3, 10}, {1, 4, 20}, {2, 3, 4}, {2, 4, 6}, {3, 5, 20}, {4, 5, 6}},
//                        {1, 2}, {5})); //{5, 6}
// }