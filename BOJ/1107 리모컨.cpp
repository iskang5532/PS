// 2022-09-17
// 1107 리모컨
// https://www.acmicpc.net/problem/1107
/*
    완전 탐색 (2,024KB, 36ms)
    시간 복잡도: ?
    풀이)
    - 어떠한 수 l(혹은 r)을 정한 후, 해당 값을 버튼만으로 만들 수 있는지를 확인.
    가능한 경우, 해당 채널에서부터 n까지 몇 개의 채널 이동이 필요한지를 구한 후 누른 버튼의 개수 및 이동 횟수를 ans에 저장. (단, ans와 비교 후 최솟값을 저장)
    - l(혹은 r)이 100이 될 경우, 채널 이동만으로 최소 횟수가 되는지를 확인 후 ans에 저장.
    - n보다 높은 수 혹은 낮은 수가 된 후 채널을 이동하는 방법 또한 가능하므로 l과 r의 초깃값을 n으로 함.
    etc.)
    - 어려웠음.. 혼자 풀어보려 했다가 실패
    n = 100으로 할 경우, l과 r의 한계를 n보다 큰 값 혹은 낮은 값으로 잡아주면 될듯
    참고)
    - 이론 및 코드: https://blog.naver.com/jinhan814/222086993561
    - 반례: https://www.acmicpc.net/board/view/96380
            https://www.acmicpc.net/board/view/96201
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 13 // max btn
#define INF 0x3f3f3f3f

bool isValid(int k, bool valid[]) // 만들 수 있는 수인가
{
    string s = to_string(k);
    for (int i = 0; i < s.length(); i++)
        if (!valid[s[i] - '0'])
            return false;

    return true;
}

int main()
{
    FAST_IO;

    int n, m; // 이동하려고 하는 채널 n(0 ≤ n ≤ 500,000) 고장난 버튼의 개수 m(0 ≤ m ≤ 10)
    cin >> n >> m;

    bool valid[MAX]; // valid[i] = false일 경우, 번호 i는 사용할 수 없음
    fill(valid, valid + MAX, true);
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        valid[k] = false;
    }

    int ans = INF;
    for (int cnt = 0, l = n, r = n;; cnt++, l--, r++) // cnt: 채널 이동 횟수
    {
        if (l == 100 || r == 100)
        {
            ans = min(ans, cnt);
            break;
        }

        if (isValid(l, valid))
        {
            int k = cnt + to_string(l).length();
            ans = min(ans, k);
        }
        if (isValid(r, valid))
        {
            int k = cnt + to_string(r).length();
            ans = min(ans, k);
        }
    }

    cout << ans;
}
