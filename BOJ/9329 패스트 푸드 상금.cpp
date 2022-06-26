// 2022-06-26
// 9329 패스트 푸드 상금
// https://www.acmicpc.net/problem/9329
/*
    완전 탐색 (2,020KB, 4ms)
    시간 복잡도: ?
    풀이)
    - i번째 상금을 얻는데 필요한 스티커 중 가장 적은 개수를 저장한 후, 상금과 곱하여 최대 상금 액수인 ans에 추가.
    etc.) 상금 획득에 필요한 스티커가 중복되는 문제인줄로 착각
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 0x7fffffff
#define MAX 33 // max m

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m; // 상금의 종류 n (1 ≤ n ≤ 10), 스티커의 종류 (1 ≤ m ≤ 30)
        cin >> n >> m;
        vector<int> v[MAX]; // 상금 획득에 필요한 스티커를 저장
        int prize[MAX];     // 상금 (prize[i] ≤ 1,000,000)
        for (int i = 1; i <= n; i++)
        {
            int k; // 필요한 스티커의 개수 (1 ≤ k ≤ m)
            cin >> k;
            for (int idx = 0; idx < k; idx++)
            {
                int a; // 필요한 스티커의 종류
                cin >> a;
                v[i].push_back(a);
            }
            cin >> prize[i];
        }

        int cnt[MAX]{}; // 스티커의 개수 (cnt[i] ≤ 100)
        for (int i = 1; i <= m; i++)
            cin >> cnt[i];

        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int mn = INF; // 상금 획득에 필요한 스티커들 중 가장 적은 개수
            for (auto &cur : v[i])
                mn = min(cnt[cur], mn);

            ans += prize[i] * mn;
        }

        cout << ans << endl;
    }
}