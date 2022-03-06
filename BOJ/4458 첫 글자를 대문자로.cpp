// 4458 첫 글자를 대문자로
// https://www.acmicpc.net/problem/4458
/*
    문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - getline으로 개행문자가 입력될 때까지 문자열을 받아 s에 저장.
    이후 s의 첫 문자를 대문자로 바꿔 출력하며, 그 외 문자열 또한 출력해줌.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        string s;
        getline(cin, s);
        cout << (char)toupper(s[0]) << string(s.begin() + 1, s.end()) << '\n';
    }
}
