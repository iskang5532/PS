// 2022-07-19
// 25215 타이핑
// https://www.acmicpc.net/problem/25215
/*
    그리디 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 연속된 대소문자의 개수를 저장할 sum[]. (sum[i] = k일 때, i에서부터 연속되는 대소문자는 k개 (s[i]에 따라 대소문자 결정))
    - 별표, 즉 쉬프트의 여부를 저장할 onShift. 만약 onShift가 false일 경우 소문자, true일 경우 대문자이다.
    - sum값을 이용하여 최소 횟수를 구함.
    - sum[i]를 cnt라 하고 현재 문자 s[i]를 c라고 한다.
    - cnt == 1일 경우, c와 쉬프트를 비교한다.
    만약 c가 대문자이면서 쉬프트키가 켜져 있거나, 소문자이면서 쉬프트키가 꺼져 있는 경우, 알파벳 버튼을 누르기만 하면 되므로 ans += 1.
    서로 다른 경우, 쉬프트키를 누른 후 알파벳 버튼을 누르거나, 알파벳 버튼을 누른 후 별을 눌러야 한다.
    그러나, 연속된 횟수가 1이다. 즉, 다음에 오는 문자는 현재 쉬프트와 같은 대소문자일 것이다. (c와 쉬프트가 서로 다르므로)
    이는 후자의 알파벳 버튼을 누른 후 별표를 누르는 것이 최소 횟수가 된다. (= ans += 2)
    - sum[i] >= 2일 경우, 연속된 횟수 cnt만큼 더한다.
    이때, 만약 쉬프트와 다를 경우, 쉬프트키를 반전한다. (= ans++)
    etc.) DP?
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 3'003 // max s.length

bool isSame(bool onShift, char c) // 소문자 or 대문자가 같은지 확인
{
    return (onShift && isupper(c)) || !onShift && islower(c);
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;
    int sum[MAX]{}; // sum[i] = k일 때, i에서부터 연속되는 대소문자는 k개 (s[i]에 따라 대소문자 결정)
    for (int i = 1, pos = 0, cnt = 1; i <= s.length(); i++)
    {
        if (i == s.length())
            sum[pos] = cnt;

        isupper(s[i]) == isupper(s[i - 1]) ? cnt++
                                           : (sum[pos] = cnt, cnt = 1, pos = i);
    }

    int ans = 0;
    bool onShift = false;
    for (int i = 0; i < s.length();)
    {
        int cnt = sum[i];
        char c = s[i];
        if (cnt == 1)
            ans += (isSame(onShift, c) ? 1 : 2); // 별표 여부 판별
        else
        {
            ans += cnt;
            if (!isSame(onShift, c)) // 쉬프트키 여부 판별
                ans++, onShift = !onShift;
        }

        i += cnt;
    }

    cout << ans;
}