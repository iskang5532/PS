// 2022-05-20
// 6550 부분 문자열
// https://www.acmicpc.net/problem/6550
/*
    그리디 (2,392KB, 0ms)
    시간 복잡도: O(s2.length())
    풀이)
    - s1의 시작점 l, s2의 시작점 r.
    - s2[0]에서부터 탐색.
    만약 s1[l] == s2[r]일 경우, l++.
    만약 s1의 문자를 모두 탐색한 경우, "Yes" (= s1는 s2의 부분 문자열)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    string s1, s2;
    while (cin >> s1 >> s2)
    {
        bool valid = false;
        for (int l = 0, r = 0; r < s2.length(); r++)
        {
            if (s1[l] == s2[r])
                l++;
            if (l == s1.length())
                valid = true;
        }

        cout << (valid ? "Yes" : "No") << endl;
    }
}