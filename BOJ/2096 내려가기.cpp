/* 
 * 2096 내려가기
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2096
 * ETC.) 메모리 제한에 주의.
 * 첫 풀이에서는 문제를 잘못 읽어 n*n과 같은 정사각형이 주어지는 줄 알았는데, 가로의 크기는 3으로 고정이었음.
 * 두 번째에서는 메모리 제한에 걸림.
 * 이를 해결하기 위해, 3*2 배열 두 개를 사용하여 입력되는 값을 이용한 현재까지의 최댓값 저장과 이를 갱신해주기 위한 이전 값 저장을 해줌.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
#define LEFT 0
#define MID 1
#define RIGHT 2
#define MAX_ROW 3

struct P
{
    int _min, _max;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;
    P prev[MAX_ROW] = {{0, 0}, {0, 0}, {0, 0}}; // 이전 값 저장. 첫 입력에서의 이전 값은 없으므로 0으로 고정
    P curr[MAX_ROW];                            // col번째 위치까지의 최댓값 및 최솟값을 저장. 저장 이후 prev에 옮겨줌
    for (int col = 0; col < n; col++)
    {
        int l, m, r; // 0 <= 9
        cin >> l >> m >> r;

        // 현재 col까지의 최솟값 및 최댓값 구하기
        // 현재 위치(row)로 올 수 있는 이전 위치(col, row)에서의 적절한 값을 가져와 입력된 값과 더해줌
        curr[LEFT]._min = l + min(prev[LEFT]._min, prev[MID]._min);
        curr[LEFT]._max = l + max(prev[LEFT]._max, prev[MID]._max);

        curr[MID]._min = m + min({prev[LEFT]._min, prev[MID]._min, prev[RIGHT]._min});
        curr[MID]._max = m + max({prev[LEFT]._max, prev[MID]._max, prev[RIGHT]._max});

        curr[RIGHT]._min = r + min(prev[RIGHT]._min, prev[MID]._min);
        curr[RIGHT]._max = r + max(prev[RIGHT]._max, prev[MID]._max);

        for (int i = 0; i < MAX_ROW; i++) // 갱신된 현재 값을 이전 값으로 만들어 줌
            prev[i] = curr[i];
    }

    // curr의 세 값들 중 최댓값 및 최솟값을 확인하여 저장
    int _min = min({curr[LEFT]._min, curr[MID]._min, curr[RIGHT]._min});
    int _max = max({curr[LEFT]._max, curr[MID]._max, curr[RIGHT]._max});

    cout << _max << " " << _min;
}