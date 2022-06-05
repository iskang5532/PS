// 2022-06-03
// 1213 팰린드롬 만들기
// https://www.acmicpc.net/problem/1213
/*
    그리디, 투 포인터? (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력받은 문자열로 팰린드롬을 구하는 함수 get_ans()를 수행.
    만약 만들 수 없으면 빈 문자열을 반환.
    - 문자의 개수를 센 후 cnt에 저장.
    - 여러 개의 팰린드롬이 존재할 수 있으나, 출력은 사전 순으로 앞서는 것을 출력해야 하므로 'A'를 우선으로 탐색 및 ans의 앞에서부터 저장.
    현재 탐색 중인 문자를 ans에 저장하되, 위치는 ans의 가장 앞인 l과 가장 뒤인 r, 중앙의 위치인 m.
    이후 저장할 때마다 l++, r--.
    - 현재 탐색 중인 문자의 개수가 홀수일 경우
     - 문자열의 길이가 짝수이거나 이전에 ans[m]에 값을 넣었을 경우, 빈 문자열 반환.
     - ans[m]에 문자를 넣은 후, cnt[c]--. (남은 문자의 개수를 0 혹은 짝수로 만듦)
    - 현재 문자의 개수가 남아 있으면, 남은 문자를 모두 소모하여 [l]과 [r]에 넣음.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

string get_ans(const string &s)
{
    string ans;
    ans.resize(s.length());

    int cnt['Z' + 1]{};
    for (const auto &c : s)
        cnt[c]++;

    int sz = s.length();
    int l = 0, r = sz - 1, m = sz / 2;
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (cnt[c] & 1) // 홀수개
        {
            if (!(sz & 1) || ans[m] != '\0') // 문자열의 길이가 짝수 or 중앙의 위치에 이미 문자를 넣었을 경우
                return "";
            ans[m] = c, cnt[c]--; // 문자의 개수를 0 혹은 짝수로 만듦
        }

        while (cnt[c])
        {
            ans[l] = ans[r] = c, cnt[c] -= 2;
            l++, r--;
        }
    }

    return ans;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    string ans = get_ans(s);
    cout << (ans.empty() ? "I'm Sorry Hansoo" : ans);
}