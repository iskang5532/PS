// 1018 체스판 다시 칠하기
// https://www.acmicpc.net/problem/1018
/*
    완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 기준점을 정한 후, 기준점에서부터 길이 8만큼의 구역을 확인. (이때, OOB가 나오지 않도록 범위를 잡아줘야 함.)
    - 기준점, 즉 시작 칸의 색깔은 'B'와 'W' 두 가지 경우가 있음. 또한, 이는 bool의 형태로 생각할 수 있음.
    그러므로 두 가지 경우에 대해 각각 조사를 진행. (= cnt_a, cnt_b)
    - 현재 탐색중인 칸의 색은 2진법을 이용해 나타낼 수 있음. (가로 및 세로의 길이가 짝수(8)라 가능)
    이를 절대적인 색상이라고 봐주며, 시작점의 색상과의 조화 여부에 따라 카운팅. (= 체스판이 되는가>)
    시작점의 색상은 두 개가 있으므로 각각의 경우에 대해 저장을 해줘야 함. (= cnt_a, cnt_b)
    (cnt_a, cnt_b가 무엇인지가 중요하다기 보다는 두 가지 경우를 정확히 나눠 저장한다는 것에 의미를 둬야 함.
    이유는 ret를 구하는 과정에서 'W'의 개수 혹은 'B'의 개수보다는 변경시킨 최소 개수를 구하는 것이므로 개수만 알면 됨.)
    etc.) 헷갈리는 문제. 만약 8x8과 같이 짝수x짝수가 아닐 경우의 풀이는?
    - 예전에 못푼 문제였는데 풀어서 좋았음.
    참고)
 */

#include <iostream>
#include <algorithm> // min

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX 50 + 1

int n, m; // 8 ≤ n, m ≤ 50
char board[MAX][MAX];

int solution()
{
    int ret = INF;

    for (int i = 0; i <= n - 8; i++) // 기준점 (시작점; 원점)
        for (int j = 0; j <= m - 8; j++)
        {
            int cnt_a = 0, cnt_b = 0;
            for (int y = i; y < i + 8; y++)
                for (int x = j; x < j + 8; x++)
                {
                    bool color = (y + x) & 1; // 현재 위치의 색 (절대적)
                    if (board[y][x] == 'B' != color)
                        cnt_a++;
                    else
                        cnt_b++;
                }
            ret = min({ret, cnt_a, cnt_b});
        }

    return ret;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    cout << solution();
}