// 2941 크로아티아 알파벳
// https://www.acmicpc.net/problem/2941
/*
    셋 (2,032KB, 0ms)
    시간 복잡도: O(N) (unordered set에서 find의 시간복잡도는 O(1))
    풀이)
    - 변경할 문자열을 셋에 넣은 후, 탐색중인 문자열이 존재하는지 판단.
    - 입력된 문자열의 [0]에서부터 탐색.
    만약 [i, i+1] 문자열이 셋에 존재할 경우, i++.
    만약 [i, i+2] 문자열이 "dz="인 경우, i += 2.
    이후 ans++.
    - 주의할 점은, i+1 혹은 i+2가 문자열의 범위를 벗어날 수 있으므로 예외 처리에 주의.
    - 셋에 "dz="를 넣3이므로; 셋에 2의 길이만 남김)
    etc.) 길이가 3인 문자열이 존재해서 좀 난잡해진듯
 */

#include <iostream>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int main()
{
    FAST_IO;

    string str;
    cin >> str;

    int ans = 0;
    unordered_set<string> us = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
    for (int i = 0; i < str.length(); i++)
    {
        if (i + 2 < str.length() && us.find(string(str.begin() + i, str.begin() + i + 3)) != us.end())
            i += 2;
        else if (i + 1 < str.length() && us.find(string(str.begin() + i, str.begin() + i + 2)) != us.end())
            i++;

        ans++;
    }

    cout << ans;
}