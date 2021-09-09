/* 
 * 11780 플로이드 2
 * 플로이드 와샬
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/
 * etc.) 첫 플로이드 풀이.
 * 중간에 방문하는 지점을 구하는 문제가 어려웠음.
 * 참고: https://blog.naver.com/ndb796/221234427842 (이론)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define INF 987654321

void floyd_warshall(vector<vector<int>> &arr, vector<vector<int>> &next, const int n)
{
    for (int k = 1; k <= n; k++) // 거쳐가는 지점
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (arr[i][k] + arr[k][j] < arr[i][j]) // 거쳐가는 경우가 비용이 덜 드는 경우 (= 갱신)
                {
                    arr[i][j] = arr[i][k] + arr[k][j];
                    next[i][j] = next[i][k]; // i to j에 중간 지점인 k(= i to k)를 넣어줌
                }
}
void print(const vector<vector<int>> &arr, vector<vector<int>> &next, const int n)
{
    // print matrix
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (arr[i][j] == INF)
                cout << 0 << " ";
            else
                cout << arr[i][j] << " ";
        cout << endl;
    }

    // i to j
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j || arr[i][j] == INF) // 본인에게 가는 경우 or i to j가 없는 경우
                cout << 0 << endl;
            else
            {
                vector<int> p; // backtrace를 위한 공간
                int k = i;     // 초깃값은 시작점 i
                while (k != j) // k == j일 경우는 중간값이 없는 경우 (첫 입력 때의 [a][b] = b)
                {
                    p.push_back(k);
                    k = next[k][j]; // k to j 중에 방문하는 곳
                }
                p.push_back(j); // 빠진 도착점을 넣어줌

                cout << p.size() << " ";
                for (const auto &elem : p)
                    cout << elem << " ";
                cout << endl;
            }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 1 <= n <= 100, 1 <= m <= 100k
    cin >> n >> m;

    vector<vector<int>> arr(n + 1, vector<int>(n + 1, INF)); // arr[a][b] = c일 경우, a에서 b로 가는 비용은 c
    vector<vector<int>> next(n + 1, vector<int>(n + 1));     // next[a][b] = c일 경우, a에서 b로 갈 때 거쳐가는 지점 c
    for (int i = 1; i <= n; i++)
        arr[i][i] = 0; // 본인에게 가는 거리는 0
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (c < arr[a][b]) // 입력값이 기존값보다 작은 경우 (= 갱신이 필요한 경우)
        {
            arr[a][b] = c;
            next[a][b] = b; // a to b의 기본값은 b (이 시점에서 중간에 거쳐가는 지점은 없음)
        }
    }

    floyd_warshall(arr, next, n);

    print(arr, next, n);
}