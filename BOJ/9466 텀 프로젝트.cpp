/*
    9466 텀 프로젝트
    DFS (2,800KB,540 ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/9466
    풀이)
    - 팀에 속하지 않는 인원을 구하기 위해 팀에 속한 인원을 구해줌.
    - 학생을 정점으로 생각하며, 각 정점의 상위 정점을 parent 배열에 저장.
    - 1번부터 n번까지 모든 정점을 탐색하여, 팀, 즉 사이클을 이루고 있는지 확인. (이 값은 dfs에서 start의 값이 됨.)
    - visited 배열을 이용하여 각 정점을 탐색한 적이 있는지 확인하며 현재 사이클의 값이라는 의미를 가짐.
    - [3 1 4 3], 1번 정점부터 탐색할 경우 (start == 1)
    1) 1번 정점에 방문한 적이 없으므로 visited[1]에 start의 값인 1을 넣음.
    이후 parent[1](= 3)을 가지고 dfs. (curr == 3)
    2) 3번 정점에 방문한 적이 없으므로 visiteid[3] = 1.
    이후 parent[3](= 4)를 가지고 dfs. (curr == 4)
    3) 4번 정점에 방문한 적이 없으므로 visited[4] = 1.
    이후 parent[4](= 3)를 가지고 dfs. (curr == 3)
    4) 3번 정점에 방문한 적이 있음. (이 순간, 사이클이 생성된 것을 알 수 있음.)
    - curr의 값이 사이클의 시작점으로 생각함.
    - 사이클에 포함된 정점의 개수를 확인.
    curr에서부터 시작하여 curr로 돌아올 때까지 값의 개수를 확인한다. (= curr != parent[curr])
    이떄, parent[curr] == curr일 수도 있으므로 curr부터 세어준 후 시작한다. (예제의 2번 입력과 같은 경우)
    5) 1번 정점이 끝났으므로 2번 정점을 이용해 1)부터 시작하며, 최종적으로 나온 값인 cnt의 값을 이용해 팀에 속하지 못한 인원을 구함.
    etc.) 유니온 파인드를 이용한 듯한 문제. 어려웠으나 재밌었던 문제.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222075625376
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100'000 + 1

int parent[MAX], visited[MAX];
int cnt; // 사이클에 속하는 정점의 개수

// start: 시작점, curr: 시작점 start에서부터 출발한 i번째 정점
void dfs(const int start, int curr)
{
    if (!visited[curr]) // 사이클 형성이 안됐거나 방문한 적이 없는 경우
    {
        visited[curr] = start;
        dfs(start, parent[curr]);
    }
    else if (visited[curr] == start) // 사이클이 형성된 경우 (이때, curr가 사이클의 시작점이 됨)
    {
        cnt++;
        int nxt = parent[curr];
        while (nxt != curr) // 한 바퀴 돌아 시작점으로 돌아온 경우
            cnt++, nxt = parent[nxt];
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 학생의 수 n(2 ≤ n ≤ 10^5)
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> parent[i];

        cnt = 0;
        fill(visited, visited + MAX, 0);
        for (int i = 1; i <= n; i++)
            if (!visited[i])
                dfs(i, i);

        cout << n - cnt << endl; // (학생의 수 - 팀에 속한 인원)
    }
}