// 2022-09-07
// 18231 파괴된 도시
// https://www.acmicpc.net/problem/18231
/*
    그리디 (3,25KB, 20ms)
    시간 복잡도: ?
    풀이)
    - 도시의 인접한 관계를 입력받아 저장할 path[].
    - 파괴된 도시의 정보를 저장할 p[].
    - 해당 도시를 파괴하였는지를 저장할 used[], 폭탄을 떨어뜨린 도시를 저장할 ans.
    - 1번 도시부터 n번 도시까지 탐색.
    만약 i번 도시가 파괴되었으면서 인접한 모든 도시가 파괴되었을 경우, 해당 도시에 폭탄을 떨어뜨림. (ans에 추가)
    폭탄이 떨어졌으므로 해당 도시 및 인접한 도시를 파괴됨. (used 갱신)
    - 파괴된 도시 p와 used를 비교.
    만약 두 값이 다를 경우, -1을 출력.
    만약 두 값이 모두 같을 경우, ans의 크기와 저장된 값을 출력.
    etc.) 쉬운듯 어려운듯한 문제
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 2'003 // max n

vector<int> path[MAX]; // path[i] = {a, b}일 때, 도시 i와 인접한 도시는 a, b

bool isValid(bool p[], int cur) // 파괴시켜야 하는 도시인가
{
    for (const auto &next : path[cur])
        if (!p[next]) // 인접한 도시가 파괴되지 않았을 경우
            return false;

    return true;
}

bool isValid(bool p[], bool boom[]) // 파괴된 도시들이 일치하는가
{
    for (int i = 0; i < MAX; i++)
        if (p[i] != boom[i])
            return false;

    return true;
}

int main()
{
    FAST_IO;

    int n, m; // 도시의 개수 N(1 ≤ N ≤ 2,000), 도로의 개수 M(1 ≤ M ≤ min(N×(N-1)/2, 100,000))
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        path[a].push_back(b), path[b].push_back(a);
    }

    int k; // 파괴된 도시의 개수 K(1 ≤ K ≤ N)
    cin >> k;
    bool p[MAX]{}; // boom[i] = true일 경우, i번 도시는 파괴됨
    for (int i = 0; i < k; i++)
    {
        int t; // 파괴된 도시의 번호 Pi(1 ≤ Pi ≤ N)
        cin >> t;
        p[t] = true;
    }

    vector<int> ans;
    bool boom[MAX]{}; // 임의로 파괴할 도시 (boom[i] = true일 경우, i번 도시는 파괴됨)
    for (int cur = 1; cur <= n; cur++)
        if (p[cur] && (path[cur].empty() || isValid(p, cur))) // 파괴된 도시이면서 폭탄을 떨어뜨려도 되는가
        {
            ans.push_back(cur), boom[cur] = true;
            for (const auto &next : path[cur]) // 인접한 도시 폭발
                boom[next] = true;
        }

    if (isValid(p, boom)) // 파괴된 도시들이 일치하는가
    {
        cout << ans.size() << endl;
        for (const auto &i : ans)
            cout << i << ' ';
    }
    else
        cout << -1;
}