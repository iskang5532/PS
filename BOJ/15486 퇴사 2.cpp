/*
    15486 퇴사 2
    DP (19,480KB, 216ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/15486
    풀이)
    - dp[i] = k일 경우, i일까지 얻을 수 있는 최대 이익은 k.
    - 3일째일 경우, 3일째에 얻을 수 있는 최대 금액을 dp[3]에 저장한 이후, 3일째의 상담 금액을 3+t의 위치에 넣어줌. (단, max로 넣어줘야 함.)
    - 주의할 점은, 예제 2번과 같이 마지막 날에 하루 짜리 상담이 존재할 수 있음. 이 경우, 마지막 날에 p만큼 금액을 추가시켜 줘야 함. (혹은 n+1번쨰와 비교해서 더 큰 값으로)
    etc.) 탑다운 방식인가 싶어서 해보려 했으나 구현에서 실패.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 1'500'000 + 1 + 50
#define first t
#define second p
typedef pair<int, int> pii; // 상담 시간 t, 금액 p

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; //  1 ≤ n ≤ 1,500,000
    cin >> n;
    vector<pii> arr(n); // 1 ≤ Ti ≤ 50, 1 ≤ Pi ≤ 1,000
    for (auto &[t, p] : arr)
        cin >> t >> p;

    int dp[MAX];
    fill(dp, dp + MAX, 0);
    for (int i = 0; i <= n; i++)
    {
        auto [t, p] = arr[i];
        dp[i] = max(dp[i], dp[i - 1]);
        dp[i + t] = max(dp[i + t], dp[i] + p); // 상담 금액을 추가한 최대 이익을 +t의 위치로
    }
    cout << max(dp[n - 1], dp[n]);
}