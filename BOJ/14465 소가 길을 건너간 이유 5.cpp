// 14465 소가 길을 건너간 이유 5
// https://www.acmicpc.net/problem/14465
/*
    누적합, 슬라이딩 윈도우 (2,288KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 2중 for문으로 풀어보려 했으나 TLE 받을거라 생각하고 포기.
    - 크기가 k인 연속된 구간을 확인했을 때, 고장난 신호등이 존재하면 안된다.
    만약 존재할 경우, 고쳐야 할 신호등의 개수이다.
    이를 이용해 첫 번째 횡단보도부터 마지막 횡단보도까지 크기 k만큼 확인하며 고장난 신호등의 개수를 확인한 후, 가장 작은 값을 저장 후 출력한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n, k, b; // 횡단보도의 개수 n(1 ≤ N ≤ 100,000), 연속할 개수 k, 고장난 신호등 개수 b (1 ≤ B, K ≤ N)
    cin >> n >> k >> b;

    int pSum[MAX]; // pSum[i] = k일 때, i까지 고장난 신호등의 개수는 총 k개
    fill(pSum, pSum + MAX, 0);
    for (int i = 0; i < b; i++)
    {
        int x;
        cin >> x;
        pSum[x] = 1;
    }
    for (int i = 2; i <= n; i++)
        pSum[i] += pSum[i - 1];

    int ans = INF;
    int l = 1, r = k;
    while (r <= n)
    {
        int t = pSum[r] - pSum[l]; // 크기가 k인 {l, r}에서의 고장난 신호등의 개수 (= 고쳐야할 개수)
        ans = min(ans, t);

        l++, r++;
    }

    cout << ans;
}

// for (int r = k; r < n; r++)
// {
//     int t = pSum[r] - pSum[r - k];
//     ans = min(ans, t);
// }