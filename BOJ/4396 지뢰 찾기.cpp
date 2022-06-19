// 2022-06-09
// 4396 지뢰 찾기
// https://www.acmicpc.net/problem/4396
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 주변에 지뢰가 몇 개 있는지를 저장할 cnt. (cnt[y][x] = k일 때, {y, x} 주변에는 지뢰가 k개)
    - 해당 위치에 지뢰가 존재하는지를 저장할 bomb. (bomb[y][x] = true일 때, {y, x}는 지뢰가 존재)
    1. 탐색중인 칸 {y, x}가 플레이어가 고른 칸일 경우, ans[y][x]에 cnt[y][x]를 저장.
    이때, {y, x}에 지뢰가 존재할 경우 boom = true.
    2. 만약 지뢰가 있는 칸을 골랐을 경우
    bomb의 모든 값을 확인하며, 지뢰의 위치와 똑같은 ans의 위치에 지뢰를 넣음. (기존 값 → '*')
    3. ans 출력.
    etc.) 깔끔하지 않은게 아쉽
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 13

constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

int n;
bool bomb[MAX][MAX]; // bomb[y][x] = true일 떄, {y, x}에 지뢰가 존재함
int cnt[MAX][MAX];   // cnt[y][x] = k일 때, {y, x} 주변에 지뢰가 k개 존재함

bool OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < n); }

int main()
{
    FAST_IO;

    cin >> n;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
        {
            char c;
            cin >> c;
            if (c == '*')
            {
                bomb[y][x] = true;
                for (int d = 0; d < 8; d++)
                {
                    auto [ny, nx] = pii{y + dy[d], x + dx[d]};
                    if (OOB(ny, nx))
                        continue;

                    cnt[ny][nx]++;
                }
            }
        }

    char ans[MAX][MAX];
    bool boom = false; // 폭탄을 건드렸는가
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
        {
            char c;
            cin >> c;
            if (bomb[y][x] && c == 'x')
                boom = true;

            ans[y][x] = (c == 'x' ? cnt[y][x] + '0' : '.');
        }
    for (int y = 0; y < n && boom; y++)
        for (int x = 0; x < n; x++)
            if (bomb[y][x])
                ans[y][x] = '*';

    for (int y = 0; y < n; y++, cout << endl) // print
        for (int x = 0; x < n; x++)
            cout << ans[y][x];
}