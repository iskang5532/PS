// 2023-01-14
// 27161 크레이지 타임
// https://www.acmicpc.net/problem/27161
/*
    구현 (2,184KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 현재 부를 시간 t가 입력된 x와 같은지, 혹은 s가 모래시계인지를 비교하여 답을 ans에 저장.
    - 시간은 0부터 11까지 총 12개를 사용. (비교 시, t+1의 값을 사용)
    - 만약 t+1과 x가 같을 경우, 동기화의 법칙으로 인해 게임판 중앙을 내리쳐야 함. (단, 시간 역행의 법칙이 발동되지 않아야 함)
    - 만약 s가 모래시계일 경우, 시간 역행의 법칙이 발동해야 함. (단, 동기화의 법칙이 발동되지 않아야 함)
    - 구한 ans의 값을 출력.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

int main()
{
    FAST_IO;

    int n; // 카드의 개수 (1 ≤ n ≤ 1,000)
    cin >> n;
    vector<pair<string, int>> v(n);
    for (auto &[s, x] : v)
        cin >> s >> x;

    vector<pair<int, string>> ans;
    for (int i = 0, t = -1, rev = false; i < n; i++) // 시간 t, 반전 상태 rev
    {
        const auto &[s, x] = v[i];

        t = (12 + t + (!rev ? 1 : -1)) % 12; // 시간 갱신 (반전 상태일 경우, 거꾸로)

        pair<int, string> p;
        p.first = t;
        if (t + 1 == x && s != "HOURGLASS") // 시간과 x가 일치하는 경우 (단, 모래시계 아니어야 함)
            p.second = "YES";
        else
            p.second = "NO";
        ans.push_back(p);

        if (s == "HOURGLASS" && t + 1 != x) // 모래시계일 경우, 반전 (단, 시간은 x와 일치하지 않음)
            rev = !rev;
    }

    for (const auto &[i, s] : ans)
        cout << i + 1 << ' ' << s << endl;
}