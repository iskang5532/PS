// 2022-09-29
// 1411 비슷한 단어
// https://www.acmicpc.net/problem/1411
/*
    완전 탐색 (2,024KB, 0ms)
    시간 복잡도: O(n(n+1)(n+2)/6)?
    풀이)
    - 두 단어를 비교할 경우, 확인해야 할 것이 두 가지 있다.
    1. 동일한 위치에 연속한 문자의 개수가 동일한가? (단, 문자는 서로 달라도 됨)
    2. 이전에 나온 문자와 동일한 문자가 나중에 나왔을 경우, 다른 문자 또한 동일한 상황과 위치가 같은가? (단, 문자는 서로 달라도 됨)
    - 2번을 만족하는지를 확인하기 위해 각 단어의 문자마다 '번호'를 부여한다. (2번 같은 경우, "aba"와 "bab"가 만족. 번호 부여 시, 121)
    - 단어 속 문자의 '위치'에 부여된 번호를 저장할 cnt[][].
    - 단어 속 '문자'에 부여할 번호를 임시로 저장힐 ch[].
    - pos번 문자 c부터 확인. (부여할 번호는 k)
    만약 ch[pos]가 0일 경우, 이전에 c에 번호를 부여한 적이 없음. 그러므로 ch[pos] 및 cnt에 값을 갱신하며 k++.
    만약 ch[pos]가 0이 아닐 경우, 이전에 c에 번호를 부여한 적이 있음. 그러므로 cnt에만 값을 갱신.
    - 최종적으로 구한 cnt값과 2중 for문을 이용하여 각 단어마다 비교.
    만약 모든 pos에 대해 cnt[i][pos] == cnt[j][pos]가 성립할 경우, ans++.
    만약 어떠한 pos에 대해 cnt[i][pos] != cnt[j][pos]가 성립할 경우, 서로 다른 단어.
    etc.) 완탐 안되는줄. 하나 배웠음.
    참고)
    - 삼각수의 합: https://ko.wikipedia.org/wiki/%EC%82%BC%EA%B0%81%EC%88%98
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_N 103  // max n
#define MAX_LEN 53 // max str.len

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    string v[MAX_N];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    const int l = v[0].length();

    int cnt[MAX_N][MAX_LEN]{}; // cnt[i][j] = k일 때, i번 단어 속 j번 문자의 번호는 k. (풀이 참고)
    for (int i = 0; i < n; i++)
    {
        int ch['z' + 3]{}; // ch['a'] = k일 때, 문자 a의 번호는 k
        for (int pos = 0, k = 1; pos < l; pos++)
        {
            char c = v[i][pos];
            if (ch[c] == 0) // 번호를 부여받은 적이 없는 문자인가
                cnt[i][pos] = ch[c] = k, k++;
            else
                cnt[i][pos] = ch[c];
        }
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) // 완전 탐색
        for (int j = i + 1; j < n; j++)
        {
            bool valid = true;
            for (int pos = 0; pos < l && valid; pos++)
                if (cnt[i][pos] != cnt[j][pos])
                    valid = false;
            if (valid)
                ans++;
        }

    cout << ans;
}