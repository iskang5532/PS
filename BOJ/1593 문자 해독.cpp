// 2022-06-11
// 1593 문자 해독
// https://www.acmicpc.net/problem/1593
/*
    슬라이딩 윈도우 (7,544KB, 24ms)
    시간 복잡도: ?
    풀이)
    - 문자열 W에 존재하는 문자의 개수를 cnt에 저장.
    - 문자열 s에서 길이 g만큼의 문자열에 존재하는 문자의 개수를 센 후, cnt에 존재하는 값과 같은지 확인.
    문자의 개수가 같다는 것은 W로 만들 수 있는 순열이란 뜻.
    - next_permutation을 이용할 경우 3000!으로 TLE.
    - 슬라이딩 윈도우를 사용하여 s에서 g만큼 확인.
    etc.) 문제 이해가 어려웠음
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int cnt['z' + 1];

bool isValid()
{
    for (char c1 = 'A', c2 = 'a'; c2 <= 'z'; c1++, c2++)
        if (cnt[c1] != 0 || cnt[c2] != 0)
            return false;

    return true;
}

int main()
{
    FAST_IO;

    int g, S;
    cin >> g >> S;
    string w, s;
    cin >> w >> s;
    for (const auto &c : w)
        cnt[c]--;

    int ans = 0;
    for (int i = 0; i < g - 1; i++) // 슬라이딩 윈도우를 위한 작업
        cnt[s[i]]++;
    for (int l = -1, r = g - 1; r < S; l++, r++)
    {
        cnt[s[l]]--, cnt[s[r]]++;
        if (isValid())
            ans++;
    }

    cout << ans;
}