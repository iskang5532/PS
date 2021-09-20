/* 
 * 9663 N-Queen
 * brute_force
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/9663
 * etc.) row 반복문의 위치가 헷갈렸으며, 퀸이 놓일 자리가 적합한지 판단하는 과정에서 꽤 힘들었음.
 * 참고: https://blog.naver.com/jinhan814/222065450993 (대각선 판단 여부)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 15

int N;                   // 체스판의 크게 및 퀸의 개수 (1 <= N <= 15)
int ans = 0;             // 서로 공격할 수 없게 놓는 경우의 수
bool visited_x[MAX];     // 수직 라인. x[row] == true인 경우 n번째 줄(col)에서 row 위치에 퀸이 존재함 (= 서로 공격 가능)
bool visited_l[MAX * 2]; // 좌하단 대각선. l[k] == true인 경우 (k, 0)에서부터 (0, k)까지 하나의 퀸이 존재함
bool visited_r[MAX * 2]; // 우하단 대각선.

bool isValid(const int col, const int row)
{
    if (visited_x[row] || visited_l[col + row] || visited_r[N - 1 + col - row]) // 수직, 좌하단-우상측, 우하단-좌상측 확인
        return false;
    return true;
}

void dfs(int col = 0, int cnt = 0) // 놓인 퀸의 개수 cnt
{
    if (cnt == N) // N개의 퀸이 정상적으로 놓인 경우
    {
        ans++;
        return;
    }

    for (int row = 0; row < N; row++) // 현재 col에서 모든 row를 확인
        if (isValid(col, row)) // 현재 위치가 적합한지
        {
            visited_x[row] = true;
            visited_l[col + row] = true;
            visited_r[N - 1 + col - row] = true;
            dfs(col + 1, cnt + 1); // 다음 col 및 놓인 퀸의 개수 +1
            visited_x[row] = false;
            visited_l[col + row] = false;
            visited_r[N - 1 + col - row] = false;
        }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> N;
    dfs();

    cout << ans;
}

// n is 4, ans is 92
// [l]                      [r]
//  0   00   01   02  [03]   0
//  1   10   11  [12]  13    1
//  2   20  *21*  22   23    2
// [3] [30]  31  [32]  33    3
//  4                  []   [4]
//  5                        5
//  6                        6