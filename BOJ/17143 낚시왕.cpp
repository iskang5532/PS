/*
    17143 낚시왕
    구현 (2288KB, 104ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/17143
    etc.) 상어의 위치 및 이동 방향을 알기 때문에 이동 시간을 O(s)가 아닌 O(1)로 시간을 줄알 수 있겠지만, 시간 초과가 나지 않으므로 하지 않았음.
    - 사람이 움직여 상어을 잡은 후, 상어가 움직임. 이를 사람이 끝까지 도달할 때까지 반복.
    - 상어의 속도가 이동 방향에 대한 격자판의 크기보다 훨씬 클 경우, 값을 줄여 쓸데없는 행동을 없앰.
    - 상어가 방향을 바꿔야 하는 경우가 생기는데, 벽에 붙어 있을 때 바꿀 경우 예제의 (1, 3) 상어와 같이 입력으로 들어오는 순간 바뀔 수가 있음.
    때문에 벽 앞에 도착하는 순간에 방향을 바꿔줘야 함.
 */

#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

struct Shk
{
    int s, d, z; // 속력 (0 ≤ s ≤ 1k), 방향 (1 ≤ d ≤ 4), 크기 (1 ≤ z ≤ 10k) (d; 위, 아래, 오른, 왼)

    friend bool operator==(const Shk &p1, const Shk &p2)
    {
        if (p1.d == p2.d && p1.s == p2.s && p1.z == p2.z)
            return true;
        return false;
    };
    friend bool operator!=(const Shk &p1, const Shk &p2)
    {
        if (p1.d == p2.d && p1.s == p2.s && p1.z == p2.z)
            return false;
        return true;
    };
};

const int dim_col[5] = {0, 0, 0, 1, -1}; // idx, 위, 아래, 오른, 왼
const int dim_row[5] = {0, -1, 1, 0, 0};
const Shk IDX = {0, 0, 0}; // 빈 공간

void moved_shk(vector<vector<Shk>> &arr, int R, int C)
{
    vector<vector<Shk>> ret(C + 1, vector<Shk>(R + 1, IDX));

    for (int row = 1; row <= R; row++)
        for (int col = 1; col <= C; col++)
            if (arr[col][row] != IDX) // 현재 위치에 상어가 존재하는 경우
            {
                int c = col, r = row;
                Shk curr = arr[col][row];

                if (curr.d == UP || curr.d == DOWN)
                {
                    curr.s %= (R - 1) * 2;           // 필요 없는 행동 제거
                    for (int i = 0; i < curr.s; i++) // 상어를 진행 방향으로 한 칸씩 이동시킴
                    {
                        if (r == 1 && curr.d == UP)
                            curr.d = DOWN;
                        else if (r == R && curr.d == DOWN)
                            curr.d = UP;

                        r += dim_row[curr.d];
                    }
                }
                else if (curr.d == LEFT || curr.d == RIGHT)
                {
                    curr.s %= (C - 1) * 2;
                    for (int i = 0; i < curr.s; i++)
                    {
                        if (c == 1 && curr.d == LEFT)
                            curr.d = RIGHT;
                        else if (c == C && curr.d == RIGHT)
                            curr.d = LEFT;

                        c += dim_col[curr.d];
                    }
                }

                if (ret[c][r].z < curr.z) // 현재 도착한 상어가 이전에 존재하던 상어보다 큰 경우
                    ret[c][r] = curr;
            }

    arr = move(ret);
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int R, C, M; // 격자판의 크기 (2 ≤ R, C ≤ 100), 상어의 수 (0 ≤ M ≤ R×C)
    cin >> R >> C >> M;

    vector<vector<Shk>> arr(C + 1, vector<Shk>(R + 1, IDX));
    for (int i = 0; i < M; i++)
    {
        int r, c; // 상어의 위치 (1 ≤ r ≤ R, 1 ≤ c ≤ C)
        cin >> r >> c;

        auto &[s, d, z] = arr[c][r];
        cin >> s >> d >> z;
    }

    int result = 0;
    for (int people = 1; people <= C; people++)
    {
        for (int row = 1; row <= R; row++)
            if (arr[people][row] != IDX) // 사람 발밑에 상어가 존재하는 경우
            {
                result += arr[people][row].z, arr[people][row] = IDX;
                break;
            }

        moved_shk(arr, R, C);
    }

    cout << result;
}