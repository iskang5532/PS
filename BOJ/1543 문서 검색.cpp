// 2022-05-19
// 1543 문서 검색
// https://www.acmicpc.net/problem/1543
/*
    그리디, 완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문서 s1에서 검색할 문자열 s2가 몇 번 존재하는지 확인.
    - s1[st]에서부터 s2의 길이만큼 탐색.
    만약 탐색한 문자열 s == s2일 경우, ans++ 및 s1의 다음 위치에서 다시 탐색. (탐색 시작 위치 st에서부터 s2의 길이만큼 떨어진 위치)
    만약 탐색한 문자열 s != s2일 경우, s1[st+1]부터 탐색.
    - 주의할 점은, 검색할 문자 s2가 문서 s1보다 길 수 있음.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s1, s2;
    getline(cin, s1), getline(cin, s2);

    if (s1.length() < s2.length()) // 검색할 문자열이 더 긴 경우
    {
        cout << 0;
        return 0;
    }

    int ans = 0;
    for (int st = 0; st <= s1.length() - s2.length();)
    {
        bool valid = true;
        for (int i = 0; i < s2.length() && valid; i++)
            if (s1[i + st] != s2[i])
                valid = false;

        if (valid)
            ans++, st += s2.length();
        else
            st++;
    }

    cout << ans;
}