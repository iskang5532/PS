// 17413 단어 뒤집기 2
// https://www.acmicpc.net/problem/17413
// 2022-04-04
/*
    구현 (2,592KB, 0ms)
    풀이)
    - 공백이 포함된 입력이므로 getline을 이용하여 문자열을 입력받음.
    - 문자열을 뒤집어야 하는 경우가 있으므로, 문자열 s에 저장 및 최종적으로 출력할 문자열 ans.
    - 현재 문자가 열린 괄호('<')인 경우, 닫힌 괄호('>')가 나올 때까지 태그이다.
    즉, s와는 더 이상 관계가 없으므로 s를 뒤집은 후 ans에 추가.
    또한, 닫힌 괄호가 나올 때까지 문자를 그대로 저장한다.
    - 현재 문자가 공백(' ')인 경우, s를 뒤집은 후 ans에 추가.
    - 저장된 s를 ans에 추가하지 못하는 경우도 있으므로, s에 값이 존재할 경우 ans에 추가.
 */

#include <iostream>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string in;
    getline(cin, in);

    string ans;
    string s;          // 뽑아낸 문자열
    bool flag = false; // 현재 문자가 태그인가?
    for (const auto &c : in)
    {
        if (c == '<')
        {
            flag = true;
            if (s.size())
                reverse(s.begin(), s.end()), ans += s, s.clear();
        }

        if (flag)
        {
            ans.push_back(c); // 태그인 경우, 반전 없이 문자 그대로를 추가
            if (c == '>')
                flag = false;
        }
        else if (c == ' ')
            reverse(s.begin(), s.end()), ans += s + ' ', s.clear();
        else
            s.push_back(c);
    }
    if (s.size())
        reverse(s.begin(), s.end()), ans += s;

    cout << ans;
}