// 2022-10-21
// 20365 블로그2
// https://www.acmicpc.net/problem/20365
/*
    sol.1) 그리디 (2,912KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 연속된 색은 한 번으로 칠할 수 있으므로 erase 및 unique를 이용하여 제거한다.
    남아 있는 'B' 혹은 'R'의 개수를 확인.
    둘 중 더 많은 색을 전체적으로 칠한 후, 나머지 색을 따로 칠한다.
    즉, 1 + min(B, R)을 출력한다.
 */

#include <iostream>
#include <algorithm> // unique

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 문제의 수 (1 ≤ n ≤ 500,000)
    cin >> n;
    string s;
    cin >> s;

    s.erase(unique(s.begin(), s.end()), s.end());

    int b = 0, r = 0;
    for (const auto &c : s)
        c == 'B' ? b++
                 : r++;
    cout << 1 + min(b, r);
}

/*
    sol.2) 그리디, 구현 (2,912KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 연속된 색은 한 번으로 칠할 수 있음.
    - 칠할 색의 개수를 저장할 B, R.
    - 연속된 색임을 확인하기 위해, 이전 색을 prev에 저장.
    만약 이전 색과 다른 경우, 새로운 색이 나온 것이므로 현재 색의 개수를 카운팅한다.
    둘 중 더 많은 색을 전체적으로 칠한 후, 나머지 색을 따로 칠한다.
    즉, 1 + min(B, R)을 출력한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 문제의 수 (1 ≤ n ≤ 500,000)
    cin >> n;
    string s;
    cin >> s;

    int b = 0, r = 0;
    char prev = ' '; // 이전 색
    for (const char &c : s)
    {
        if (c != prev)
            c == 'B' ? b++
                     : r++;
        prev = c;
    }

    cout1 + << min(b, r);
}