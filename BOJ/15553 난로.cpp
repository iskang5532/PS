// 2022-07-18
// 15553 난로
// https://www.acmicpc.net/problem/15553
/*
    그리디, 정렬 (2,680KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 입장하는 두 친구 간 시간 차이를 저장할 gap[].
    - 난로가 켜져 있는 시간의 최솟값은 친구의 수 n이 가장 이상적이다.
    다만, 성냥의 개수가 부족할 경우 입장 시간의 차이만큼 난로를 계속 켜줘야 한다.
    즉, 부족한 성냥의 개수만큼 작은 gap을 더한다.
    - ans의 기본값은 n이다. 즉, 친구가 입장할 때마다 난로를 켰다는 것이다.
    만약 성냥이 부족할 경우, 난로를 계속해서 키게 된다. 즉, 다른 친구가 입장할 때 켜지 않아도 된다. (= ans--)
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n, k; // 친구의 수 n(1 ≤ n ≤ 100,000), 성냥의 개수 k(1 ≤ k ≤ n)
    cin >> n >> k;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int gap[MAX]; // gap[i] = k일 때, i번과 i+1번 친구의 도착 시간의 차이는 k
    for (int i = 0; i < n - 1; i++)
        gap[i] = v[i + 1] - v[i];
    sort(gap, gap + n - 1); // 오름차순 정렬

    int ans = n;
    for (int i = 0; i < n - k; i++) // 부족한 성량의 개수만큼
        ans--, ans += gap[i];

    cout << ans;
}