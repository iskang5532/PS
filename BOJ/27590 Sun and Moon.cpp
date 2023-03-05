// 2023-02-28
// 27590 Sun and Moon
// https://www.acmicpc.net/problem/27590
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - ds와 dm이 서로 같아질 때까지 연산 후, 연산 횟수를 출력한다.
    - ds와 dm은 각각 ys와 ym을 넘길 수 없다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int ds, ys, dm, ym;
    cin >> ds >> ys >> dm >> ym;

    int ans = 0;
    while (ds != dm)
    {
        ++ds %= ys, ++dm %= ym;
        ans++;
    }

    cout << ans;
}