/*
    합승 택시 요금 (코딩테스트 연습 > 2021 KAKAO BLIND RECRUITMENT > 합승 택시 요금)
    다익스트라
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/72413
    풀이)
    - 시작점 s에서 두 사람이 동시에 임의의 정점 i로 이동 시 비용은 한 번만 계산. (같이 이동)
    이는 s에서 목적지까지 바로 가는 것보다 정점 i로 동시에 방문하여 비용을 한 번만 계산한 후, 정점 i에서부터 목적지까지의 비용이 더 저렴할 수 있음.
    그러므로 최소 비용을 [s → 목적지]가 아닌 [s → i → 목적지]를 구해줌. ([s → 목적지]는 [s → s → 목적지]로 구할 수 있음)
    여기서 주의할 점은, 목적지는 2개이므로 다익스트라를 세 번 돌려줘야 한다. ([s → i], [i → a], [i → b])
    또한 i는 n까지이므로 3n번 다익스트라를 돌려줘야 하는데, 이 경우 시간 초과가 나버리며, 시간 초과가 나지 않도록 다른 방식으로 접근해야 한다.
    - [s → i → 목적지]를 구하는 것이 아닌, [목적지 → i] 및 [s → i]를 구해준다.
    이는 앞서 했던 풀이와 똑같이 세 번의 다익스트라를 사용한다. 그러나 정점 i에 대해서는 이미 구해진 값을 사용한다.
    [s → i → a]같은 경우, [s → i], [i → a]가 되며 [i → a]는 결국 [a → i]가 된다. (양방향이므로 가능)
    결국 앞서 구한 세 번의 다익스트라 안에 필요한 모든 정보가 들어가게 되며, 앞서 구현한 코드와는 시간 복잡도가 n만큼 차이가 나게 된다.
    1) 정점 간 간선의 정보를 저장할 arr 선언 및 입력.
    2) [s → i], [a → i], [b → i]의 최단 비용을 구해줌.
    3) 임의의 정점 i를 1부터 n까지 반복문을 돌려 [s → i → 목적지]까지의 최단 비용을 구해줌.
    etc.)
    - 첫 풀이에서는 TLE를 받음. (풀이는 맨 아래 주석 참고).
    - 문제 해결 방법에 1번, 시간 초과 해결에 대해 1번 고비였음. 결국 시간 초과는 구글신에게..
    - 이런 문제는 플로이드-와샬을 사용하는게 가장 무난한갑다.
    참고)
    - 이론: https://ansohxxn.github.io/programmers/120/#-2-%EC%B0%A8-%ED%92%80%EC%9D%B4- (시간 초과에 대한 해결법 참고)
 */

#include <string>
#include <queue>

using namespace std;

#define INF 20'000'000 + 1
#define MAX 200 + 1
typedef pair<int, int> pii;

int solution(int n, int s, int a, int b, vector<vector<int>> fares)
{
    vector<pii> arr[MAX]; // 정점 간 비용을 저장 (arr[1] = {{3, 10}, {2, 99}}일 경우 정점 1에서 3까지의 비용이 10, 2까지의 비용이 99)
    for (const auto &elem : fares)
    {
        int a = elem[0], b = elem[1], c = elem[2];
        arr[a].push_back({b, c}), arr[b].push_back({a, c}); // 양방향
    }

    auto get_cost = [&](int start) -> vector<int> // 시작점에서부터 각 정점까지의 최소 비용을 구함
    {
        queue<int> q;
        q.push({start});
        vector<int> cost(n + 1, INF); // 시작점에서부터 각 정점까지의 최소 비용을 저장
        cost[start] = 0;

        while (!q.empty())
        {
            int curr_v = q.front();
            q.pop();
            for (const auto &[next, next_c] : arr[curr_v]) // 현재 정점에서 갈 수 있는 다음 정점
                if (cost[next] > cost[curr_v] + next_c)    // 만약 현재 정점까지의 비용 + 다음 정점까지의 비용이 더 작은 경우 (= 갱신 가능)
                {
                    cost[next] = cost[curr_v] + next_c;
                    q.push(next); // 현재 정점까지의 비용이 더 적으므로 갈 수 있는 정점들 또한 비용이 적어짐. 그러므로 갱신을 위해 정점 입력
                }
        }

        return cost;
    };

    vector<int> cost_StoI = get_cost(s); // 시작점에서부터 각 정점까지의 최소비용
    vector<int> cost_AtoI = get_cost(a); // 정점 a에서부터 각 정점까지의 최소비용
    vector<int> cost_BtoI = get_cost(b); // 정점 b에서부터 각 정점까지의 최소비용

    int ans = INF;
    for (int i = 1; i <= n; i++) // 방문할 정점
        ans = min(ans, cost_StoI[i] + cost_AtoI[i] + cost_BtoI[i]);
    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution(6, 4, 6, 2, {{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}}) << endl; // 82
//     cout << solution(7, 3, 4, 1, {{5, 7, 9}, {4, 6, 4}, {3, 6, 1}, {3, 2, 3}, {2, 1, 6}}) << endl;                                                     // 14
//     cout << solution(6, 4, 5, 6, {{2, 6, 6}, {6, 3, 7}, {4, 6, 7}, {6, 5, 11}, {2, 5, 12}, {5, 3, 20}, {2, 4, 8}, {4, 3, 9}}) << endl;                 // 18
// }

// TLE (3*n만큼 다익스트라를 돌림)
// int ans = INF;
// for (int i = 1; i <= n; i++)
// {
//     int total = get_cost(s, i);
//     if (total == INF)
//         continue;

//     if (total < ans)
//         total += get_cost(i, a);
//     if (total < ans)
//         total += get_cost(i, b);

//     ans = min(ans, total);
// }