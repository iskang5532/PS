/* 
 * 13398 연속합 2
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/13398
 * ETC.) 헷갈림
 * 참고: https://yangorithm.tistory.com/190 (설명)
 * 다른 풀이: https://yabmoons.tistory.com/617
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;

    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem; // -1k <= 1k

    int answer = arr[0]; // 기본 최댓값을 첫 번째 값으로

    // dp[i][j]이며 j == 0인 경우, 일반적인 연속 합 구하기이며
    // j == 1일 경우, 값을 제거한 경우에 대한 연속 합 구하기이다. (밑 주석 참고)
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0] = {arr[0], arr[0]};
    for (int i = 1; i < n; i++) // [1]부터
    {
        dp[i][0] = max(arr[i], dp[i - 1][0] + arr[i]); // 알반적인 연속 합 구하기

        // 1. 현재 값을 제거하는 경우
        // 값을 제거하지 않은 이전 값(j == 0)을 가져 옴 (여기서 j == 1인 값을 가져올 경우, 제거를 두 번 하게 되는 셈)
        // 2. 현재 값을 제거하지 않는 경우
        // 이전 제거된 값의 누적합을 가져와 현재 값과 더해줌
        dp[i][1] = max(dp[i - 1][0] + 0, dp[i - 1][1] + arr[i]);

        answer = max({answer, dp[i][0], dp[i][1]}); // 현재까지 구한 값들 중 최댓값을 구함
    }

    cout << answer;
}