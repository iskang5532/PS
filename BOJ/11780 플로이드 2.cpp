// 11780 플로이드 2
// https://www.acmicpc.net//problem/11780
/*
    플로이드 와샬 (2,156KB, 32ms)
    시간 복잡도: O(V^3) (3중 for문)
    풀이)
    - 플로이드 와샬로 구한 모든 경로를 path에 저장.
    - a에서 b로 갈 때 방문한 모든 지점을 저장할 P.
    P[a][b] = c일 때, a에서 b로 이동할 시 a 다음 위치는 c. (만약 c == b면 a 다음은 b)
    - 플로이드 와샬 수행 과정에서 경로의 비용 갱신이 가능할 시, P값 또한 갱신해준다.
    P[a][b] = P[a][mid]. 주의할 점은, P[a][b]에 mid값을 넣으면 안 됨.
    - 도시의 개수 및 경로 출력.
    경로는 P에 저장되어 파악할 수 있지만, 개수는 파악할 수 없음.
    그러므로 임의의 공간 v를 만들어 거쳐 가는 지점을 저장한 후, v의 크기를 이용해 개수를 파악.
    etc.) 방문하는 지점을 저장한 P를 구하는게 어려웠던 문제.
    - P[a][b] = P[a][mid]인데, P[a][b] = mid가 안되는 이유는 무엇인가? (예제로 확인이 가능하나, 정확히 모르겠음)
    참고)
    - 이론: https://blog.naver.com/ndb796/221234427842
    - 코드: https://blog.naver.com/jinhan814/222084200773
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 987654321

int n, m;    // 도시의 개수 n(1 ≤ n ≤ 100), 버스의 개수 m(1 ≤ m ≤ 100,000)
int a, b, c; // 시작 도시 a, 도착 도시 b, 비용 c(1 ≤ c ≤ 100k)

void print_ans(const vector<vector<int>> &path, const vector<vector<int>> &P);
void Floyd_Warshall(vector<vector<int>> &path, vector<vector<int>> &P)
{
    for (int mid = 1; mid <= n; mid++) // 거쳐가는 지점
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= n; b++)
                if (a == b) // a to a
                    continue;
                else if (path[a][mid] + path[mid][b] < path[a][b]) // 거쳐 가는 경우가 비용이 덜 드는 경우 (= 갱신)
                {
                    path[a][b] = path[a][mid] + path[mid][b];
                    P[a][b] = P[a][mid]; // a에서 b로 가기 위한 a 다음 위치
                }
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    vector<vector<int>> path(n + 1, vector<int>(n + 1, INF)); // path[a][b] = c일 때, a에서 b로 가는 비용은 c
    vector<vector<int>> P(n + 1, vector<int>(n + 1));         // P[a][b] = c일 때, a에서 b로 이동할 시 a 다음 위치는 c (c == b일 시, a 다음은 b)

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        if (c < path[a][b]) // 입력값이 기존값보다 작은 경우 (= 갱신이 필요한 경우)
        {
            path[a][b] = c;
            P[a][b] = b; // a to b의 기본값은 b (이 시점에서는 중간에 거쳐가는 지점은 없음)
        }
    }

    Floyd_Warshall(path, P);

    print_ans(path, P);
}

void print_ans(const vector<vector<int>> &path, const vector<vector<int>> &P)
{
    // 도시 a에서 b로 가는데 필요한 최소 비용
    for (int a = 1; a <= n; a++, cout << endl)
        for (int b = 1; b <= n; b++)
            path[a][b] == INF ? cout << '0' << ' ' : cout << path[a][b] << ' ';

    // 도시 a에서 b로 최소 비용으로 가면서 포함한 도시의 개수와 도시의 경로
    for (int st = 1; st <= n; st++)
        for (int ed = 1; ed <= n; ed++)
            if (st == ed || path[st][ed] == INF) // 자기 자신에게 or 길이 없는 경우
                cout << '0' << endl;
            else
            {
                vector<int> v;

                int i = st; // 출발점에서부터
                while (i != ed)
                {
                    v.push_back(i);
                    i = P[i][ed];
                }
                v.push_back(i); // 도착점 추가

                cout << v.size() << ' ';
                for (const auto &i : v)
                    cout << i << ' ';
                cout << endl;
            }
}

// 람다 재귀식: https://blog.naver.com/jinhan814/222201778180
// 2,024KB, 92ms
// {
//     if (c < path[a][b])
//         P[a][b] = P[mid][b]; // a에서 b로 가기 위한 a 다음 위치
// }
// {
//     vector<vector<int>> P(n + 1, vector<int>(n + 1)); // P[a][b] = c일 때, a에서 b로 갈 때의 첫 번째 위치는 c

//     P[a][b] = a; // a to b의 기본값은 a (이 시점에서는 중간에 거쳐가는 지점은 없음)
// }
// {
//     function<void(int, int)> func = [&](int k, int dep) -> void
//     {
//         if (k == st)
//         {
//             cout << dep << ' ' << k << ' ';
//             return;
//         }
//         func(P[st][k], dep + 1);
//         cout << k << ' ';
//     };
//     func(ed, 1);
//     cout << endl;
// }

// 4 5
// 1 4 10000
// 3 4 1
// 1 3 10
// 2 3 1
// 1 2 1
// 1 to 4 = 3