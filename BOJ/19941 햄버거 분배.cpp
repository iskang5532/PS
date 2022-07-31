// 2022-07-30
// 19941 햄버거 분배
// https://www.acmicpc.net/problem/19941
/*
    그리디 (2,168KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자열을 입력받은 후, 왼쪽 문자 s[p]부터 확인.
    만약 s[p]가 사람일 경우, s[p]는 k만큼 떨어진 s[p]-k부터 s[p]+k까지의 햄버거를 먹을 수 있다.
    햄버거는 왼쪽인 s[p]-k부터 탐색하여 먹지 않은 햄버거를 먹는다.
    왼쪽의 햄버거는 s[p]는 닿지만, s[p+i]는 닿지 않을 수가 있다.
    그러므로, 가장 먼 왼쪽 햄버거를 먹이게 된다면 이후에 나오는 사람들 또한 선택지가 많아지며, 최대한 많은 사람이 햄버거를 먹을 수 있게 된다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 20'003 // max n

int main()
{
    FAST_IO;

    int n, k; // 문자의 개수 n(1 ≤ n ≤ 20,000), 선택할 수 있는 거리 k(1 ≤ k ≤ 10)
    cin >> n >> k;
    string s;
    cin >> s;

    int ans = 0;
    bool ate[MAX]{};            // ate[i] = true일 경우, i번째 햄버거는 먹음
    for (int p = 0; p < n; p++) // 사람
    {
        if (s[p] == 'H')
            continue;
        for (int h = max(0, p - k); h <= min(n - 1, p + k); h++) // 햄버거
            if (s[h] == 'H' && !ate[h])
            {
                ate[h] = true, ans++;
                break;
            }
    }

    cout << ans;
}