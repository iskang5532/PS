/* 
 * 1535 안녕
 * DP, knapsack
 * 시간 복잡도: O(nm)? (dp를 생성할 떄의 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/1535
 * etc.) 잃은 체력에 대해 얻을 수 있는 기쁨을 구하는 식으로 작성.
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> l(n), j(n);
    for (auto &elem : l)
        cin >> elem;
    for (auto &elem : j)
        cin >> elem;

    const int hp = 99; // 잃을 체력이기 때문에 100이 아닌 99
    vector<int> curr(hp + 1, 0), prev(hp + 1, 0); // dp[i]는 체력을 i만큼 잃었을 때 얻을 수 있는 기쁨
    for (int i = 0; i < n; i++) 
    {
        for (int pos = l[i]; pos <= hp; pos++)
            curr[pos] = max(prev[pos], j[i] + prev[pos - l[i]]);
        prev = curr;
    }

    cout << curr.back();
}