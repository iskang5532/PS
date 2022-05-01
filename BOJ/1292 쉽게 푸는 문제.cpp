// 2022-04-26
// 1292 쉽게 푸는 문제
// https://www.acmicpc.net/problem/1292
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 첫 번째 값부터 탐색을 시작하며, 현재 탐색중인 값을 k, k가 나온 횟수를 cnt, 전체 수열에서의 현재 위치를 pos.
    - 만약 pos == a가 될 경우, 값 k를 ans에 저장.
    이후 pos == b가 될 때까지 값 k를 ans에 저장.
    - cnt가 k번 나올 경우, cnt를 초기화하며 k++. (다음 값을 탐색)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

int main()
{
    FAST_IO;

    int a, b; // 1 ≤ A ≤ B ≤ 1,000
    cin >> a >> b;

    ll ans = 0;
    int pos = 1;
    int k = 1, cnt = 0; // 탐색중인 값의 크기와 횟수
    while (pos <= b)
    {
        if (cnt == k)
            cnt = 0, k++;

        if (a <= pos && pos <= b)
            ans += k;

        cnt++, pos++;
    }

    cout << ans;
}