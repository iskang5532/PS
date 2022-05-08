// 2022-05-05
// 19844 단어 개수 세기
// https://www.acmicpc.net/problem/19844
/*
    구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 현재 탐색 중인 문자열을 저장할 s, 문자의 개수를 저장할 ans.
    - 입력된 문장에서 문자를 하나씩 확인.
    만약 현재 문자가 알파벳일 경우, s에 저장.
    만약 현재 문자가 어포스트로피일 경우, 붙은 단어인지 확인. (= isValid(s, 다음 문자))
     - 다음 문자가 모음인지 확인. (= for in ch)
     - 문자열 s가 올바른 단어인지 확인. (= for in words; s는 마지막 문자를 제외하고서 수행)
    붙은 단어일 경우, ans++ 및 s 초기화.
    만약 띄어쓰기 혹은 하이폰일 경우, ans++ 및 s 초기화.
    - 주의해야 할 점은, 어포스트로피로 구성됐지만 단어가 아닌 문자열(이하 이전 문자열)은 이후에 오는 문자열에 영향을 미침. (단, 띄어쓰기 및 하이폰이 나오기 전까지)
    즉, 이후에 오는 문자열에 이전 문자열을 포함한 후에 단어 혹은 모음이 일치하는지 확인해야 함.
    etc.)
    - 어포스트로피 포함이지만 단어가 아닌 문자열이 뒤에 오는 문자열에 영향을 안미치는 줄 알아서 오래걸린 문제.
    - 디코 솔브닥 채널에서 친절하신 분이 반례를 알려주신 덕분에 성불한 문제.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

constexpr char ch[] = {'a', 'e', 'i', 'o', 'u', 'h'};
const string words[] = {"ce", "je", "ne", "me", "te", "se", "le", "la", "de", "que", "si"};

bool isValid(const string &s, char next_c)
{
    bool flag_1{}, flag_2{};
    for (const auto &word : words) // 단어가 일치하는가
        if (s == string(word.begin(), word.end() - 1))
            flag_1 = true;
    for (const auto &c : ch) // 모음이 일치하는가
        if (next_c == c)
            flag_2 = true;

    return flag_1 && flag_2;
}

int main()
{
    FAST_IO;

    string sentence;
    getline(cin, sentence);

    int ans = 0;
    string s;
    for (int i = 0; i < sentence.length(); i++)
    {
        char c = sentence[i];

        if ('a' <= c && c <= 'z')
            s += c;
        else if (c == '\'')
        {
            if (isValid(s, sentence[i + 1]))
                ans++, s.clear();
        }
        else if (c == ' ' || c == '-')
            ans++, s.clear();
    }

    cout << ans + 1;
}