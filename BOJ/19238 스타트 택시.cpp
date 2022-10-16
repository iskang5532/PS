// 2022-10-09
// 19238 스타트 택시
// https://www.acmicpc.net/problem/19238
/*
    구현, BFS (2,160KB, 12ms)
    시간 복잡도: ?
    풀이)
    etc.)
    참고)
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define INF 0x3f3f3f3f
#define y first
#define x second

constexpr int dy[] = {-1, 0, 1, 0};
constexpr int dx[] = {0, 1, 0, -1};

struct P
{
    pii st, ed; // 출발지, 목적지
    int dist;   // 출발지까지의 거리
};

int n, m, puel; //  영역의 크기 (2 ≤ n ≤ 20), 승객의 수 (1 ≤ m ≤ n^2), 연료의 양 (1 ≤ puel ≤ 500k)

bool OOB(int ny, int nx) { return !(1 <= ny && ny <= n) || !(1 <= nx && nx <= n); }

bool cmp(const P &p1, const P &p2) // 큰 값이 앞으로
{
    auto [s1, idx1, c1] = p1;
    auto [s2, idx2, c2] = p2;

    return c1 != c2 ? c1 > c2
                    : (s1.y != s2.y ? s1.y > s2.y
                                    : s1.x > s2.x);
};

vector<vector<int>> get_dist(const vector<vector<int>> &arr, const pii &taxi) // 출발지 or 목적지까지의 거리 구하기
{
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    dist[taxi.y][taxi.x] = 0;
    queue<pii> q;
    q.push(taxi);

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{y + dy[d], x + dx[d]};

            if (OOB(ny, nx))
                continue;
            if (dist[ny][nx] != INF || arr[ny][nx]) // 이미 탐색 or 벽
                continue;

            dist[ny][nx] = dist[y][x] + 1;
            q.push(pii{ny, nx});
        }
    }

    return dist;
}

int main()
{
    FAST_IO;

    cin >> n >> m >> puel;

    vector<vector<int>> arr(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> arr[i][j];

    pii taxi;
    cin >> taxi.y >> taxi.x;

    vector<P> people(m); // 출발지, 목적지, 택시-출발지의 거리
    for (auto &[st, ed, idx] : people)
        cin >> st.y >> st.x >> ed.y >> ed.x;

    while (people.size())
    {
        auto dist = get_dist(arr, taxi); // 거리 구하기 (to 사람)
        for (auto &[st, ed, _dist] : people)
            _dist = dist[st.y][st.x]; // 사람의 정보에 거리 저장

        sort(people.begin(), people.end(), cmp); // 택시-사람의 거리를 이용한 정렬

        const auto &[st, ed, _dist] = people.back(); // 가장 가까운 사람의 정보를 빼냄
        people.pop_back();

        taxi = pii{st.y, st.x}; // 택시 이동 (사람의 위치)
        puel -= _dist;

        dist = get_dist(arr, taxi); // 거리 구하기 (to 목적지)

        taxi = pii{ed.y, ed.x}; // 택시 이동 (목적지로)
        puel -= dist[ed.y][ed.x];

        if (_dist == INF || puel < 0) // 손님을 목적지로 이동시킬 수 없는 경우
            break;

        puel += dist[ed.y][ed.x] * 2;
    }

    cout << (people.empty() ? puel : -1);
}

// ~2022-10-09
/*
   19238 스타트 택시
   구현 (2160KB, 12ms)
   시간 복잡도: ?
   문제: https://www.acmicpc.net/problem/19238
   etc.) 생각난 데로 구현을 한 것이라 그런지 굉장히 복잡. (tuple을 섞어서 그런 듯)
   출발지와 목적지가 쌍으로 이루어져 있으므로 입력 때 같이 묶음.
   출발지까지 거리가 가장 짧으면서 조건(col, row)을 만족하는 손님을 선택한 후 값을 빼내며, 손님의 정보를 제거. (정보는 시작점 및 도착점)
    - 여기서 거리의 짧은 손님은 정렬로 구함.
   이 문제에서는 예외처리가 많이 필요하다.
    - 손님에게 도달할 수 없는 경우
    - 손님에게 도달하는 과정에서 연료가 부족해진 경우
    - 손님을 태운 후 목적지까지 도달할 수 없는 경우
    - 손님을 태운 후 목적지까지 도달하는 과정에서 연료가 부족해진 경우 (연료가 0이 된 경우는 아님)
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 987654321

const int dim_col[4] = {-1, 0, 1, 0};
const int dim_row[4] = {0, 1, 0, -1};

struct pii
{
    int col, row;
};

bool _greater(const tuple<pii, pii, int> &p1, const tuple<pii, pii, int> &p2) // 큰 값이 앞으로
{
    auto [p1_start, p1_end, p1_cnt] = p1;
    auto [p2_start, p2_end, p2_cnt] = p2;

    if (p1_cnt == p2_cnt)
        if (p1_start.col == p2_start.col)
            return p1_start.row > p2_start.row;
        else
            return p1_start.col > p2_start.col;
    return p1_cnt > p2_cnt;
};

vector<vector<int>> get_dist(const vector<vector<int>> &arr, int n, pii &taxi)
{
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    dist[taxi.col][taxi.row] = 0;
    queue<pii> q;
    q.push(taxi);

    while (!q.empty())
    {
        auto [col, row] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int next_col = col + dim_col[i];
            int next_row = row + dim_row[i];

            if (!(1 <= next_col && next_col <= n) || !(1 <= next_row && next_row <= n)) // 범위
                continue;
            if (dist[next_col][next_row] != INF) // 이미 탐색
                continue;
            if (arr[next_col][next_row]) // 벽
                continue;

            dist[next_col][next_row] = dist[col][row] + 1;
            q.push(pii{next_col, next_row});
        }
    }

    return dist;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m, puel; //  영역의 크기 (2 ≤ n ≤ 20), 승객의 수 (1 ≤ m ≤ n^2), 연료의 양 (1 ≤ puel ≤ 500k)
    cin >> n >> m >> puel;

    vector<vector<int>> arr(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> arr[i][j];

    pii taxi;
    cin >> taxi.col >> taxi.row;

    vector<tuple<pii, pii, int>> people(m); // 출발지, 목적지, 택시-출발지의 거리
    for (auto &[start, end, TEMP] : people)
        cin >> start.col >> start.row >> end.col >> end.row;

    while (true)
    {
        auto dist = get_dist(arr, n, taxi); // 택시-사람의 거리를 구함
        for (auto &[start, end, _dist] : people)
            _dist = dist[start.col][start.row]; // 택시와 사람의 거리

        if (people.empty()) // 모든 사람들을 다 이동시킨 경우
        {
            cout << puel << endl;
            return 0;
        }
        sort(people.begin(), people.end(), _greater);   // 택시-사람의 거리를 이용한 정렬
        const auto [start, end, _dist] = people.back(); // 가장 가까운 사람의 정보를 빼냄
        people.pop_back();

        taxi = pii{start.col, start.row}; // 택시의 위치를 사람의 위치로 이동
        puel -= _dist;

        dist = get_dist(arr, n, taxi); // 택시-목적지의 위치를 구함

        taxi = pii{end.col, end.row}; // 택시를 목적지로
        puel -= dist[end.col][end.row];

        if (_dist == INF || puel < 0) // 손님을 목적지로 이동시킬 수 없는 경우도 포함
        {
            cout << "-1";
            return 0;
        }
        puel += dist[end.col][end.row] * 2;
    }
}

// input:
// 6 4 15
// 0 0 1 0 0 0
// 0 0 1 0 0 0
// 0 0 0 0 0 0
// 0 0 0 0 0 0
// 0 0 0 0 1 0
// 0 0 0 1 0 0
// 6 5
// 2 2 5 6
// 5 4 1 6
// 4 2 3 5
// 1 6 5 4
// ans:
// 20

// input:
// 2 1 1
// 0 0
// 0 1
// 0 0
// 0 1 0 0
// ans:
// -1