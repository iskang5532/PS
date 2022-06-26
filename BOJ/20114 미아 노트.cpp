// 2022-06-20
// 20114 미아 노트
// https://www.acmicpc.net/problem/20114
/*
    문자열 (2,088KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 복원한 문자열을 저장할 ans.
    - h개 문자열의 앞에서부터 w개의 문자를 확인.
    만약 확인한 문자가 '?'가 아닐 경우, 문자 추가.
    만약 확인한 모든 문자가 '?'일 경우, '?' 추가.
    - 이후 다음 위치인 w+1번째로 옮긴 후 마찬가지로 확인.
    - 모든 문자를 확인했다면, ans 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003

int main()
{
    FAST_IO;
    int n, h, w; //  문자열의 길이 n(1 ≤ N ≤ 100), 세로 h, 가로 w (1 ≤ H ≤ 10, 1 ≤ W ≤ 10)
    cin >> n >> h >> w;

    char board[MAX][MAX];
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w * n; x++)
            cin >> board[x][y];

    string ans;
    for (int dep = 0; dep < n; dep++)
    {
        char c = '?';
        for (int x = w * dep; x < w * dep + w; x++)
            for (int y = 0; y < h; y++)
                if (board[x][y] != '?')
                    c = board[x][y];
        ans.push_back(c);
    }

    cout << ans;
}