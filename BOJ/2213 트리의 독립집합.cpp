// 2213 트리의 독립집합
// https://www.acmicpc.net/problem/2213
/*
    트리 + DP (2,784KB, 4ms)
    시간 복잡도: ?
    풀이)
    - dp[i][true/false] = k일 때, 서브트리를 포함한 i번째 정점까지 i의 값을 포함한/포함하지 않은 독립집합의 최대 크기.
    - dp[i]의 기본 값은, true는 현재 값을 추가하는 것이므로 w[i]를, false는 추가하지 않는 것이므로 0으로 한다.
     - 현재 정점을 포함(true)할 경우, 하위 노드의 값은 포함하면 안 된다.
     그러므로, dp[이전 노드][false]를 dp[현재 노드][true]에 더한다.
     - 현재 정점을 포함하지 않을(false) 경우, 하위 노드의 값은 포함하거나 하지 않아도 된다.
     즉, 둘 중에 더 큰 값을 추가해주면 되므로 max(dp[이전 노드][true], dp[이전 노드][false])를 dp[현재 노드][false]에 더한다.
    - 독립집합에 속하는 정점은 구한 dp와 백트래킹을 이용하여 구한다.
    정점을 저장하기 위한 벡터 v와 탐색 여부를 저장할 visited를 선언.
    - 백트래킹은, 현재 탐색 중인 정점 cur이 dp[cur]에 포함되어 있는지를 확인해준다.
    cur가 포함된 값인 dp[cur][ON]이 포함되지 않은 값인 dp[cur][OFF]보다 클 경우, 포함된 경우이다.
    만약 포함되어 있으면, 정점 cur는 독립집합에 포함된 정점이므로 v에 저장해주며 visited[cur]의 값을 true로 만든다. (이는, 다음 노드 next를 탐색할 때 사용한다.)
    만약 next의 상위 노드인 cur가 독립집합에 포함됐을 경우, 즉 visited[cur] == true일 경우 next는 인접한 정점이므로 포함되어서는 안 된다.
    그러므로 next와 이어진 다음 정점을 탐색한다.
    etc.) 점화식 설명이 어려운듯
    참고)
    - 백트래킹: https://www.acmicpc.net/board/view/52196
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10'003
#define OFF 0
#define ON 1
#define st 1

int n;      // 정점의 수 n(1 ≤ n ≤ 10,000)
int w[MAX]; // 정점의 가중치(1 ≤ w ≤ 10,000)
vector<int> g[MAX];
int dp[MAX][2];

void dfs(int cur = st, int dad = -1)
{
    dp[cur][ON] = w[cur];
    dp[cur][OFF] = 0;

    for (const auto &next : g[cur])
    {
        if (next == dad)
            continue;

        dfs(next, cur);

        dp[cur][ON] += dp[next][OFF];
        dp[cur][OFF] += max(dp[next][OFF], dp[next][ON]);
    }
}

vector<int> p;
bool visited[MAX];
void back_tracking(int cur = st, int dad = -1)
{
    if (!visited[dad] && dp[cur][ON] >= dp[cur][OFF]) // 인접한 노드가 추가됐는지 확인 && 현재 노드가 추가됐는가
        visited[cur] = true, p.push_back(cur);

    for (int next : g[cur])
    {
        if (next == dad)
            continue;
        back_tracking(next, cur);
    }
}

int main()
{
    FAST_IO;

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b), g[b].push_back(a);
    }

    dfs();
    back_tracking();

    sort(p.begin(), p.end());

    cout << max(dp[1][OFF], dp[1][ON]) << endl;
    for (const auto &i : p)
        cout << i << ' ';
}

// 6
// 10 1 1 1 10 10
// 1 2
// 2 3
// 3 4
// 4 5
// 3 6
// ans:
// 30
// 1 5 6