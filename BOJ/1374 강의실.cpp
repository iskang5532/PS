// 2022-07-13
// 1374 강의실
// https://www.acmicpc.net/problem/1374
/*
    그리디, 정렬 (2,680KB, 44ms)
    시간 복잡도: ?
    풀이)
    - 시작 시간과 종료 시간을 각각 저장할 배열 st[], ed[].
    - 사용중인 강의실의 개수를 저장할 sz.
    - 시작 시간과 종료 시간 사이에 다른 강의가 존재한다면, 강의실을 추가로 사용해야 함.
    만약 강의가 종료되었을 경우, 종료된 강의만큼 사용중인 강의실의 개수에서 제거.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int st[MAX], ed[MAX];
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        st[i] = b, ed[i] = c;
    }

    sort(st, st + n), sort(ed, ed + n);

    int ans = 0;
    for (int l = 0, r = 0, sz = 0; l < n; l++)
    {
        sz++;
        while (ed[r] <= st[l]) // 강의가 종료되어 사용중인 강의실 -1
            r++, sz--;

        ans = max(ans, sz);
    }

    cout << ans;
}