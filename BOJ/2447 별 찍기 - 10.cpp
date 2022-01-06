// 2447 별 찍기 - 10
// https://www.acmicpc.net/problem/2447
/*
    sol.1) 재귀 (2,020KB, 260ms)
    시간 복잡도: ?
    풀이)
    - 현재 칸(= (i,j))의 값이 무엇인지를 파악.
    - len만큼 범위를 잡음.
     - 만약 현재 칸이 범위 안에서 중앙의 위치인 경우, ' '을 출력.
     - 만약 현재 칸이 범위 안에서 중앙의 위치가 아니며 범위가 1인 경우, '*' 출력.
     - 그 외일 시, 범위를 좁힌 후 다시 탐색.
    etc.) 손으로 그려서 패턴을 파악하는 것이 단순하고 쉬운듯
    참고)
    - 이론: https://winkite1226.tistory.com/119 (그림)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 6'561 + 1

void solution(int i, int j, int len)
{
    if (i / len % 3 == 1 && j / len % 3 == 1) // 중앙
        cout << ' ';
    else if (len == 1) // 중앙이 아니며 더 이상 탐색 불가
        cout << '*';
    else
        solution(i, j, len / 3);
}

int main()
{
    FAST_IO;

    int n;
    cin >> n; // 3^k (1 ≤ k < 8)

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            solution(i, j, n); // (i,j)의 값이 무엇인지 확인
        cout << endl;
    }
}

/*
    sol.2) 분할 정복 (44,072KB, 160ms)
    시간 복잡도: ?
    풀이)
    - 전체 영역을 9분할 시켜 탐색. [0,3), [0,3)
    - 나누어진 영역 중에서 가운데 영역은 공백. 즉, (1,1)은 공백이 되어야 함.
    그러므로 c값에 공백을 넣은 후, board에 저장할 때 사용.
    또한, 공백으로 지정된 곳을 분할시켜 탐색해도 공백이 되어야 하므로, 지속해서 c값을 공백으로 넣어줌. (n == 9에서 중앙의 3x3)
    etc.) 공백인 영역은 분할 시의 영역도 공백이 된다는걸 알아채야 했던 문제.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 6'561 + 1

char board[MAX][MAX];

void solution(int y, int x, int l, char c)
{
    if (l == 1)
    {
        board[y][x] = c;
        return;
    }

    int nl = l / 3;
    for (int _y = 0; _y < 3; _y++)
        for (int _x = 0; _x < 3; _x++)
            if (c == ' ' || _y == 1 && _x == 1) // 현재 영역이 ' 'or 가운데 영역
                solution(y + _y * nl, x + _x * nl, nl, ' ');
            // continue;
            else
                solution(y + _y * nl, x + _x * nl, nl, '*');
}

int main()
{
    FAST_IO;

    int n;
    cin >> n; // 3^k (1 ≤ k < 8)

    // fill(&board[0][0], &board[0][0] + sizeof(board) / sizeof(board[0][0]), ' ');
    solution(0, 0, n, '\0');

    for (int i = 0; i < n; i++) // print
    {
        for (int j = 0; j < n; j++)
            cout << board[i][j];
        cout << endl;
    }
}