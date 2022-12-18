// 2022-12-12
// 13417 카드 문자열
// https://www.acmicpc.net/problem/13417
/*
    sol.1) 그리디 (2,020KB, 4ms)
    시간 복잡도: O(n)
    풀이)
    - 문자열의 앞 부분을 저장할 pre, 뒷 부분을 저장할 suf.
    - 현재 넣어야 될 문자 c를 이전에 만든 문자열과 비교하여 앞 혹은 뒤에 넣음.
    만약 c가 pre에 저장된 마지막 문자보다 사전 순으로 빠른 경우, pre에 추가.
    만약 c가 pre에 저장된 마지막 문자보다 사전 순으로 느린 경우, suf에 추가.
    - pre는 내림차순이므로, reverse시킨 후 suf와 같이 출력.
 */

#include <iostream>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n
#define endl '\n'

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 카드의 수(1 ≤ n ≤ 1,000)
        cin >> n;
        char c[MAX];
        for (int i = 0; i < n; i++)
            cin >> c[i];

        string pre, suf;
        for (int i = 0; i < n; i++)
            if (pre.empty() || c[i] <= pre.back())
                pre += c[i];
            else
                suf += c[i];

        reverse(pre.begin(), pre.end());
        cout << pre + suf << endl;
    }
}

/*
    sol.2) 그리디 (2,020KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 현재 넣어야 될 문자 c를 이전에 만든 문자열 anㄴ와 비교하여 앞 혹은 뒤에 넣음.
    만약 c가 ans의 첫 번째 문자보다 사전 순으로 빠른 경우, ans의 앞에 추가.
    만약 c가 ans의 첫 번째 문자보다 사전 순으로 느린 경우, ans의 뒤에 추가.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n
#define endl '\n'

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 카드의 수(1 ≤ n ≤ 1,000)
        cin >> n;
        char c[MAX];
        for (int i = 0; i < n; i++)
            cin >> c[i];

        string ans;
        for (int i = 0; i < n; i++)
            if (ans.empty() || c[i] <= ans.front())
                ans = c[i] + ans;
            else
                ans += c[i];

        cout << ans << endl;
    }
}