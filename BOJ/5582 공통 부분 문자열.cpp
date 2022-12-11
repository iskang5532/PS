// 2022-12-07
// 5582 공통 부분 문자열
// https://www.acmicpc.net/problem/5582
/*
    DP (2,168KB, 36ms)
    시간 복잡도: ?
    풀이)
    - dp를 이용하여 공통 부분 문자열을 구함.
    - 연속된 문자열을 탐색해야 하므로, 이전에 구한 dp값을 계속해서 저장하지 않고 문자열이 같을 때만 값을 저장한다.
    또한, 저장할 값은 대각선 방향에 있는 값으로, 이전에 구한 현재 탐색중인 문자열의 개수 - 1개로 구한 부분 문자열의 길이다.
    etc.) 문제에서 t가 연속으로 나타나는 것이라 해서 헷갈림
    참고)
    - 이론: https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcYlE3S%2FbtqCvxtwlpJ%2FVMcA4jeZFUuPZWsXCaaFpK%2Fimg.png (https://gusdnd852.tistory.com/173)
    - 반례: https://www.ioi-jp.org/joi/2007/FinalRound/index.html
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 4'003 // max s.length()

int main()
{
    FAST_IO;

    string s1, s2;
    cin >> s1 >> s2;

    int ans = 0;
    vector<int> prev(MAX, 0);
    for (int i = 1; i <= s1.length(); i++)
    {
        vector<int> cur(MAX, 0);
        for (int j = 1; j <= s2.length(); j++)
            if (s1[i - 1] == s2[j - 1]) // 문자가 같을 경우, 이전에 구한 부분 문자열의 길이를 가져옴
                ans = max(ans,
                          cur[j] = prev[j - 1] + 1);
        prev = cur;
    }

    cout << ans;
}

// ba
// aba
//     a b a
//   0 0 0 0
// b 0 0 1 0
// a 0 1 0 2