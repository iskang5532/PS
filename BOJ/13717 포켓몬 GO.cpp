// 2023-03-20
// 13717 포켓몬 GO
// https://www.acmicpc.net/problem/13717
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - m - k가 양수일 경우, 해당 포켓몬은 진화 가능.
    진화 횟수는 cnt에 저장하며, 진화 시 m += 2.
    - 이전에 구한 진화 최대 횟수를 mx에 저장하며, cnt와 비교.
    만약 cnt > mx일 경우, 현재 포켓몬의 이름을 name에 저장.
    - 총 진화 횟수를 tot에 저장.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 포켓몬의 종류 (1 ≤ n ≤ 70)
    cin >> n;

    int tot = 0; // 진화 횟수
    string name; // 가장 많이 진화한 포켓몬의 이름
    for (int i = 0, mx = 0; i < n; i++)
    {
        string s;
        cin >> s;
        int k, m; // 진화에 필요한 개수 k(12 ≤ k ≤ 400), 보유중인 사탕 m(1 ≤ m ≤ 10^4)
        cin >> k >> m;

        int cnt = 0;
        while (m - k >= 0) // 보유중인 사탕으로 진화시킬 수 있을 경우
            m -= k, m += 2, cnt++;

        if (cnt > mx) // 현재 마릿수가 이전에 구한 마릿수의 최댓값보다 높은 경우
            name = s, mx = cnt;
        tot += cnt;
    }

    cout << tot << endl
         << name;
}