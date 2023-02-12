// 2023-01-30
// 27210 신을 모시는 사당
// https://www.acmicpc.net/problem/27210
/*
    누적 합 (2,412KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 각 방향의 최댓값을 구한 후 더 큰 값을 출력한다.
    - 바라보는 방향이 기준 방향 dir과 같을 경우 pSum++, 다를 경우 pSum--하며, 최대 sum값을 저장하여 반환한다.
    만약 음수가 될 경우, 해당 위치까지는 사용하지 않으면 되므로 0으로 대체한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n
#define LEFT 1
#define RIGHT 2

int n, v[MAX]; // 돌상의 개수 n(1 ≤ n ≤ 100,000)

int get_ans(int dir) // dir: 바라볼 방향 (= 기준)
{
    int ret = 0, pSum = 0; // 최댓값 ret, 누적 합 pSum
    for (int i = 0; i < n; i++)
    {
        pSum += (v[i] == dir ? 1 : -1); // 기준 방향과 일치하는가?
        pSum = max(pSum, 0);

        ret = max(ret, pSum);
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];

    cout << max(get_ans(LEFT), get_ans(RIGHT));
}