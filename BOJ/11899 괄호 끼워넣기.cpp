// 2022-10-24
// 11899 괄호 끼워넣기
// https://www.acmicpc.net/problem/11899
/*
    문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 괄호의 여부에 따라 cnt에 저장.
    - 열린 괄호의 경우, cnt++.
    - 닫힌 괄호의 경우, cnt--.
    만약 cnt-- 시 음수가 될 경우, 열린 괄호가 필요함. (= ans++)
    - 모든 괄호를 확인 후, cnt의 값이 남아있을 경우 cnt만큼 닫힌 괄호가 필요함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int ans = 0;
    int cnt = 0; // 초과된 열린 괄호의 개수
    for (const char &c : s)
        if (c == ')')
            cnt == 0 ? ans++
                     : cnt--;
        else if (c == '(')
            cnt++;

    cout << ans + cnt;
}