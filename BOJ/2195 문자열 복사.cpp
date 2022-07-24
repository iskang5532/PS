// 2022-07-22
// 2195 문자열 복사
// https://www.acmicpc.net/problem/2195
/*
    그리디 (2,156KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자열 s의 각 문자의 위치를 저장할 v.  (v['z'] = {1, 3}일 경우, s에서 문자 'z'의 위치는 s[1], s[3])
    - 문자열 p의 i번째 문자를 선택한 후, v에 저장된 위치 pos를 이용.
    s[l]와 p[r]를 비교.
     - 만약 두 문자가 같은 경우, 다음 문자를 확인. (l++, r++)
     - 만약 두 문자가 다를 경우, 비교 종료.
     동일한 문자의 개수를 cnt에 저장.
    동일한 문자열의 길이 중 최댓값을 저장할 mx에 cnt를 저장.
    v에 저장된 모든 위치를 사용한 후, mx만큼 i를 옮김. (다음 확인할 문자는 mx만큼 떨어짐)
    참고)
    이론: https://codedrive.tistory.com/m/528
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s, p;
    cin >> s >> p;
    vector<int> v['z' + 1]; // v['z'] = {1, 3}일 경우, s에서 문자 'z'의 위치는 s[1], s[3]
    for (int i = 0; i < s.length(); i++)
        v[s[i]].push_back(i);

    int ans = 0;
    int pos_p = 0;
    while (pos_p < p.length())
    {
        int mx = 0; // 동일한 문자열의 길이 중 최댓값

        char c = p[pos_p];
        for (auto pos_s : v[c])
        {
            int cnt = 0; // 동일한 문자열의 길이
            while (pos_s < s.length() && pos_p + cnt < p.length())
                if (s[pos_s] == p[pos_p + cnt])
                    pos_s++, cnt++;
                else
                    break;

            mx = max(mx, cnt);
        }

        pos_p += mx;
        ans++;
    }

    cout << ans;
}