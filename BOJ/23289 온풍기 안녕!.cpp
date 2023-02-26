// 2023-02-24
// 23289 온풍기 안녕!
// https://www.acmicpc.net/problem/23289
/*
    구현, 시뮬레이션 (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 조사해야 하는 모든 칸의 온도가 k 이상이 되었을 경우, 반복한 횟수를 출력. 단, 최댓값은 101.
    - 조사해야 하는 칸의 정보를 v에 저장.
    - 입력된 벽을 2진수로 변환하여 2차원 배열 wall[][]에 저장. (wall[y][x] = 0b0011일 경우, (y, x)의 위와 좌측에 벽이 존재)
    - 온풍기에서 바람이 나와 퍼지는 온도는 항상 동일한다. 그러므로, 한 번 퍼졌을 때의 온도를 sum에 저장하여 사용한다.
    bfs()를 이용하여 sum을 구한다. 이때, 벽이 막고 있는지를 확인해야 한다.
     - 직선으로 이동 시에는 해당 위치와 다음 위치 사이에 벽이 있는지를 확인한다.
     - 대각선으로 이동 시에는 바람의 방향에 따른 벽을 고려해야 한다. (수직이 되도록 이동 후 바람의 방향에 맞춰 이동)
     만약 다음 위치가 1사분면일 경우, 우측으로 이동 후 위로 이동하는 과정에서 벽이 없어야 한다.
    - 집 안의 온도를 저장할 temp[][].
    1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
    - temp에 sum값을 더함.
    2. 온도가 조절됨
    - 해당 칸과 인접한 칸의 온도 차가 4 이상일 경우, 인접한 칸에 온도를 나눈다. (나눈 값은 t에 저장)
    - 큰 값에서 작은 값으로 퍼질 수 있는지를 조사한다.
    이는 기준이 되는 위치의 값이 인접한 칸보다 커야 하며, 만약 작을 경우 해당 칸이 기준으로 되었을 때 조절을 시도한다.
    3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
    - 바깥쪽 칸의 온도를 1씩 감소한다. 이때, 칸의 온도는 최소 0이다.
    4. 초콜릿을 하나 먹는다.
    choco++.
    5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
    - v에 저장된 값을 이용하여 칸의 온도가 k 이상인지 확인.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 23 // max n, m

class Board
{
private:
    const int dy[4] = {-1, 0, 1, 0}; // 북 서 남 동
    const int dx[4] = {0, 1, 0, -1};

    int r, c, k; // 크기 r, c(2 ≤ r, c ≤ 20), 온도 k(1 ≤ k ≤ 2,000)
    int board[MAX][MAX];
    int wall[MAX][MAX]; // wall[y][x] = 0b0011일 경우, (y, x)의 위와 좌측에 벽이 존재
    vector<pii> v;      // 조사해야 하는 칸을 저장

    int sum[MAX][MAX];  // 바람이 한 번 나올 때의 온도
    int temp[MAX][MAX]; // 온도

public:
    void input()
    {
        cin >> r >> c >> k;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
            {
                int p; // 0: 빈 칸, 1: 우측, 2: 좌측, 3: 위, 4: 아래, 5: 조사
                cin >> p;
                board[i][j] = (p == 0 || p == 5) ? -1
                              : (p == 1)         ? 1
                              : (p == 2)         ? 3
                              : (p == 3)         ? 0
                                                 : 2;
                if (p == 5)
                    v.push_back({i, j});
            }

        int w; // 벽의 개수 (0 ≤ w ≤ r*c)
        cin >> w;
        for (int i = 0; i < w; i++)
        {
            int y, x, t; // 위치 (y, x), 방향 t(0:위, 1:우측)
            cin >> y >> x >> t;

            wall[y][x] |= (1 << t);
            (t == 0) ? wall[y - 1][x] |= (1 << 2)
                     : wall[y][x + 1] |= (1 << 3);
        }
    };

    bool OOB(int ny, int nx) { return !(1 <= ny && ny <= r) || !(1 <= nx && nx <= c); }

    void get_sum()
    {
        auto _has_wall = [&](int y, int x, int ny, int nx, int dir, int d) -> bool // 해당 위치까지 벽이 있는지 확인
        {
            if (d == 1) // 직선
                return (wall[y][x] & 1 << dir) ? true : false;
            else if (dir == 0 || dir == 2) // 상하 (= 좌우 이동 후 상하 이동)
            {
                if (wall[y][x] & 1 << (d == 0 ? 3 : 1) ||
                    wall[ny][nx] & 1 << (dir + 2) % 4)
                    return true;
            }
            else if (dir == 1 || dir == 3) // 좌우 (= 상하 이동 후 좌우 이동)
            {
                if (wall[y][x] & 1 << (d == 0 ? 0 : 2) ||
                    wall[ny][nx] & 1 << (dir + 2) % 4)
                    return true;
            }
            return false;
        };

        for (int st_y = 1; st_y <= r; st_y++)
            for (int st_ = 1; st_ <= c; st_++)
            {
                if (board[st_y][st_] == -1) // 빈 공간
                    continue;

                int dir = board[st_y][st_]; // 바람의 방향

                queue<pii> q;
                q.push({st_y + dy[dir], st_ + dx[dir]}); // 선풍기의 앞에서부터 시작
                int dist[MAX][MAX]{};
                dist[st_y + dy[dir]][st_ + dx[dir]] = 5; // 초깃값 5

                constexpr int _dy[][3] = {{-1, -1, -1}, {-1, 0, 1}, {1, 1, 1}, {-1, 0, 1}};
                constexpr int _dx[][3] = {{-1, 0, 1}, {1, 1, 1}, {-1, 0, 1}, {-1, -1, -1}};
                while (q.size())
                {
                    auto [y, x] = q.front();
                    q.pop();

                    sum[y][x] += dist[y][x];

                    for (int d = 0; d < 3; d++) // 이동할 위치
                    {
                        auto [ny, nx] = pii{y + _dy[dir][d], x + _dx[dir][d]};
                        if (OOB(ny, nx) || dist[ny][nx])
                            continue;
                        if (_has_wall(y, x, ny, nx, dir, d))
                            continue;

                        dist[ny][nx] = dist[y][x] - 1;
                        if (dist[ny][nx])
                            q.push({ny, nx});
                    }
                }
            }
    }
    void flood()
    {
        for (int y = 1; y <= r; y++)
            for (int x = 1; x <= c; x++)
                temp[y][x] += sum[y][x];
    }
    void control_temp()
    {
        int t[MAX][MAX]{}; // 조절될 온도
        for (int y = 1; y <= r; y++)
            for (int x = 1; x <= c; x++)
                for (int d = 0; d < 4; d++)
                {
                    auto [ny, nx] = pii{y + dy[d], x + dx[d]};
                    if (OOB(ny, nx) || wall[y][x] & 1 << d)
                        continue;

                    int k = temp[y][x] - temp[ny][nx]; // 온도 차
                    if (k >= 4)
                        t[y][x] -= k / 4, t[ny][nx] += k / 4;
                }

        for (int y = 1; y <= r; y++)
            for (int x = 1; x <= c; x++)
                temp[y][x] += t[y][x]; // 조절된 값을 합함
    }
    void decrease_temp()
    {
        for (int y = 1; y <= r; y++)
            for (int x = 1; x <= c; x++)
                if (y == 1 || x == 1 || y == r || x == c) // 바깥쪽 칸의 온도 -1
                    temp[y][x] = max(0, temp[y][x] - 1);  // 단, 최소 온도는 0
    }
    bool is_ended() // 조건을 만족한 경우
    {
        for (const auto &[y, x] : v)
            if (temp[y][x] < k) // k 미만인 경우, 조건을 만족하지 않음
                return false;

        return true;
    }

} house;

int main()
{
    FAST_IO;

    house.input();
    house.get_sum();

    int choco = 0;
    while (choco <= 100)
    {
        house.flood();         // 1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
        house.control_temp();  // 2. 온도가 조절됨
        house.decrease_temp(); // 3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
        choco++;               // 4. 초콜릿을 하나 먹는다.

        if (house.is_ended()) // 5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
            break;
    }

    cout << choco;
}