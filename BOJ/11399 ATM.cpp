// 11399 ATM
// https://www.acmicpc.net/problem/11399
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: O(logn + n)
    풀이)
    - 시간이 적게 걸리는 순으로 인출할 시, 가장 적은 시간이 나옴. 그러므로, 입력된 시간을 오름차순 정렬.
    - 이전까지 걸린 시간을 알고 있어야 하므로, sum에 저장함.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003

int main()
{
    FAST_IO;
    int n; // 사람의 수 N(1 ≤ N ≤ 1,000)
    cin >> n;
    int v[MAX]; // 인출에 걸리는 시간 (1 ≤ vi ≤ 1,000)
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    int ans = 0;
    int sum = 0; // 이전까지 사용된 시간의 합
    for (int i = 0; i < n; i++)
        ans += v[i] + sum, sum += v[i];

    cout << ans;
}