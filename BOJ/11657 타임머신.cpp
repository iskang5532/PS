// 11657 타임머신
// https://www.acmicpc.net/problem/11657
/*
    SPFA (2,168KB, 0ms)
    시간 복잡도: O(VE) (최악: O(V + E); SPFA의 시간 복잡도)
    풀이)
    - 정점은 1부터 시작. 0부터 시작시키기 위해 입력된 정점의 값에 -1을 해줌.
    - SPFA를 이용해 시작점 0에서부터 모든 정점까지의 거리를 구함.
     - 큐에 존재하는 정점만 탐색.
     큐에 수가 존재하는 지의 여부는 inQ에 저장. (inQ[k] = true일 시, 값 k는 큐에 존재)
     - 각 정점까지의 최대 탐색 횟수는 n번이다. 만약 n번 이상 탐색된 경우, 무한 사이클이 생성된 것임.
     각 정점의 탐색 횟수를 저장할 cycle. (cycle[n] = k일 경우, n번째 정점의 탐색 횟수는 k)
    - 무한 사이클이 생기는지의 여부를 isCycle에 저장.
    참고)
    - 이론: https://www.crocus.co.kr/1089
    - 출력 초과: https://www.acmicpc.net/board/view/55270 (and why used long long)
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321
#define MAX 500 + 1 // 도시의 최대 개수
using ll = long long;
using pii = pair<int, int>;

int n, m; // 도시의 개수 N(1 ≤ N ≤ 500), 버스 노선의 개수 M(1 ≤ M ≤ 6,000)
vector<pii> v[MAX];
bool isCycle = false; // 무한 사이클인가?

vector<ll> SPFA(int st = 0)
{
    vector<ll> dist(n + 1, INF); // dist[n] = k일 경우, 0에서 n번째 지점까지의 최단 거리는 k
    queue<int> q;
    bool inQ[MAX];  // inQ[k] = true일 경우, 수 k는 큐에 들어 있음
    int cycle[MAX]; // cycle[n] = 4일 경우, n번 지점은 4번 방문함

    dist[st] = 0;
    q.push(st);
    fill(inQ, inQ + MAX, false);
    fill(cycle, cycle + MAX, 0);

    while (q.size() && !isCycle)
    {
        int cur = q.front();
        q.pop(), inQ[cur] = false;

        for (const auto &elem : v[cur])
        {
            auto [next, n_c] = elem;

            if (dist[next] > dist[cur] + n_c)
            {
                dist[next] = dist[cur] + n_c;

                if (!inQ[next]) // 큐에 값이 없을 경우 (= 새로 큐에 넣어줌)
                {
                    q.push(next), inQ[next] = true;
                    cycle[next]++;

                    if (cycle[next] > n) // 사이클의 횟수가 허용량을 초과 (= 무한 사이클 형성)
                        isCycle = true;
                }
            }
        }
    }

    return dist;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c; // 버스 노선의 정보 A, B, C(1 ≤ A, B ≤ N, |C| ≤ 10,000)
        cin >> a >> b >> c;

        v[a - 1].push_back({b - 1, c});
    }

    vector<ll> dist = SPFA();

    if (isCycle)
        cout << "-1";
    else
        for (int i = 1; i < n; i++)
            cout << (dist[i] != INF ? dist[i] : -1) << endl;
}