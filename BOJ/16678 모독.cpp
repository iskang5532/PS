// 2022-09-12
// 16678 모독
// https://www.acmicpc.net/problem/16678
/*
    그리디, 정렬 (2,288KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 인접한 수의 차이가 최대 1이 나도록 만들면 되는 문제.
    - 입력된 수를 v[]에 저장한 후 오름차순 정렬.
    - 현재 탐색중 인 값 v[i]가 조건을 만족하기 위해 되어야 할 수(명예)를 k라 할 때, 다음 수는 k+1 이하여야 한다.
    또한, v[0]은 1이어야 한다.
    - v[i]가 k 미만일 경우, v[i-1]과 같다. 즉, v[i]는 해커를 고용하여 명예를 감소시킬 필요가 없다.
    - v[i]가 k와 같을 경우, v[i]는 해커를 고용하여 명예를 감소시킬 필요가 없다.
    그러나 v[i]는 v[i-1] + 1이므로, k 또한 +1이 되어야 한다.
    - v[i]가 k 초과일 경우, 해커를 고용하여 명예를 감소시켜야 한다.
    - 정답이 int형 범위를 벗어날 수 있음에 주의.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n; // 국회의원의 수 (1 ≤ n ≤ 100,000)
    cin >> n;
    int v[MAX]; // 명예 (1 ≤ vi ≤ 100,000)
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    ll ans = 0;
    for (int i = 0, k = 1; i < n; i++)
        if (v[i] >= k)
            ans += v[i] - k, k++;

    cout << ans;
}