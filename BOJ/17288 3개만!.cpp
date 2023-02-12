// 2023-02-09
// 17288 3개만!
// https://www.acmicpc.net/problem/17288
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 연속된 횟수를 cnt에 저장 후, cnt가 1이 되는 순간이면서 이전 값이 3인 순간의 횟수를 구함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int ans = 0;
    int cnt = 1; // 연속된 횟수
    for (int i = 1; i < s.length(); i++)
    {
        int cur = s[i] - '0', prev = s[i - 1] - '0';
        if (cur - 1 == prev)
            cnt++;
        else
        {
            if (cnt == 3)
                ans++;
            cnt = 1;
        }
    }

    cout << ans + (cnt == 3);
}