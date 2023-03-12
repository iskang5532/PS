// 2023-03-09
// 17822 원판 돌리기
// https://www.acmicpc.net/problem/17822
/*
    구현, 덱 (2,180KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 2차원 공간에 저장.
    원판이 도는 것은 컨테이너가 앞 혹은 뒤로 값이 미는 것과 같다. 이를 구현하기 위해 덱을 사용.
    입력된 회전 방향 d가 시계 방향일 경우 뒤 값을 앞으로, 반시계 방향일 경우 앞 값을 뒤로 옮긴다.
    - 모든 위치에 대하여 인접한 값이 같은지를 확인한다.
    같은 값이 존재할 경우, 두 값 모두 삭제한다. (삭제란 컨테이너의 크기를 줄이거나 하지는 않음)
    삭제한 값을 한 번에 갱신하기 위하여 del[][]에 해당 위치에 대한 삭제 여부를 저장하며, 현재 회전하는 동안의 삭제 여부를 isDel에 저장.
    - isDel을 이용하여 값을 제거할지, 평균을 구하여 값을 갱신할지 정한다.
    주의할 점은, 나눈 값이 실수형일 수 있으며 평균과 같은 값일 경우 아무것도 하지 않아야 한다.
    etc.) 난이도에 비하여 쉽다고 생각. 
    - 평균을 구하는 데에 한 번, nx를 구하는 데에 한 번 데임.
 */

#include <iostream>
#include <deque>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define INF 0x3f3f3f3f
#define MAX 53 // max n, m

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int n, m, t; // 원판의 크기 n, 정수의 개수 m(2 ≤ n, m ≤ 50), 회전 횟수 t(1 ≤ t ≤ 50)
deque<int> board[MAX];

bool OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < m); }

int main()
{
    FAST_IO;

    cin >> n >> m >> t;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int k; // 1 ≤ k ≤ 1,000
            cin >> k;
            board[i].push_back(k);
        }
    for (int _ = 0; _ < t; _++)
    {
        int x, d, k; // 회전할 원판 번호 x(2 ≤ n ≤ n), 방향 d(0: 시계, 1: 반시계), 이동 횟수 k(1 ≤ k ≤ m)
        cin >> x >> d >> k;

        for (int pos = x; pos <= n; pos += x)
            for (int i = 0; i < k; i++)
                (d == 0) ? (board[pos - 1].push_front(board[pos - 1].back()), board[pos - 1].pop_back())   // 시계
                         : (board[pos - 1].push_back(board[pos - 1].front()), board[pos - 1].pop_front()); // 반시계

        int cnt = 0, sum = 0;                // 값의 개수 cnt와 합 sum
        bool del[MAX][MAX]{}, isDel = false; // 삭제 여부 del[][], 이번 회전에 삭제한 적이 있는지를 저장할 isDel
        for (int y = 0; y < n; y++)
            for (int x = 0; x < m; x++)
            {
                if (board[y][x] == INF)
                    continue;

                int val = board[y][x];
                cnt++, sum += val; // 값을 저장
                for (int _d = 0; _d < 4; _d++)
                {
                    auto [ny, nx] = pii{y + dy[_d], (m + x + dx[_d]) % m};
                    if (OOB(ny, nx))
                        continue;
                    if (board[ny][nx] == val) // 인접한 값이 현재 값과 동일한가
                        del[y][x] = del[ny][nx] = true, isDel = true;
                }
            }

        if (isDel) // 삭제한 적이 있는가?
        {
            for (int y = 0; y < n; y++)
                for (int x = 0; x < m; x++)
                    if (del[y][x])
                        board[y][x] = INF;
        }
        else
        {
            double avg = (double)sum / cnt;
            for (int y = 0; y < n; y++)
                for (int x = 0; x < m; x++)
                {
                    if (board[y][x] == INF)
                        continue;
                    board[y][x] += (board[y][x] < avg)   ? 1  // 평균 미만
                                   : (board[y][x] > avg) ? -1 // 평균 초과
                                                         : 0; // 평균
                }
        }
    }

    int ans = 0;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (board[y][x] != INF)
                ans += board[y][x];
    cout << ans;
}