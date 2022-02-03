// 3613 Java vs C++
// https://www.acmicpc.net/problem/3613
/*
    구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열이 정상적인 형태인지, Java형식 혹은 Cpp형식인지 확인.
    1. Java형인데 '_'가 있는가? or Cpp형인데 대문자가 있는가?
    2. 첫 글자가 대문자인가?
    3. '_'가 연속해서 존재하는가?
    4. 첫 문자 혹은 마지막 문자가 '_'인가?
    - 정상적인 형태의 문자열일 경우, Java는 Cpp형태로, Cpp는 Java형태로 바꿔준다.
    Cpp to Java
    - 각 문자를 탐색하며, '_'를 찾음.
    i번쨰 문자가 '_'인 경우, 현재 문자를 무시하고 i+1번쨰 문자를 대문자로 바꿔 넣음. ('_'이면서 다음 위치에 문자가 없는 경우도 있을 텐데, 이는 isValid에서 걸러줌)
    Java to Cpp
    - 각 문자를 탐색하며, 대문자를 찾음.
    i번째 문자가 대문자인 경우, '_'를 넣은 후 i번째 문자를 소문자로 바꿔 넣음
    etc.) 조건이 적어 보이지만, 굉장히 많은 듯한 기분.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222445439394
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
constexpr int Java = 1;
constexpr int Cpp = 2;

int language;

bool isValid(const string &s)
{
    if (s.find('_') == string::npos) // s는 Java형식
    {
        language = Java;

        if (isupper(s.front())) // 첫 문자가 대문자인가?
            return false;
    }
    else // s는 Cpp형식
    {
        language = Cpp;

        for (const auto &c : s) // 대문자가 있는가?
            if (isupper(c))
                return false;
        if (s.find("__") != string::npos) // '_'가 연속되는가?
            return false;
        if (s.front() == '_' || s.back() == '_') // 첫 문자 혹은 마지막 문자가 '_'인가?
            return false;
    }

    return true;
}

string toJava(const string &s)
{
    string ret;

    for (int i = 0; i < s.length(); i++)
        if (s[i] == '_')
            ret.push_back(toupper(s[i + 1])), i++;
        else
            ret.push_back(s[i]);

    return ret;
}

string toCpp(const string &s)
{
    string ret;

    for (int i = 0; i < s.length(); i++)
        if (isupper(s[i])) // 대문자인가?
        {
            ret.push_back('_');
            ret.push_back(tolower(s[i]));
        }
        else
            ret.push_back(s[i]);

    return ret;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    if (isValid(s)) // 유효한 문자열인가?
        if (language == Cpp)
            cout << toJava(s);
        else // langauge == Java
            cout << toCpp(s);
    else
        cout << "Error!";
}