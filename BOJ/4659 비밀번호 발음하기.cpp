// 2022-06-05
// 4659 비밀번호 발음하기
// https://www.acmicpc.net/problem/4659
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - a부터 z까지 문자 c가 자음인지 모음인지를 저장할 ch. (ch[c] == JA일 경우, 자음)
    - 연속된 자음 혹은 모음의 개수를 저장할 j, m. (j == 2일 경우, 연속된 자음의 개수는 2개)
    - 1번 조건 여부를 저장할 used_mo와 2, 3번 조건 여부를 저장할 valid.
    - 이전에 탐색한 문자를 저장할 prev.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define JA 0
#define MO 1

void print_ans(const string &s, bool valid)
{
    cout << "<" << s << ">"
         << " is " << (valid ? "" : "not ") << "acceptable." << endl;
}

int main()
{
    FAST_IO;

    int ch['z' + 1];
    for (char c = 'a'; c <= 'z'; c++)
        ch[c] = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ? MO : JA);

    string s;
    while (cin >> s)
    {
        if (s == "end")
            break;

        bool valid = true, used_mo = false;
        int j = 0, m = 0; // 연속된 자음 혹은 모음의 개수
        char prev = '\0';
        for (const auto &c : s)
        {
            if (ch[c] == JA)
                j++, m = 0;
            else if (ch[c] == MO)
            {
                used_mo = true;
                m++, j = 0;
            }

            if (j == 3 || m == 3 || (prev != 'e' && prev != 'o' && prev == c))
                valid = false;
            prev = c;
        }

        if (!used_mo)
            valid = false;
        print_ans(s, valid);
    }
}