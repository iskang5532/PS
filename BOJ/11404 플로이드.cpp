// 11404 플로이드
// https://www.acmicpc.net/problem/11404
/*
    플로이드 와샬 (2,152KB, 24ms)
    시간 복잡도: O(V^3) (3중 for문)
    풀이)
    - path[i][j] = c일 때, i에서 j로 가기 위한 비용은 c.
    만약 c == INF라면 i에서 j로 가는 방법은 없는 것이며, 0일 경우 a to b.
    - i에서 j로 이동할 때, 중간 지점 k를 거쳐 가는 방법이 비용이 덜 드는지를 조사.
    - 주의할 점은, 입력에서 여러 a to b가 입력될 수 있으며, 각기 다른 비용일 수 있다.
    그러므로, 입력 시에 최소 비용만 저장할 수 있도록 해야 한다.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 987654321

void Floyd_Warshall(vector<vector<int>> &path, int n)
{
    for (int k = 0; k < n; k++) // 거쳐가는 지점
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i == j) // i to i
                    continue;
                else if (path[i][k] + path[k][j] < path[i][j])
                    path[i][j] = path[i][k] + path[k][j];
}

int main()
{
    FAST_IO;

    int n, m; // 도시의 개수 n(2 ≤ n ≤ 100), 버스의 개수 m(1 ≤ m ≤ 100,000)
    cin >> n >> m;

    vector<vector<int>> path(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++)
    {
        int a, b, c; // 도시 a b, 비용 c(1 ≤ c ≤ 100,000)
        cin >> a >> b >> c;
        if (path[a - 1][b - 1] > c)
            path[a - 1][b - 1] = c;
    }

    Floyd_Warshall(path, n);

    for (const auto &row : path)
    {
        for (const auto &col : row)
            col == INF ? cout << '0' << ' ' : cout << col << ' ';
        cout << endl;
    }
}