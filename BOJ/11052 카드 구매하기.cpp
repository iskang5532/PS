/*
    11052 카드 구매하기
    DP, Knapsack (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/11052
    풀이)
    - dp[pos][i] = k일 경우, pos번쨰 카드 팩까지 이용했을 때 i개의 카드를 맞추기 위한 최대 금액은 k.
    - 카드팩을 하나씩 늘려가며 특정한 카드의 개수에 대한 최대 금액을 구함.
    i > pos, arr[pos] > arr[]이며 dp[pos][i]를 구하려고 할 때,
    현재 카드팩에 들어 있는 카드의 개수인 arr[pos](= cnt)를 i개에서 제외시킨 i - cnt를 이용해줌. (현재 카드팩에 존재하는 카드를 이용하여도 i개의 카드를 맞출 수 없음.)
    이는 이전에 구한 dp[i-cnt]의 값을 이용해주면 된다. (dp[i-cnt]에는 i-cnt개를 구했을 때의 최대 금액 k가 저장되어 있음.)
    이처럼 이전에 구한 값을 이용해야 하므로 2차원 배열을 이용해줌.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 1000 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 카드의 개수 (1 ≤ n ≤ 1k)
    cin >> n;

    int arr[MAX];
    for (int i = 1; i <= n; i++)
        cin >> arr[i]; // 1 ≤ k ≤ 10k

    vector<int> curr(n + 1, 0), prev(n + 1, 0); // dp[i] = k일 때, i개의 카드를 위한 최대 금액 k

    for (int pos = 1; pos <= n; pos++) // pos번째 카드팩까지 사용
    {
        for (int i = pos; i <= n; i++)                        // 현재 카드팩까지 사용해서 카드를 i개로 만들기 위한 최대 금액을 구함
            curr[i] = max(arr[pos] + curr[i - pos], prev[i]); // 현재 금액 + 카드팩에 들어 있는 카드의 수만큼 뺐을 때에 얻을 수 있는 최대 금액 or 이전에 구한 최대 금액

        prev = curr;
    }
    cout << curr.back();
}