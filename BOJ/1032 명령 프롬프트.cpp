// 1032 명령 프롬프트
// https://www.acmicpc.net/problem/1032
/*
    구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: O(n*len)
    풀이)
    - 입력된 n개의 문자열 중 임의의 문자열 s1을 선택. (비교 대상)
    선택한 s1을 이용하여 모든 문자열의 pos번째 문자와 비교.
    만약 s1과 s2의 pos번째 문자가 서로 다른 경우, 해당 위치의 문자는 '?'
    만약 s1과 모든 문자열의 pos번째 문자가 같은 경우, 해당 위치의 문자는 pos번째 문자를 넣음.
    - 완성된 문자열을 출력.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 50
    cin >> n;
    vector<string> v(n); // 1 ≤ vi.len ≤ 50
    for (auto &s : v)
        cin >> s;

    string ans = "";
    string s1 = v.front(); // 임의의 문자열 (비교 대상)
    for (int pos = 0; pos < s1.length(); pos++)
    {
        bool flag = false;
        for (const auto &s2 : v)
            if (s1[pos] != s2[pos]) // pos번째 문자가 서로 다른가?
                flag = true;

        if (flag)
            ans.push_back('?');
        else
            ans.push_back(v.front()[pos]);
    }

    cout << ans;
}