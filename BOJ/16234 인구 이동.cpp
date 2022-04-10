// 16234 인구 이동
// https://www.acmicpc.net/problem/16234
// 2022-04-07
/*
    sol.1) 구현, BFS (2,068KB, 356ms)
    풀이)
    - BFS를 이용하여 국경선이 열린 곳을 구함. (= isValid())
    만약 국경선이 열렸을 경우, 이어진 땅을 그룹으로 묶음. (group[][]에 저장)
    또한, 해당 그룹에 포함된 땅의 수와 인구수를 저장할 P. (P[i] = {sum, cnt}일 경우, i번 그룹은 총 sum명과 cnt개의 땅이 포함됨)
    - 만약 국경선이 열린 적이 있을 경우, 열린 국경선을 통해 인구를 분배함. (= moved())
    각 땅을 탐색하며, 해당 땅의 그룹을 확인하여 인원을 분배.
*/

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53 // max n

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

struct pii
{
    int sum, cnt;

    void operator+=(const pii &p) { sum += p.sum, cnt += p.cnt; };
};

int n, l, r; // 크기 n(1 ≤ n ≤ 50), 범위 l, r(1 ≤ L ≤ R ≤ 100)
int board[MAX][MAX];
int group[MAX][MAX]; // (i, j)가 몇 번째 그룹인지
pii P[MAX * MAX];    // P[i] = {sum, cnt}일 경우, i번 그룹은 총 sum명과 cnt개의 땅이 포함됨)

bool isValid()
{
    bool ret = false;
    fill(&group[0][0], &group[0][0] + MAX * MAX, 0);
    fill(P, P + MAX * MAX, pii{0, 0});

    int cnt = 0; // 부여할 그룹의 번호
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!group[i][j])
            {
                cnt++;
                queue<pii> q;
                q.push({i, j});

                group[i][j] = cnt, P[cnt] += pii{board[i][j], 1};
                while (q.size())
                {
                    auto [y, x] = q.front();
                    q.pop();
                    for (int i = 0; i < 4; i++)
                    {
                        auto [ny, nx] = pii{y + dy[i], x + dx[i]};
                        if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
                            continue;
                        if (group[ny][nx]) // 그룹에 속한 경우
                            continue;

                        int sub = abs(board[y][x] - board[ny][nx]);
                        if (l <= sub && sub <= r)
                        {
                            ret = true;
                            group[ny][nx] = cnt, P[cnt] += pii{board[ny][nx], 1};
                            q.push({ny, nx});
                        }
                    }
                }
            }

    return ret;
}

void moved()
{
    int k[MAX * MAX]{}; // i번째 그룹에 분배될 인구수
    for (int i = 1; i < MAX * MAX; i++)
    {
        auto [sum, cnt] = P[i];
        if (cnt >= 2) // 그룹에 땅이 둘 이상인 경우
            k[i] = sum / cnt;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int g = group[i][j];
            if (k[g]) // 분배될 인구수가 존재할 경우
                board[i][j] = k[g];
        }
}

int main()
{
    FAST_IO;

    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    int ans = 0;
    while (true)
    {
        if (!isValid())
            break;

        moved(), ans++;
    }

    cout << ans;
}

// 2022-04-07
/*
    sol.2) 구현, 유니온 파인드 (2,068KB, 88ms)
    풀이)
    - 유니온 파인드를 사용하여 각 땅의 그룹을 관리.
    etc.) MST?
    참고)
    - 2차원 배열을 1차원 배열로 Conv: https://blog.naver.com/jinhan814/222152206836
 */

#include <iostream>
#include <numeric> // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max n

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int n, l, r;         // 크기 n(1 ≤ n ≤ 50), 범위 l, r(1 ≤ L ≤ R ≤ 100)
int board[MAX][MAX]; // 0 ≤ k ≤ 100

struct Union_Find
{
    int group[MAX * MAX];
    int cnt[MAX * MAX]; // i번 그룹에 포함된 땅의 수
    int sum[MAX * MAX]; // i번 그룹의 전체 인구
    void init()
    {
        iota(group, group + MAX * MAX, 0);
        fill(cnt, cnt + MAX * MAX, 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                sum[i * n + j] = board[i][j];
    }

    int find_parent(int x) { return group[x] == x ? group[x] : group[x] = find_parent(group[x]); }
    int find_parent(int y, int x) { return find_parent(n * y + x); } // to 1d
    void union_parent(int a, int b)
    {
        if (a > b)
            swap(a, b);
        group[b] = a, sum[a] += sum[b], cnt[a] += cnt[b];
    }
} uf;

bool isValid()
{
    bool flag = false; // 국경선이 열렸는가?
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            for (int d = 0; d < 4; d++)
            {
                auto [ny, nx] = pii{y + dy[d], x + dx[d]};
                if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
                    continue;

                int diff = abs(board[y][x] - board[ny][nx]);
                if (l <= diff && diff <= r)
                {
                    int a = uf.find_parent(y, x), b = uf.find_parent(ny, nx);
                    if (a != b)
                        uf.union_parent(a, b);

                    flag = true;
                }
            }

    return flag;
}

void moved()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int group = uf.find_parent(i, j);
            board[i][j] = uf.sum[group] / uf.cnt[group];
        }
}

int main()
{
    FAST_IO;

    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    int ans = 0;
    while (true)
    {
        uf.init();
        if (!isValid())
            break;

        moved(), ans++;
    }

    cout << ans;
}