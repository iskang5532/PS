// 2022-09-11
// 23843 콘센트
// https://www.acmicpc.net/problem/23843
/*
    그리디, 우선순위 큐 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    1. 충전에 필요한 시간이 가장 큰 기기를 우선으로 충전.
    2. m개의 충전 중인 기기 중 먼저 끝나는 기기 다음으로 남아 있는 기기를 충전.
    - 1번은 정렬을 이용. (입력된 값을 t에 저장 후 내림차순 정렬)
    - 2번은 우선순위 큐를 이용하여 구현. (우선순위 큐는 오름차순 정렬)
    t에 저장된 값을 m개 뽑은 후 우선순위 큐에 저장.
    이후, 가장 먼저 끝나는 기기 pq.top()을 꺼낸 후, 남아 있는 기기 t[i]의 값을 더한 후 pq에 다시 넣음.
    이는 pq.top()이 이용한 콘센트에 t[i]를 충전하는 것이며, 결과적으로 두 기기를 충전하기 위해서는 pq.top() + t[i]의 시간이 걸림.
    - 충전에 필요한 최소 시간을 구하기 위해서는, pq에 저장되는 값 중 최댓값을 기억해야 하므로, ans에 저장한다.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 10'003 // max n

int main()
{
    FAST_IO;

    int n, m; // 전자기기의 개수 n(1 ≤ n ≤ 10,000), 콘센트의 개수 m(1 ≤ m ≤ 10)
    cin >> n >> m;
    int t[MAX]; // 충전에 필요한 시간 (2^0 ​≤ ti ≤ 2^15, ti = 2^k (0 ≤ k ≤ 15, k는 정수))
    for (int i = 0; i < n; i++)
        cin >> t[i];

    sort(t, t + n, greater<int>()); // 내림차순 정렬

    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq; // 오름차순 정렬
    for (int i = 0; i < n; i++)
    {
        int cur = t[i];
        if (pq.size() + 1 > m) // 기기를 추가할 수 없는 경우 (모든 콘센트 사용)
            cur += pq.top(), pq.pop();
        pq.push(cur);

        ans = max(ans, cur);
    }

    cout << ans;
}