/*
    스티커 모으기(2) (코딩테스트 연습 > Summer/Winter Coding(~2018) > 스티커 모으기(2))
    DP
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12971
    풀이)
    - DP를 이용. (dp[i] = k일 때, i번째 스티커까지 뜯었을 때 얻을 수 있는 최댓값은 k)
    - 주어지는 원형의 스티커는 첫 번째 값과 마지막 값은 연결되어 있음.
    즉, 첫 번째 값과 마지막 값은 동시에 선택할 수 없음. 이에 따라 첫 번째 값을 선택할 시 마지막 값은 자동으로 선택할 수 없게 된다.
    만약 마지막 값이 나머지 값들보다 하염없이 크다면, 마지막 값을 선택해야 하는데, 이 경우 마지막 값을 선택할 수 없게 됨.
    따라서 마지막 값을 선택할 수 있게끔 하는 방법은, 첫 번째 값을 선택하지 않는 것.
    - 첫 번째 값을 선택할 때와 선택하지 않을 때의 두 경우에 대한 최댓값을 구한다. (DP 이용)
    - i번째 스티커를 선택할 때의 최댓값은 [i번째 스티커의 값 + i-2번째까지의 최댓값(= dp)] 혹은 [i-1번째까지의 최댓값]중 큰 값이다. (i까지 구한 값이 i-1보다 작을 수가 있으므로 i-1을 비교해줌)
    etc.) 어려웠음. 구현 문제인 줄 알았으나 DP 문제였음. DP 문제들은 DP라고 알아채는게 너무 어려운듯 싶음..
    참고)
    - 이론: https://yabmoons.tistory.com/485
 */

#include <vector>

using namespace std;

int solution(vector<int> sticker)
{
    int ans = 0;
    int n = sticker.size();
    if (n == 1) // 값이 하나인 경우에 대한 예외 처리
        return sticker.front();

    vector<int> dp(n, 0); // dp[i] = k일 때, i번째 스티커까지 뜯었을 때 얻을 수 있는 최댓값은 k

    // 첫 번째 스티커부터 뜯는 경우 (= 마지막 스티커 x)
    {
        dp[0] = dp[1] = sticker[0]; // 첫 번째 스티커를 뜯어야 하기 때문에 dp[1] 또한 첫 번째 스티커 값으로

        for (int i = 2; i < n - 1; i++)
            dp[i] = max(sticker[i] + dp[i - 2], dp[i - 1]);
        ans = max(ans, dp[n - 2]);
    }
    // 두 번째 스티커부터 뜯는 경우 (= 마지막 스티커 o)
    {
        dp[0] = 0, dp[1] = sticker[1]; // 두 번째 스티커를 뜯어야 하므로 [0]은 사용하지 않은 값인 0을 넣음

        for (int i = 2; i < n; i++)
            dp[i] = max(sticker[i] + dp[i - 2], dp[i - 1]);
        ans = max(ans, dp[n - 1]);
    }
    return ans;
}

#include <iostream>
#define endl "\n"
int main()
{
    cout << "36?\t" << solution({14, 6, 5, 11, 3, 9, 2, 10}) << endl; // 36
    cout << "8?\t" << solution({1, 3, 2, 5, 4}) << endl;              // 8
    cout << "32?\t" << solution({5, 1, 16, 17, 16}) << endl;          // 32
    cout << "1004?\t" << solution({1004}) << endl;                    // 1004
    cout << "999?\t" << solution({999, 999}) << endl;                 // 999
}