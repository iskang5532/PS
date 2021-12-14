// 17218 비밀번호 만들기
// https://www.acmicpc.net/problem/17218
/*
    LCS, DP (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 두 문자열의 각 문자에 대한 LCS를 구해 2차원 배열인 dp에 저장.
    - dp의 끝자락(= [s1.len][s2.len]부터 탐색하며, 조건에 맞춰 문자열의 문자를 저장.
    s1[i-1] == s2[j-1]일 경우, 해당 문자열을 출력하며 i -= 1, j -= 1. (아마 현재 위치(dp[i][j])와 다음 두 위치(dp[i-1][j], dp[i][j-1])가 다르면서 다음 두 위치의 값이 같을 때인듯)
    그 외엔, dp[i]와 dp[j] 중 i가 크면 i쪽으로, j가 크면 j쪽으로 이동.
    dp의 범위를 벗어날 때까지 탐색을 계속해줌.
    - 이후 저장한 문자 출력.
    - 자세한 풀이는 참고 사이트에서 확인.
    etc.) 문자열을 구하는게 어려웠던 문제.
    참고)
    - 문자열 구하는 방법: https://www.geeksforgeeks.org/printing-longest-common-subsequence/
 */

#include <iostream>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 40 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    string s1, s2;
    cin >> s1 >> s2;

    int dp[MAX][MAX]; // dp[i][] = k일 때, s1[0]부터 s1[i]까지 s2와 비교하며 쌓은 LCS 길이는 k.
    for (int i = 0; i <= s1.length(); i++)
        for (int j = 0; j <= s2.length(); j++)
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    string ans;
    int i = s1.length(), j = s2.length();
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            ans.push_back(s1[i - 1]);
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) // i쪽 방향의 값이 더 큰 경우
            i--;
        else // j쪽 방향의 값이 더 큰 경우
            j--;
    }

    // print dp
    // for (int i = 1; i <= s1.length() && cout << endl; i++)
    //     for (int j = 1; j <= s2.length(); j++)
    //         cout << dp[i][j] << " ";
    reverse(ans.begin(), ans.end());
    cout << ans;
}