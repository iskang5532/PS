/* 
 * 2580 스도쿠
 * backtracking
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2580
 * etc.) 값이 포함된 사각형 내 숫자를 판별하는 방법이 까다로웠음.
 * 추가로, 100ms 미만이 나온 코드를 봐도 이해가 잘 안돼서 아쉬움..
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 9 // 스도쿠의 크기
typedef pair<int, int> pii;

int sudoku[MAX][MAX]; // 빈 칸 포함된 입력 및 채워질 스도쿠
vector<pii> z;        // 빈 칸의 위치
bool sw = false;      // 스도쿠가 채워졌는지의 여부

bool isValid(const int col, const int row, const int k) // (col, row)위치에 k값이 적합한지 판단
{
    for (int i = 0; i < MAX; i++)
        if (sudoku[col][i] == k || sudoku[i][row] == k) // 가로 세로
            return false;

    int dy = col / 3, // 적합한 사각형까지의 y
        dx = row / 3; // 적합한 사각형까지의 x
    for (int y = 0 + (3 * dy); y < 3 + (3 * dy); y++) // 포함될 사각형 내
        for (int x = 0 + (3 * dx); x < 3 + (3 * dx); x++)
            if (sudoku[y][x] == k)
                return false;

    return true;
}

void dfs(const vector<pii>::iterator &itr = z.begin())
{
    if (itr == z.end()) // 빈 칸을 모두 사용한 경우 (= 스도쿠를 모두 채움)
    {
        sw = true; // 반복문을 빠져나갈 수 있도록 만들어줄 트리거
        return;
    }

    for (int k = 1; k <= 9; k++) // 빈 칸 (col, row)에 들어갈 값 k
    {
        auto [col, row] = *itr;
        if (isValid(col, row, k)) // (col, row)에 k가 들어가도 괜찮은지
        {
            sudoku[col][row] = k; // 빈 칸에 k를 넣음
            dfs(itr + 1);         // 다음 빈칸을 탐색

            if (sw == true) // 만약 빈 칸이 모두 채워진 경우
                return;
            sudoku[col][row] = 0; // 현재 k값은 아니었기 때문에 다시 빈 칸으로
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    for (int col = 0; col < MAX; col++)
        for (int row = 0; row < MAX; row++)
        {
            int k;
            cin >> k; // 1 <= 9
            sudoku[col][row] = k;

            if (k == 0) // 빈 칸일 경우
                z.push_back(pii{col, row}); // 빈 칸의 위치를 저장
        }

    dfs(); // 스도쿠를 모두 채움

    for (int col = 0; col < MAX; col++) // print
    {
        for (int row = 0; row < MAX; row++)
            cout << sudoku[col][row] << " ";
        cout << endl;
    }
}