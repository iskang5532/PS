// 2022-11-11
// 5177 출력 형식이 잘못되었습니다
// https://www.acmicpc.net/problem/5177
/*
    구현, 파싱 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자열을 압축하는 함수 comp를 구현 및 이용하여 입력받은 문자열 s1, s2를 압축함.
     - 알파벳 대소문자는 동일하므로, 소문자로 변환.
     - ',' 혹은 ';'는 동일하므로 ','로 변환.
     - 여는 괄호는 동일하므로 '['로 변환.
     - 닫는 괄호는 동일하므로 ']'로 변환.
     - 문자열의 시작이 공백이거나, 마지막이 공백일 경우 제거.
     - 연속된 공백은 하나의 공백으로 처리.
     - 특수 부호의 양 옆에 공백에 있을 시 제거.
    - 압축된 두 문자열을 서로 비교 후, 값을 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

string comp(const string &_s)
{
    string s;
    for (const char &c : _s)
        if (s.empty() || !(s.back() == ' ' && c == ' '))
            s += c;

    int st = 0, ed = s.length() - 1; // 공백을 제거 한 문자열의 시작점 st와 끝점 ed
    while (st < s.length() && s[st] == ' ')
        st++;
    while (ed > 0 && s[ed] == ' ')
        --ed;

    string ret;
    for (int i = st; i <= ed; i++)
    {
        char cur = s[i];
        if ('A' <= cur && cur <= 'Z')
            cur |= 32;
        else if (cur == ',' || cur == ';')
            cur = ',';
        else if (cur == '(' || cur == '{' || cur == '[')
            cur = '[';
        else if (cur == ')' || cur == '}' || cur == ']')
            cur = ']';
        else if (cur == ' ')
        {
            char prev = ret.size() ? ret.back() : '\0'; // 이전에 ret에 저장된 문자
            char next = i <= ed ? s[i + 1] : '\0';      // s의 다음 문자
            if (prev == '[' || prev == ']' || prev == ',')
                continue;
            else if (next == ')' || next == '}' || next == ']' || next == ',' || next == ';' || next == ':')
                continue;
        }

        ret += cur;
    }

    return ret;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    cin.ignore();
    for (int i = 1; i <= tc; i++)
    {
        string s1, s2;
        getline(cin, s1), getline(cin, s2);

        cout << "Data Set " << i << ": "
             << (comp(s1) == comp(s2) ? "equal" : "not equal") << "\n\n";
    }
}