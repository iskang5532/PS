// 1912 연속합
// https://www.acmicpc.net/problem/1912
/*
    DP (2,412KB, 4ms)
    시간 복잡도: O(n)
    풀이)
    - n개의 값을 입력받아 v에 저장.
    - 연속합의 최댓값을 저장할 ans.
    - 첫 번째 값부터 탐색을 수행. 현재 값 v[i]에 이전 값 v[i-1]을 더할 시 v[i]보다 더 큰 지를 비교하며, 큰 값을 ans 및 v[i]에 저장.
    이후 v의 마지막 값까지 비교.
    - v[0]부터 탐색할 경우 v[0] + v[-1]이 되므로, v[0]의 값을 ans에 저장한 후 v[1]부터 탐색을 수행.
    etc.) 누적합?
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define MAX 100'000 + 1 //수의 최대 개수

int pSum[MAX]; // |vi| ≤ 1,000

int main()
{
    FAST_IO;

    int n; // 수의 개수 (1 ≤ n ≤ 100,000)
    cin >> n;
    for (int i = 0, idx; i < n; i++)
        cin >> idx, pSum[i] = max(idx, pSum[i - 1] + idx);

    int ans = pSum[0];
    for (int i = 1; i < n; i++)
        ans = max(ans, pSum[i]);

    cout << ans;
}

// int main()
// {
//     FAST_IO;

//     int n; // 수의 개수 (1 ≤ n ≤ 100,000)
//     cin >> n;
//     for (int i = 0; i < n; i++)
//         cin >> v[i];

//     int ans = -1e9;
//     for (int i = 0; i < n; i++)
//     {
//         v[i] = max(v[i], v[i] + v[i - 1]);
//         ans = max(ans, v[i]);
//     }

//     cout << ans;
// }