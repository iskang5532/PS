// 11559 Puyo Puyo
// https://www.acmicpc.net/problem/11559
// 2022-04-10
/*
    구현, 유니온 파인드 (2,020KB, 0ms)
    풀이)
    - 유니온 파인트를 사용하여 인접한 같은 색상의 수를 저장. (cnt[g] = k일 경우, 그룹 g에 속한 색상은 k (이때, 색상은 모두 같음)
    - 연쇄가 가능한지를 탐색. (bang())
     - 모든 칸을 탐색하며, 탐색 중인 칸의 색상과 같은 인접한 색상이 있을 경우.
     만약 두 색상의 그룹이 다를 경우, 합쳐줌.
     이때, 두 그룹의 cnt를 합쳐줘야 함. (cnt++로 수행할 경우, 한쪽 그룹의 cnt가 손실될 수 있음)
     - 모든 칸을 탐색하며, 그룹의 cnt가 4 이상인 경우, 값을 공백으로 바꿈.
     또한, 연쇄가 가능한 경우이므로 true를 반환하여 ans++.
    - 색상을 아래로 내림. (= fallen())
    값을 옮길 가장 아래 칸인 bot, 값이 옮겨질 대상이면서 가장 위 칸인 top.
    bot이 공백이면서 top에 색상이 존재할 경우, top의 색상을 bot으로 옮김. (또한, top은 공백 처리)
    etc.) 아래로 푸쉬할 떄, 기준점은 += -1 해줘야 함에 주의
 */

#include <iostream>
#include <numeric> // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"

constexpr int n = 12, m = 6;
constexpr int dy[4] = {-1, 0, 1, 0}; // 북 동 남 서
constexpr int dx[4] = {0, 1, 0, -1};

char board[n][m];

struct Union_FInd
{
    int group[n * m]; // group[i] = g일 경우, i번째 위치의 그룹은 g
    int cnt[n * m];   // cnt[g] = k일 경우, 그룹 g에 속한 색상은 k (이때, 색상은 모두 같음)

    void init() { iota(group, group + n * m, 0), fill(cnt, cnt + n * m, 1); }
    int find_parent(int x) { return x == group[x] ? group[x] : group[x] = find_parent(group[x]); }
    int find_parent(int y, int x) { return find_parent(y * m + x); }
    void union_parent(int a, int b)
    {
        if (a > b)
            swap(a, b);
        group[b] = a, cnt[a] += cnt[b];
    }
} uf;

bool bang()
{
    bool ret = false; // is 뿌요뿌요??
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            for (int i = 0; i < 4; i++)
            {
                auto [ny, nx] = pii{y + dy[i], x + dx[i]};
                if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                    continue;
                if (board[y][x] != board[ny][nx] || board[y][x] == '.')
                    continue;

                int a = uf.find_parent(y, x), b = uf.find_parent(ny, nx);
                if (a != b)
                    uf.union_parent(a, b);
            }

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
        {
            int group = uf.find_parent(y, x);
            if (uf.cnt[group] >= 4)
                board[y][x] = '.', ret = true;
        }

    return ret;
}

void fallen()
{
    for (int x = 0; x < m; x++)
        for (int top = n - 2, bot = n - 1; top >= 0; top--)
            if (board[bot][x] != '.')
                bot--;
            else if (board[top][x] != '.')
                board[bot][x] = board[top][x], board[top][x] = '.', bot--;
}

int main()
{
    FAST_IO;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    int ans = 0;
    while (true)
    {
        uf.init();
        if (!bang())
            break;
        fallen(), ans++;
    }
    cout << ans;
}