// 14499 주사위 굴리기
// https://www.acmicpc.net/problem/14499
// 2022-04-04
/*
    구현 (2,020KB, 0ms)
    풀이)
    - 주사위의 값을 저장하며 주사위의 회전을 수행할 수 있는 구조체 dice를 구현.
    - 입력되는 k에 맞게 주사위를 회전시키며 값을 저장.
    etc.)
    - 문제에서 입력으로 받는 주사위의 좌표인 (x, y)에서 x는 서쪽에서부터 떨어진 거리, y는 북쪽에서부터 떨어진 거리이다.
    그러나 이 풀이는 기존 좌표를 사용한 문제를 풀 때와 동일하도록 x와 y를 바꾼 후 입력을 받음.
    참고)
    - 주사위 구현: https://blog.naver.com/jinhan814/222152108276
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 23 // max n, m

constexpr int dy[5] = {00, 0, 0, -1, 1}; // -, 동, 서, 남, 북
constexpr int dx[5] = {00, 1, -1, 0, 0};

struct Dice
{
    int B, D, F, U, L, R; // 2, 1, 5, 6, 4, 3

    void rotate_R() // 우측으로
    {
        int temp = L;
        L = D, D = R, R = U, U = temp;
    }
    void rotate_F() // 앞쪽으로
    {
        int temp = B;
        B = D, D = F, F = U, U = temp;
    }
    void rotate(int d)
    {
        if (d == 1) // 동
            rotate_R();
        else if (d == 2) // 서
            rotate_R(), rotate_R(), rotate_R();
        else if (d == 3) // 북
            rotate_F(), rotate_F(), rotate_F();
        else if (d == 4) // 남
            rotate_F();
    }
} dice;

int main()
{
    FAST_IO;

    int n, m, x, y, k; // 지도의 크기 n, m(1 ≤ n, m ≤ 20), 주사위의 좌표 x, y(0 ≤ x ≤ n-1, 0 ≤ y ≤ m-1), 명령의 개수 k (1 ≤ k ≤ 1,000)
    cin >> n >> m >> y >> x >> k;

    int board[MAX][MAX]; // 0 ≤ k ≤ 9
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            cin >> board[y][x];

    for (int i = 0; i < k; i++)
    {
        int d; // 동 서 북 남 = 1, 2, 3, 4
        cin >> d;

        auto [ny, nx] = pii{y + dy[d], x + dx[d]};
        if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
            continue;

        dice.rotate(d), y = ny, x = nx;

        if (board[y][x])
            dice.D = board[y][x], board[y][x] = 0;
        else
            board[y][x] = dice.D;

        cout << dice.U << endl;
    }
}

// input:
// 2 2 1 0 1
// 0 0
// 0 1
// 1
// ans:
// 0