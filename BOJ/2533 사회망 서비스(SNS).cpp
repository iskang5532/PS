// 2533 사회망 서비스(SNS)
// https://www.acmicpc.net/problem/2533
/*
    트리 + DP (73,616KB, 796ms)
    시간 복잡도: ?
    풀이)
    - dp를 이용해 현재 정점 cur와 정점의 서브트리의 얼리어답터 최솟값을 저장함.
    - 근 노드는 1로 고정. (편의성)
    - 모든 노드를 탐색하며 값을 구함.
    1. 노드는 다음 노드의 리프 노드를 우선적으로 탐색. (모든 리프 노드를 우선적으로 탐색하는 것은 아님)
    2. 리프 노드일 경우, dp의 초깃값을 저장. (people = 0, early = 1)
    3. 리프 노드의 상위 노드, 즉 부모 노드에 리프 노드의 초깃값을 더함.
    4. 해당 부모 노드에 다른 노드가 있는지 탐색.
    - 노드의 마지막 탐색은 근 노드가 된다. 즉, dp의 최종값은 근 노드에 업데이트 되므로, dp[1]의 값을 사용한다.
    근 노드가 얼리어답터일 경우와 아닐 경우가 있으므로, 두 가지 경우 중 더 작은 값을 출력해준다.
    etc.) [i-2]의 값을 모르므로 1차원 배열이 아닌 2차원 배열을 이용하여 [i-2]의 값을 [i-1]에 저장하여 [i]에서 사용.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222097529937
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000'003
#define PEOPLE 0
#define EARLY 1

vector<int> g[MAX];
int cnt[MAX][2]; // cnt[i][state] = k일 경우, i번 정점의 상태가 state일 때, 정점 i 및 서브트리 얼리어답터의 최솟값

void dfs(int cur, int dad)
{
    cnt[cur][PEOPLE] = 0, cnt[cur][EARLY] = 1;

    for (int next : g[cur]) // 정확히는 현재 노드의 자식 노드
    {
        if (next == dad)
            continue;

        dfs(next, cur);

        cnt[cur][PEOPLE] += cnt[next][EARLY];                        // 현재 정점이 일반인인 경우, 자식 노드는 얼리어답터여야 한다.
        cnt[cur][EARLY] += min(cnt[next][EARLY], cnt[next][PEOPLE]); // 현재 정점이 얼리어답터일 경우, 최솟값을 필요로 함 (이전 상태는 얼리어답터가 아니어도 됨)
    }
}

int main()
{
    FAST_IO;

    int n; // 정점 개수 (2 ≤ N ≤ 1,000,000)
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b), g[b].push_back(a);
    }

    dfs(1, -1);

    cout << min(cnt[1][PEOPLE], cnt[1][EARLY]);
}