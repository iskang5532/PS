// 2022-07-15
// 1689 겹치는 선분
// https://www.acmicpc.net/problem/1689
/*
    그리디 (9,712KB, 400ms)
    시간 복잡도: ?
    풀이)
    - 선분의 시작 좌표를 저장할 st[], 끝나는 좌표를 저장할 ed[].
    - 선분의 겹치는 개수를 저장할 sum.
    - st와 ed를 탐색. (st의 위치를 저장할 l, ed의 위치를 저장할 r)
     - 현재 탐색중인 st를 저장할 cur.
     - st를 하나씩 탐색할 때마다, sum++.
     이때, ed[r]의 값이 cur 이하인 경우, 즉 cur보다 이전 선분인 경우 sum--.
*/

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000'003 // max n

int main()
{
    FAST_IO;

    int n; // 선분의 개수(1 ≤ N ≤ 1,000,000)
    cin >> n;
    int st[MAX], ed[MAX];
    for (int i = 0; i < n; i++)
        cin >> st[i] >> ed[i];

    sort(st, st + n), sort(ed, ed + n);

    int ans = 0;
    for (int l = 0, r = 0, cur, sum = 0; l < n; l++)
    {
        cur = st[l], sum++;

        while (ed[r] <= cur)
            sum--, r++;

        ans = max(ans, sum);
    }

    cout << ans;
}