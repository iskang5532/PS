/* 
 * 17951 흩날리는 시험지 속에서 내 평점이 느껴진거야 
 * 파라메트릭 서치
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/17951
 * etc.) 파라메트릭 서치로 바꾼 후 품.
 * - 기준값(= mid)을 정한 뒤 mid를 초과하는 값이 나오도록 구간을 나눴을 때의 구간의 개수(= cnt)가 k값과 일치하는지 확인한다.
 * 만약 cnt > k인 경우 mid가 작기 때문이며, cnt < k인 경우 mid가 크기 때문이다.
 * 여기서 조건을 만족하는 최소 mid값을 구해야 하기 때문에 cnt <= k로 바꿔준다.
 * 참고: https://blog.naver.com/jinhan814/222334635256 (이론)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
#define INF 987654321

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k; // 시험지의 개수, 그룹의 수 (1 ≤ k ≤ n ≤ 10^5)
    cin >> n >> k;
    int mx = 0;
    vector<int> arr(n); // (0 ≤ x ≤ 20)
    for (auto &elem : arr)
        cin >> elem, mx = max(mx, elem);

    int l = mx, r = mx * n;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        int cnt = 1;
        int score = 0;
        for (const auto &elem : arr)
        {
            score += elem;
            if (score > mid) // mid값을 초과한 경우, 그룹을 나눠줌
                score = 0, cnt++;
        }
        if (cnt > k)
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << l;
}