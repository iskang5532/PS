/*
    2217 로프
    그리디 (2,412KB, 12ms)
    시간 복잡도: O(N^2) (모든 로프 확인 및 max())
    문제: https://www.acmicpc.net/problem/2217
    etc.) 밑에 주석으로 달아 둔 예제와 같이 결과값이 i값일 때보다 i+1 혹은 i-1값이 더 클 수 있음. 때문에 완전 탐색으로 해결.
    - 로프가 버틸 수 있는 무게를 내림차순으로 정렬.
    - 가장 강한 로프부터 하나 씩 사용하여 버틸 수 있는 무게 ans를 구함.
    - 0, .. , i로 구한 ans는 0, .. , i - (i-1)보다 큼. (앞에서부터 가장 강한 로프이므로. 밑 예제를 통해 확인해보기)
    참고)
    반례: https://www.acmicpc.net/board/view/25029
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

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

    int n; // 로프의 개수 N(1 ≤ N ≤ 100k)
    cin >> n;
    vector<int> arr(n); // 로프가 버틸 수 있는 중량 (1 ≤ ai ≤ 10k)
    for (auto &elem : arr)
        cin >> elem;
    sort(arr.begin(), arr.end(), greater<int>());

    int ans = 0, cnt = 1;
    for (const auto &k : arr)
        ans = max(ans, k * cnt), cnt++;

    cout << ans;
}

// 7%
// 3
// 11
// 5
// 4
// ans: 12