// 6324 URLs
// https://www.acmicpc.net/problem/6324
/*
    정규표현식 (2,076KB, 0ms)
    시간 복잡도: ?
    이론: https://blog.naver.com/jinhan814/222090272427
 */
#include <iostream>
#include <regex>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    // 괄호()로 묶는 이유는, 차후 sregex_iterator를 사용하기 위함.
    regex _REGEX(R"((\w+)://([\w.-]+)?:?(\d+)?/?(\S+)?)");
    // (\w+)          알파벳 대소문자와 숫자가 1회 이상 반복하는 위치. ([A-za-z0-9])
    // ://
    // ([\w.-]+)?   알파벳 대소문자와 숫자 및 '.', '-'가 1회 이상 반복하는 위치. 단, 없을 수도 있음.
    // :?
    // (\d+)?       숫자가 1회 이상 반복하는 위치. 단, 없을 수도 있음.
    // /?
    // (\S+)?       공백을 제욓나 나머지 문자가 1회 이상 반복하는 위치. 단, 없을 수도 있음.

    for (int i = 0; i < tc; i++) // tc
    {
        string s;
        cin >> s;

        auto it = *sregex_iterator(s.begin(), s.end(), _REGEX); // 괄호()로 묶인 정규표현식을 나눔

        string ans[4];
        for (int i = 0; i < 4; i++)
        {
            ans[i] = it[i + 1]; // sregex_iterator의 값은 [1]부터
            if (ans[i].empty())
                ans[i] = "<default>";
        }

        cout << "URL #" << i + 1 << endl;
        cout << "Protocol =" << ' ' << ans[0] << endl;
        cout << "Host     =" << ' ' << ans[1] << endl;
        cout << "Port     =" << ' ' << ans[2] << endl;
        cout << "Path     =" << ' ' << ans[3] << endl
             << endl;
    }
}