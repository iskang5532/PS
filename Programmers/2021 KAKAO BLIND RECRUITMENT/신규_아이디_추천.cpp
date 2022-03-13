/*
    신규 아이디 추천 (코딩테스트 연습 > 2021 KAKAO BLIND RECRUITMENT > 신규 아이디 추천)
    구현
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/72410
    풀이)
    1) 문자열을 하나씩 확인하여 대문자는 소문자로, 허용할 수 없는 문자는 다음 문자를 확인.
    2) 문자열을 하나씩 확인하며, 마침표가 반복되는 경우 저장하지 않음. 또한 앞부분과 뒷부분이 마침표면 제외.
    3) 규칙이 적용된 문자열의 길이 확인.
    3-1) 빈 문자열인 경우, 5단계 및 7단계를 적용한 "aaa"를 반환.
    3-2) 16 이상인 경우, 15까지 자른 후 잘린 문자열의 마지막 문자가 마침표인지 확인.
    3-3) 2 이하인 경우, 길이가 3 이상이 될 때까지 마지막 문자를 추가.
    etc.) 적힌데로 구현해서 그런지 굉장히 지저분하다.
 */

#include <string>
using namespace std;

string rule_12(const string &str) // 소문자로 변환 및 특정 문자 제거
{
    string ret;
    for (const auto &c : str)
        if ('A' <= c && c <= 'Z')
            ret.push_back(c + 0x20);
        else if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == '-' || c == '_' || c == '.')
            ret.push_back(c);

    return ret;
}
string rule_34(const string &str) // 마침표 제거
{
    string ret;
    if (str.front() != '.')
        ret.push_back(str.front());
    for (int i = 1; i < str.length(); i++)
        if (str[i - 1] == '.' && str[i] == '.')
            continue;
        else
            ret.push_back(str[i]);
    if (ret.back() == '.')
        ret.pop_back();

    return ret;
}
string rule_6(const string &str) // 문자열 자르기
{
    string ret = str.substr(0, 15);
    if (ret.back() == '.') // rule_4
        ret.pop_back();

    return ret;
}
string rule_7(const string &str) // 문자열 추가
{
    string ret = str;
    char c = str.back();
    while (ret.length() <= 2)
        ret.push_back(c);
    return ret;
}

string solution(string new_id)
{
    new_id = rule_12(new_id); // 소문자로 변환 및 특정 문자 제거
    if (!new_id.empty())
        new_id = rule_34(new_id); // 마침표 제거

    if (new_id.empty()) // rule_5
        return "aaa";
    else if (new_id.length() >= 16)
        new_id = rule_6(new_id); // 문자열 자르기
    else if (new_id.length() <= 2)
        new_id = rule_7(new_id); // 문자열 추가

    return new_id;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << "1. " << ("bat.y.abcdefghi" == solution("...!@BaT#*..y.abcdefghijklm")) << endl;
//     cout << "2. " << ("z--" == solution("z-+.^.")) << endl;
//     cout << "3. " << ("aaa" == solution("=.=")) << endl;
//     cout << "4. " << ("123_.def" == solution("123_.def")) << endl;
//     cout << "5. " << ("abcdefghijklmn" == solution("abcdefghijklmn.p")) << endl;
//     cout << "6. " << ("000" == solution(".000.")) << endl;
// }