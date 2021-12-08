/*
    1106 호텔
    DP Knapsack (2,804KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1106
    풀이)
    - dp[i][j] = k일 때, i번쨰 도시까지 j원을 썼을 때 얻을 수 있는 최대 인원은 k.
    - 기존 가방 문제와 접근하는 법이 살짝 달랐다.
    기존 문제는 무게 w까지 채울 수 있는 최대 가치 v를 구했다면, 이 문제는 가치를 이용해 일정 무게에 도달해야 한다는 점이었다.
    - 0원부터 금액 i에 대한 dp를 탐색. 중간에 dp[i]의 값이 c 이상이 될 경우 i를 출력.
    etc.)
    - 그리디로 풀려 했으나 실패. 이유는 구한 구객 == c이 아니어도 돼서
    - 색다른 접근법이었음
    - MAX 구하기가 사알짝 어려웠음
    참고)
    - 어썸한 출력 방법: https://blog.naver.com/jinhan814/222308504476
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100'000 + 1 // 고객 당 비용이 100일 때, 1k명을 채우기 위한 비용은 100k

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int c, n; // 필요 고객 c(1 ≤ c ≤ 1k), 도시의 개수 n(1 ≤ n ≤ 20)
    cin >> c >> n;

    vector<int> v(n), p(n); // 비용 및 고객의 수 (1 ≤ vi, wi ≤ 100)
    for (int i = 0; i < n; i++)
        cin >> v[i] >> p[i];

    vector<int> curr(MAX, 0), prev(MAX, 0); // dp[i][j] = k일 때, i번쨰 도시까지 j원을 썼을 때 얻을 수 있는 최대 인원은 k
    for (int pos = 0; pos < n; pos++)
    {
        for (int i = v[pos];; i++)
        {
            curr[i] = max(prev[i], p[pos] + curr[i - v[pos]]);
            if (curr[i] >= c)
                break;
        }
        prev = curr;
    }

    for (int i = 0; curr[i] < c || !(cout << i); i++)
        ;
    // for (int i = 0; i < curr.size(); i++)
    //     if (curr[i] >= c)
    //     {
    //         cout << i;
    //         return 0;
    //     }
}