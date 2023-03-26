// 2023-03-22
// 9093 단어 뒤집기
// https://www.acmicpc.net/problem/9093
/*
    구현, 문자열 (2,024KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 문장 s에서 문자를 하나씩 검사.
    만약 현재 문자가 영어 알파벳인 경우, word에 추가.
    만약 현재 문자가 공백인 경우, word를 뒤집어 공백과 함께 ans에 저장.
    - 모든 단어를 검사했을 경우, ans 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    cin.ignore();
    string s;
    while (tc-- && getline(cin, s))
    {
        string ans;

        string word;
        for (int i = 0; i <= s.length(); i++) // 문자열의 길이 + 1만큼 조사하여 마지막 단어가 ans에 추가되게끔 만듦
            if (i != s.length() && s[i] != ' ')
                word += s[i];
            else
                ans += string(word.rbegin(), word.rend()) + ' ', word.clear();

        cout << ans << endl;
    }
}