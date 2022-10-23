// 2022-10-19
// 15886 내 선물을 받아줘 2
// https://www.acmicpc.net/problem/15886
/*
    sol.1) 구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 반복되는 구간을 탐색 후 t[]에 저장.
    - 방문한 위치를 visited[]에 저장 후, 재방문 시 반복되는 구간임을 확인.
    - 모든 문자에 관하여 확인. 이전에 찾은 반복되는 구간이 이후에 나올 수도 있으므로, 찾은 구간을 t[]에 저장.
    - t에 저장된 반복되는 구간의 개수를 ans에 저장.
    출력 시, ans/2의 값을 출력.
    etc.) 바로 못풀고 일주일 후에 떠오름
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

int main()
{
    FAST_IO;

    int n; // 길이 (2 ≤ N ≤ 1,000)
    cin >> n;
    string s; // 지도
    cin >> s;

    bool t[MAX]{}; // 반복되는 구간 (t[i] == t[i + 1] == true일 경우, i와 i+1에서 반복)
    for (int i = 0; i < n; i++)
    {
        bool visited[MAX]{};
        int pos = i; // 현재 탐색중인 문자의 위치
        while (!visited[pos])
        {
            visited[pos] = true;
            s[pos] == 'E' ? pos++ : pos--;
        }

        t[pos] = true;
    }

    int ans = 0;
    for (int i = 0; i < MAX; i++)
        if (t[i])
            ans++;
    cout << (ans >> 1);
}

/*
    sol.2) 구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 연속적인 문자는 결국 하나의 문자로 볼 수 있음.
    - 'E'와 'W'가 번갈아가며 나오므로, 문자열 길이의 절반을 출력.
 */

#include <iostream>
#include <algorithm> // unique

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

int main()
{
    FAST_IO;

    int n; // 길이 (2 ≤ N ≤ 1,000)
    cin >> n;
    string s; // 지도
    cin >> s;

    s.erase(unique(s.begin(), s.end()), s.end());

    cout << (s.length() >> 1);
}