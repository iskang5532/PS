/* 
 * 2629 양팔저울
 * DP, knapsack
 * 시간 복잡도: O(nm)? (dp 구성 시의 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/2629
 * etc.) 사용된 추의 무게 w로 구슬의 무게 a를 확인할 수 있는 방법은 w - a == 0이 되는 순간이다.
 * 때문에, 추를 하나씩 추가하면서 만들 수 있는 무게를 구한 후, 구하고자 하는 값 a가 존재하는지 확인하면 된다. (주어진 추의 무게가 1, 4일 경우 1, 3, 4를 만들 수 있으며, 이는 곧 무게 1, 3, 4를 가진 구슬을 확인할 수 있음.)
 * 추가로, 모든 추의 무게 합은 최대 15k이지만 구슬의 무게는 40k으로 범위에서 벗어난 다는 점에 주의.
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 추의 개수 ( <= 30)
    cin >> n;
    int mx = 0; // 모든 추의 무게 합
    vector<int> arr(n); // 추의 무게 ( <= 500)
    for (auto &elem : arr)
    {
        cin >> elem;
        mx += elem; // 만들 수 있는 최대 무게
    }

    // 현재 사용하고 있는 추의 무게가 w, 현재 만들 수 있는 무게가 x일 때 |w - x| == i이 되어야 dp[i]의 값이 true가 된다.
    // 이 때 x의 값은 두 개이며, i를 기준으로 w만큼 떨어진 좌측값 l과 우측값 r이다.
    vector<bool> curr(mx + 1, false), prev(mx + 1, false); // dp[i] == true일 경우, 추를 이용해 무게 i를 만들 수 있음
    for (const auto &k : arr) // 추를 하나 씩 사용
    {
        curr[k] = true; // 스스로 만들 수 있는 무게
        for (int w = 0; w <= mx; w++) // dp[w]
        {
            int l = abs(w - k), r = w + k; // dp[w]를 만들 때 사용할 값.
            if ((0 <= l && prev[l] == true) || (r <= mx && prev[r] == true)) // dp[i]를 true로 만들 수 있는 값 x가 존재할 경우
                curr[w] = true;
        }
        prev = curr;
    }

    int m; // 구슬의 개수 ( <= 7)
    cin >> m;
    while (m--)
    {
        int k; // 구슬의 무게 ( <= 40k)
        cin >> k;

        if (k > mx || curr[k] == false)
            cout << 'N' << " ";
        else // curr[k] == true
            cout << 'Y' << " ";
    }
}

// 2, 5 and 5, 2
// 2, 5일 경우, dp[3]을 구하기 위해서는 좌측값(= l)을 알아야 하며, i가 -3(= 2 - 5)과 같이 크기가 상반될 수 있기 때문에 절댓값을 취해줌.
// 5, 2일 경우, dp[3]을 구하기 위해서는 우측값(= r)을 알아야 함.