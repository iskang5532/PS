// 2022-07-11
// 24524 아름다운 문자열
// https://www.acmicpc.net/problem/24524
/*
    그리디 (3,680KB, 12ms)
    시간 복잡도: ?
    풀이)
    - t의 각 문자가 몇 번째에 위치해 있는지를 저장할 pos.(pos[c] = k일 때, 문자 c는 t에서 k+1에 위치 (= t[k+1]))
    - s의 각 문자를 탐색하면서 t의 pos번째 위치 문자를 몇 개 만들 수 있는지를 저장할 cnt. (cnt[pos] = k일 때, 문자 t[pos]를 만들 수 있는 개수는 k개)
    - s의 각 문자를 탐색. (현재 문자를 c, t에서 c 이전 값의 위치를 prev)
    만약 c가 t에서 첫 번째 문자인 경우, cnt++.
    만약 c가 t에 존재하면서 이전에 탐색하여 prev 문자가 존재할 경우, prev 문자의 개수 -1, 현재 문자의 개수 +1
    최종적으로, cnt[t.back()]의 값은 t를 만들 수 있는 개수가 된다.
    etc.) LIS 느낌으로 풀다가 실패
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 28 // max t.length

int main()
{
    FAST_IO;

    string s, t;
    cin >> s >> t;

    int pos['z' + 1]{}; // pos[c] = k일 때, 문자 c는 t에서 k+1에 위치 (= t[k+1])
    for (int i = 0; i < t.length(); i++)
        pos[t[i]] = i + 1;

    int cnt[MAX]{}; // cnt[pos] = k일 때, 문자 t[pos]를 만들 수 있는 개수는 k개
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        int cur = pos[c], prev = pos[c] - 1; // t에서의 위치

        if (cur == 1) // t[0]?
            cnt[cur]++;
        else if (cur != 0 && cnt[prev])
            cnt[prev]--, cnt[cur]++;
    }

    cout << cnt[pos[t.back()]];
}