// 2022-07-03
// 2015 수들의 합 4
// https://www.acmicpc.net/problem/2015
/*
    누적합, 맵 (12,972, 40ms)
    시간 복잡도: ?
    풀이)
    - n의 크기가 200k. 즉, 2중 for문을 이용하여 부분합의 개수를 구할 경우 TLE.
    - 맵을 이용하여 이전까지의 누적합을 저장하여 현재 필요로 하는 누적합이 있는지를 파악. 이 경우, O(n)에 부분합의 개수를 확인할 수 있음.
    - 입력받은 값 a를 이용하여 누적합을 구한 후, pSum[]에 저장.
    - 현재 탐색중인 값의 인덱스를 i라 할 때, i-1까지 모든 누적합의 개수를 저장할 m.
    - 이전까지의 누적합 pSum[i - 1]을 맵에 저장한 후, 현재 필요로 하는 이전 누적합 pSum[i] - k를 찾은 후, 맵에 존재하는 값의 개수만큼 ans에 추가.
    이때, 먼저 이전 누적합의 개수를 더해주게 되는데 이는 0을 추가하기 위함.
    pSum[i]에서 k를 빼게 될 경우, k를 만드는데 필요한 값이 나온다. 이 값이 이전에 구한 누적합에 존재할 경우, k를 만들 수 있음.
    etc.) 누적합도 신기한데 맵을 이용한 풀이가 있다는것에 또 한번 신기함을 느낌
    참고)
    - 코드: https://atcoder.jp/contests/abc233/editorial/3186
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
#define MAX 200'003 // max n

unordered_map<int, int> m; // i-1까지의 누적합을 저장

int main()
{
    FAST_IO;

    int n, k;
    cin >> n >> k;
    ll pSum[MAX]{};
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        pSum[i] = pSum[i - 1] + a;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        m[pSum[i - 1]]++;

        ans += m[pSum[i] - k];
    }

    cout << ans;
}