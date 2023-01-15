// 2023-01-13
// 21966 (중략)
// https://www.acmicpc.net/problem/21966
/*
    문자열, 구현 (2,392KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s를 이용하여 세 가지 규칙에 맞춰 출력한다.
    1. s의 길이가 25 이하인 경우, s를 출력한다.
    2. s에서 앞과 뒷 부분을 자른 부분 문자열이 모두 같은 문장에 속하는지 확인한다.
    이는, 부분 문자열 안에 존재하는 마침표가 마지막 위치인지 확인하면 된다. (마지막 위치에 존재하지 않을 경우, 서로 다른 문장)
    3. 앞과 뒷 부분을 잘라 출력하되, 중간에 '......'을 같이 출력한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

bool isValid(const string &s) // 같은 문장에 속하는지 확인
{
    for (int i = 0; i < s.length(); i++)
        if (s[i] == '.' && i != s.length() - 1)
            return false;
    return true;
}

int main()
{
    FAST_IO;

    int n; // 글자의 길이 (2 ≤ n ≤ 100,000)
    cin >> n;
    string s;
    cin >> s;
    if (s.length() <= 25) // 1.
        cout << s;
    else if (isValid(string(s.begin() + 11, s.end() - 11))) // 2.
        cout << string(s.begin(), s.begin() + 11)
             << "..."
             << string(s.end() - 11, s.end());
    else // 3.
        cout << string(s.begin(), s.begin() + 9)
             << "......"
             << string(s.end() - 10, s.end());
}