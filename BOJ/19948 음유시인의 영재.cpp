// 2022-10-20
// 19948 음유시인의 영재
// https://www.acmicpc.net/problem/19948
/*
    구현 (2,156KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 스페이스바 횟수를 저장할 sp, 영자판 횟수를 저장할 cnt[].
    - 이전에 나온 문자를 저장할 prev.
    - 현재 문자의 종류에 따라 sp 혹은 cnt[] 감소.
    단, 현재 문자와 이전 문자가 같을 경우 감소시키지 않음.
    - 이전 문자가 스페이스바일 경우, 현재 문자를 ans에 추가.
    - 제목 ans 또한 영자판을 이용하여 눌러야 함.
    즉, 횟수가 남아 있는지 확인해야 함.
    - sp와 cnt[]에 남은 값을 이용하여 ans를 출력할 수 있는지 확인.
    참고)
    - 해결 팁: https://www.acmicpc.net/board/view/57614
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int cnt[26]; // 영자판 횟수 (1 ≤ cnt[] ≤ 10,000)

bool isValid(const string &s)
{
    for (const char &c : s)
        cnt[c - 'A']--;
    for (int i = 0; i < 26; i++)
        if (cnt[i] < 0)
            return false;
    return true;
}

int main()
{
    FAST_IO;

    string s;
    getline(cin, s), cin.clear();
    int sp; // 스페이스바 횟수 (1 ≤ sp ≤ 10,000)
    cin >> sp;
    for (int i = 0; i < 26; i++)
        cin >> cnt[i];

    string ans;
    char prev = ' '; // 이전에 나온 문자
    for (char &c : s)
    {
        if (prev == ' ' && c != ' ') // 이전 문자가 스페이스바였을 경우, 현재 문자 추가 (단, 현재 문자는 스페이스바가 아니어야 함)
            ans += toupper(c);
        if (prev != c)
            c == ' ' ? sp--
                     : cnt[(c | 32) - 'a']--;

        prev = c;
    }

    cout << (sp >= 0 && isValid(ans) ? ans : "-1");
}