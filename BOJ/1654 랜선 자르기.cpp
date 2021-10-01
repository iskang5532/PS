/* 
 * 1654 랜선 자르기
 * 파라메트릭 서치
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/1654
 * etc.) 이분 탐색 문제라 해서 적당히 lower_bound를 사용하여 푸는 문제라 생각했지만 생각보다 어려웠음..
 * - 결정 문제로 바꿔준 후 풀었음.
 * - 잘라서 만든 랜선의 길이를 len이라고 했을 때, 각 랜선마다 len만큼 자른 후에 나온 랜선의 개수가 n개에 미치는지에 대해 판단.
 * 만약 만들어진 개수가 n개보다 적은 경우 len이 너무 크다고 판단하여 len을 줄이며, 반대로 개수가 너무 많은 경우 len을 늘려 개수를 줄임.
 * 참고: https://www.crocus.co.kr/1000 (파라메트릭 서치에 대한 이론)
 */

#include <iostream>
#include <vector>
#include <algorithm> // max_element

using namespace std;

#define endl "\n"
#define INF 987564321
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int k, n; // 랜선의 개수 (1 <= k <= 10k), 필요한 랜선의 개수 (1 <= n <= 1M) (k <= n)
    cin >> k >> n;

    vector<int> arr(k); // 랜선의 길이 <= 2^31 - 1
    for (auto &elem : arr)
        cin >> elem;

    // l = 1: 문제에서 랜선의 길이는 2^31-1 이하라고 나오며 최솟값은 나와있지 않다. 그러나 mid 혹은 cnt 연산 과정에서 0/2와 같은 연산이 나올 수 있기 때문에 최솟값을 1로 설정했음. (0일 경우 런타임 에러_
    // long long: mid값을 구할 때 서로 더해주는 과정에서 INT_MAX + INT_MAX가 발생할 수 있음. (이를 방지하기 위해 *1LL를 해줬었는데, 시간 초과..)
    ll l = 1, r = *max_element(arr.begin(), arr.end());
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        int cnt = 0;
        for (const auto &elem : arr)
            cnt += elem / mid;

        if (cnt >= n)
            l = mid + 1;
        else //if (cnt < n)
            r = mid - 1;
    }

    cout << r;
}