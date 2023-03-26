// 2023-03-25
// 3447 버그왕
// https://www.acmicpc.net/problem/3447
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자열에서 "BUG"를 찾아 지우는 함수를 만들어 사용.
    해당 함수는 "BUG"를 찾았을 경우 제거 후 true를 반환하며, 찾지 못한 경우 false를 반환.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

bool erase_bug(string &s) // "BUG"가 있으면 제거하며 true를 반환
{
    bool ret = false;

    string _s;
    for (int i = 0; i < s.length(); i++)
        if (i + 2 < s.length() && string(s.begin() + i, s.begin() + i + 3) == "BUG") // 현재 문자를 포함한 3개의 문자가 "BUG"인 경우
            i += 2, ret = true;
        else
            _s += s[i];

    s = _s;
    return ret;
}

int main()
{
    FAST_IO;
    string s;
    while (getline(cin, s))
    {
        while (erase_bug(s))
            ;

        cout << s << endl;
    }
}