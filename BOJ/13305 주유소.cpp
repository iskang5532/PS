// 13305 주유소
// https://www.acmicpc.net/problem/13308
/*
    그리디 (2,680KB, 20ms)
    시간 복잡도: ?
    풀이)
    - i번째 주유소까지의 리터당 최소 가격 mn을 구함.
    이후, 다음 도시까지 갈 수 있도록 도로의 길이만큼 주유함. 이때 가격은 mn.
    - 이전 도시에서의 가격이 더 저렴할 경우, 여러 도시를 방문할 때 사용할 수 있도록 저렴한 가격으로 미리 주유함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_N 100'003
using ll = long long;

int main()
{
    FAST_IO;

    int n; // 도시의 개수 (2 ≤ N ≤ 100,000)
    cin >> n;
    int l[MAX_N], c[MAX_N]; // 도로의 길이 l, 주유소의 리터당 가격 c (1 ≤ l[i], c[i] ≤ 1,000,000,000)
    for (int i = 0; i < n - 1; i++)
        cin >> l[i];
    for (int i = 0; i < n; i++)
        cin >> c[i];

    ll ans = 0;
    int mn = c[0]; // i번째 도시까지의 최소 가격을 저장
    for (int i = 0; i < n; i++)
    {
        mn = min(mn, c[i]);

        ans += 1LL * mn * l[i];
    }

    cout << ans;
}