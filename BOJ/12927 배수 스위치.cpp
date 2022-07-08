// 2022-07-05
// 12927 배수 스위치
// https://www.acmicpc.net/problem/12927
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 첫 번째 전구부터 마지막 전구까지 확인.
    만약 i번 전구가 켜져 있는 경우, i번 전구를 끄며 i의 배수 번호를 가지는 전구의 상태를 모두 반전시킴.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max length

int main()
{
    FAST_IO;

    int n = 1;
    bool on[MAX]; // on[i] = true일 경우, i번 전구는 켜져 있음
    for (char c; cin >> c; n++)
        on[n] = (c == 'Y' ? true : false);

    int ans = 0;
    for (int i = 1; i < n; i++)
        if (on[i])
        {
            ans++;
            for (int pos = i; pos < n; pos += i)
                on[pos] = !on[pos];
        }

    cout << ans;
}