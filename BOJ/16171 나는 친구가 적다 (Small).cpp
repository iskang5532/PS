// 2023-01-01
// 16171 나는 친구가 적다 (Small)
// https://www.acmicpc.net/problem/16171
/*
    문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s에서 숫자를 제거하여 새로운 문자열을 만든다.
    이후, string::find를 이용하여 s에 k가 포함되어 있는지 확인한다.
    만약 포함되어 있을 경우 1을, 아닐 경우 0을 출력한다.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 10'003

string get_s(const string &s)
{
    string ret; // s에서 숫자가 제외된 새로운 문자열
    for (const char &c : s)
        if (!('0' <= c && c <= '9'))
            ret += c;

    return ret;
}

int main()
{
    FAST_IO;

    string s, k;
    cin >> s >> k;
    s = get_s(s);

    cout << (s.find(k) != string::npos ? 1 // k가 포함되어 있는가?
                                       : 0);
}