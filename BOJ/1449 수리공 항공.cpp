// 2022-08-10
// 1449 수리공 항승
// https://www.acmicpc.net/problem/1449
/*
    그리디, 정렬 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 최소한의 테이프를 이용해야 하므로, 테이프를 붙일 때 최대한 많은 파이프를 붙여야 한다.
    - 입력된 파이프의 위치를 정렬한 후, 가장 왼쪽에 존재하는 파이프부터 확인.
    - 가장 최근에 막은 파이프의 위치를 r이라 하며 현재 파이프 i가 r보다 클 시, i는 막지 않은 상태.
    그러므로, i에 테이프를 붙임. 이후, 길이 l만큼 인접한 파이프 또한 막히므로 r을 갱신.
    r값은 v[i] + l - 1 (1을 빼주는 이유는 v[i]를 포함해야 하므로)
    etc.)
    - 문제에 필요 없는 지문과 어색한 지문이 존재하여 다른 의미로 어려웠던 문제
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

int main()
{
    FAST_IO;

    int n, l; // 새는 곳의 개수 n, 테이프의 길이 l(1 ≤ n, l ≤ 1,000)
    cin >> n >> l;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    int ans = 0;
    int r = 0;
    for (int i = 0; i < n; i++)
        if (r < v[i])
            ans++, r = v[i] + l - 1;

    cout << ans;
}