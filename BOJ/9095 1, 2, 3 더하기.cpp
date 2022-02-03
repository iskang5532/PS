// 9095 1, 2, 3 더하기
// https://www.acmicpc.net/problem/9095
/*
    DP (2,020KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - DP[i] = k일 때, 값 i를 만들 수 있는 경우의 수는 k.
    - [4]를 구할 시
    4는 3에서 +1인 값이다. 이는 3을 만들 수 있는 모든 경우에서 +1을 해주면 된다. ([3]에서 수 1을 사용)
    즉, [3]을 구하여 [4]에 넣는다.
    4는 2에서 +2의 값이기도 하다. 즉, 위와 같은 이유로 [2]를 구하여 [4]에 더한다.
    마지막으로, 4는 1에서 +3이기도 하다. 이 또한 위와 같은 이유로 [1]을 구하여 [4]에 더한다.
    - [5]를 구할 시
    [4], [3], [2]까지 구한 후 [5]에 추가해준다. 이후 [1]을 구할 순서인데, [1]은 구하지 않는다.
    수 1, 2, 3만을 이용해서이다.
    etc.) 거의 하루종일 고민한 문제. 보일듯 하면서 안보였던 점화식..
    - [1], [2], [3], [4]의 결과는 각각 [1], [2], [4], [7]이다.
    이를 봤을 때, i번째의 값은 이전의 세 값을 더하면 얻을 수 있다는 걸 알 수 있다.
    참고)
    - 이론: https://jyami.tistory.com/15
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10 + 1

int main()
{
    FAST_IO;

    int dp[MAX];
    dp[1] = 1, dp[2] = 2, dp[3] = 4;
    for (int i = 2; i < MAX; i++)
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 1 ≤ n ≤ 10
        cin >> n;
        cout << dp[n] << endl;
    }
}