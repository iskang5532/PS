// 2022-10-23
// 24725 엠비티아이
// https://www.acmicpc.net/problem/24725
/*
    완전 탐색 (2,328KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값 중 'E' 혹은 'I'의 위치를 st에 저장.
    이후, st에 저장된 값을 하나씩 완전 탐색에 사용.
    - ch에 각 위치의 MBTI를 저장.
    - 첫 번쨰 MBTI의 값은 st에 저장된 값이므로, 두 번째부터 탐색. (= next == 2)
    만약 다음 위치의 값이 두 번째 MBTI인 'N' 혹은 'S'인 경우, 그 다음 위치를 확인. (= next == 3)
    만약 그 다음 위치의 값이 세 번째 MBTI인 'F' 혹은 'T'인 경우, 그 다음 위치를 확인. (= next == 4)
    만약 그 다음 위치의 값이 네 번째 MBTI인 'P' 혹은 'J'인 경우, 그 다음 위치를 확인. (= next == 5)
    만약 next == 5일 경우, MBTI를 완성한 경우이므로 ans++.
    etc.) 지저분하게 푼듯한 기분
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 203 // max n, m

constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
constexpr char ch[][2] = {{}, {}, {'N', 'S'}, {'F', 'T'}, {'P', 'J'}};

int n, m; // 1 ≤ n, m ≤ 200
char board[MAX][MAX];
vector<pii> st;
int ans = 0;

bool OOB(int ny, int nx)
{
    return !(0 <= ny && ny < n) || !(0 <= nx && nx < m);
}

void sol(int i, int j)
{
    for (int d = 0; d < 8; d++)
    {
        int y = i, x = j;
        for (int next = 2; next <= 5; next++) // 다음 위치
        {
            bool _find = false; // next 위치의 mbti를 찾았는가
            if (next == 5)
            {
                ans++;
                break;
            }

            auto [ny, nx] = pii{y + dy[d], x + dx[d]};
            if (OOB(ny, nx))
                break;

            for (const char &c : ch[next])
                if (board[ny][nx] == c)
                {
                    y = ny, x = nx;
                    _find = true;
                    break;
                }

            if (!_find) // next번 mbti를 찾지 못했을 경우
                break;
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 'E' || board[i][j] == 'I')
                st.push_back({i, j});
        }

    for (const auto &[i, j] : st)
        sol(i, j);

    cout << ans;
}