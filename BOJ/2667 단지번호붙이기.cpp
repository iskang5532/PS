// 2022-10-30
// 2667 단지번호붙이기
// https://www.acmicpc.net/problem/2667
/*
    BFS, 유니온 파인드(MST?) (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 board[][]에 저장.
    - 모든 값을 확인.
    만약 board[y][x]값이 1(= 집)일 경우, bfs와 시작점 st(y, x)를 이용하여 인접한 모든 집을 확인. (단, 방문한 적이 없어야 함)
    - 유니온 파인드를 이용하여 단지를 관리.
    - 한 번의 탐색으로 구한 모든 집은 같은 단지에 속함.
    - 각 집마다 번호를 부여하며, 단지에 속해질 때 사용.
    단지의 번호는, 단지에 속해질 집 중 가장 작은 번호를 사용.
    단지에 속한 집의 개수 또한 cnt[]에 저장하며, 이 또한 시작한 집의 번호를 사용.
    추가로, 번호가 작은 순서대로 board를 탐색하므로, st의 값이 무조건 부모가 됨. (두 집의 번호가 parent, child일 경우 parent < child가 항상 성립)
    - st로 구한 parent 단지 내 집의 수인 cnt[parent]를 v에 저장.
    - 모든 board의 값을 확인하여 v가 구해졌을 경우, v를 정렬.
    이후, v의 크기 및 v의 값을 출력.
    etc.)
    - 이런 문제는 유니온 파인드 풀이밖에 생각이 안남.
    - 예전에 분할정복으로 풀었었는데, 분할압축 공부하면서 얼떨결에 푼듯.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 28 // max n
#define HOUSE '1'

constexpr int dy[] = {-1, 0, 1, 0}; // 북 동 남 서
constexpr int dx[] = {0, 1, 0, -1};

struct Union_Find
{
    int parent[MAX * MAX];
    int cnt[MAX * MAX]; // 인접한 집의 개수 (cnt[i] = k일 경우, i번과 인접한 집의 개수는 k개)
    Union_Find()
    {
        iota(parent, parent + MAX * MAX, 0);
        fill(cnt, cnt + MAX * MAX, 1);
    }

    int find_parent(int x) { return x == parent[x] ? parent[x] : parent[x] = find_parent(parent[x]); }
    int find_parent(int y, int x) { return find_parent(y * MAX + x); }
    void union_parent(int par, int child) { cnt[par] += cnt[child], parent[child] = par; }
} uf;

int n; // 5 ≤ N ≤ 25
char board[MAX][MAX];
bool visited[MAX][MAX];
vector<int> v; // 단지 내 집의 수를 저장 (v = {1, 2}일 경우, 2개의 단지가 있으며 각 단지에는 1개와 2개의 집이 존재)

bool OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < n); }

void bfs(pii st)
{
    queue<pii> q;
    q.push(st);

    int parent = uf.find_parent(st.first, st.second);
    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{y + dy[d], x + dx[d]};
            if (OOB(ny, nx))
                continue;
            if (visited[ny][nx] || board[ny][nx] != HOUSE)
                continue;

            int child = uf.find_parent(ny, nx);
            uf.union_parent(parent, child);

            q.push({ny, nx}), visited[ny][nx] = true;
        }
    }

    v.push_back(uf.cnt[parent]); // 현재 단지 내 집의 수를 저장
}

int main()
{
    FAST_IO;

    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            if (board[y][x] == HOUSE && !visited[y][x])
                visited[y][x] = true, bfs({y, x});

    sort(v.begin(), v.end());

    cout << v.size() << endl;
    for (const int &i : v)
        cout << i << endl;
}