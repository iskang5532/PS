// 2023-03-26
// 10836 여왕벌
// https://www.acmicpc.net/problem/10836
/*
    구현 (3,952KB, 2,000ms)
    시간 복잡도: ?
    풀이)
    - m^2을 n번 수행할 경우 TLE.
    - 제일 왼쪽 열과 제일 위쪽 행을 제외한 나머지 값은 해당 위치의 첫 번째 행의 값과 동일하다.
    이를 이용하여 m^2의 연산을 하지 않아도 해당 위치의 값을 구할 수 있다.
    etc.) 어려웠던 문제.
    - 삼항연산자 반환값은 뒤에 적어야 함.
    - n번의 반복문 안에서 board의 값을 저장할 때, 작성한 코드에 따라 TLE 여부가 갈림.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 703 // max m

int board[MAX][MAX];

int main()
{
    FAST_IO;

    int m, n; // 크기 m(2 ≤ m ≤ 700), 날짜 수 n(1 ≤ n ≤ 1,000,000)
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        int y = m - 1, x = 0;

        int cnt;
        for (int j = 0; j < 3; j++)
        {
            cin >> cnt;
            while (y > 0 && cnt-- > 0)
                board[y--][x] += j;
            while (cnt-- > 0)
                board[y][x++] += j;
        }
    }

    for (int y = 0; y < m; y++, cout << endl)
        for (int x = 0; x < m; x++)
            cout << 1 + board[(x == 0) ? y : 0][x] << ' '; // 제일 왼쪽 열과 제일 위쪽 행인지 확인하여 값을 출력
}