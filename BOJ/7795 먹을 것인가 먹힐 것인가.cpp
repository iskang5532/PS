// 7795 먹을 것인가 먹힐 것인가
// https://www.acmicpc.net/problem/7795
/*
    이분 탐색 (2,296KB, 28ms)
    시간 복잡도: ?
    풀이)
    1) v1의 값을 하나씩 사용하여 v2에서 탐색. (v2에서 이분 탐색을 이용하므로 정렬시켜줌)
    2) v1의 값보다 이상인 값의 첫 위치를 v2에서 찾은 후, ans에 저장.
    첫 위치를 찾는 이유는, 그 전까지의 값들은 모두 v1의 값보다 작음. 즉, 개수를 파악할 수 있음.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m; // (1 ≤ n, m ≤ 20k)
        cin >> n >> m;

        vector<int> v1(n), v2(m);
        for (auto &elem : v1)
            cin >> elem;
        for (auto &elem : v2)
            cin >> elem;
        sort(v2.begin(), v2.end());

        int ans = 0;
        for (const auto &elem : v1)
            ans += lower_bound(v2.begin(), v2.end(), elem) - v2.begin(); // elem 이상인 값의 위치를 탐색 (= elem 미만 값의 개수)
        cout << ans << endl;
    }
}