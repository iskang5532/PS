// 2022-10-13
// 1789 수들의 합
// https://www.acmicpc.net/problem/1789
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - n의 최댓값을 구해야 하므로, 최대한 많은 수를 이용하여 s를 갖춰야 함.
    - 1부터 수를 하나씩 늘려가며 sum에 더한 후, s와 비교.
    sum에 i+1(다음 수)을 더했을 때 s를 초과할 경우, i가 정답이 됨.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

int main()
{
    ll s; // 1 ≤ s ≤ 4,294,967,295
    cin >> s;

    ll i = 0, sum = 0;
    while (sum + (i + 1) <= s)
        sum += ++i;

    cout << i;
}