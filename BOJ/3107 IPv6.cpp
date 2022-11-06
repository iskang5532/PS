// 2022-11-02
// 3107 IPv6
// https://www.acmicpc.net/problem/3107
/*
    구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s에서 추출한 그룹을 저장할 group, 그룹의 개수를 저장할 cnt. (개수에는 0으로 이루어진 그룹은 포함하지 않음)
    - 콜론이 나올 때까지 문자를 group에 저장. (단, 문자는 콜론이 아니어야 함)
    콜론이 나왔을 경우, group에 저장된 문자열을 부족한 0과 함께 ans에 저장하며 cnt++.
    만약 연속된 콜론이 나왔을 경우, ans에 2개의 콜론을 저장.
    - 그룹의 개수가 8개가 아닌 경우, ans에 저장된 연속된 콜론을 0으로 바꿔줌.
    - ans에 저장된 값을 출력.
    ans에는 콜론이 없으므로 4개의 단어 사이에 콜론을 추가하여 출력.
    etc.) 헷갈림
    참고)
    - 반례: https://www.acmicpc.net/board/view/4180
            https://www.acmicpc.net/board/view/62919
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

string get_str(const string &group) // 부족한 0만큼 추가된 문자열을 반환
{
    string ret;
    for (int i = 0; i < 4 - group.length(); i++)
        ret += '0';
    ret += group;

    return ret;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    string ans;
    string group; // 그룹 문자열
    int cnt = 0;  // 그룹의 개수 cnt
    char prev = ' ';
    for (int i = 0; i < s.length(); i++)
    {
        char cur = s[i];
        if (cur != ':')
            group += cur;
        else if (group.size() && cur == ':') // 그룹 저장
            ans += get_str(group), group.clear(), cnt++;
        else if (prev == ':')
            ans += "::";

        prev = cur;
    }

    if (group.size())
        ans += get_str(group), group.clear(), cnt++;

    if (cnt != 8) // 콜론을 0으로 바꿔줘야 함
    {
        for (int i = 0; i < 8 - cnt; i++)
            group += "0000";
        ans.replace(ans.find("::"), 2, group);
    }

    for (int i = 0; i < ans.length(); i++) // 4개의 단어 사이에 콜론을 추가하여 출력.
    {
        if (i != 0 && !(i % 4))
            cout << ':';
        cout << ans[i];
    }
}