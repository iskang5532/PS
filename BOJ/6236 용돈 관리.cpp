/* 
 * 6236 용돈 관리
 * 파라메트릭 서치
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/6236
 * etc.) l, r 기본값 설정의 중요성을 느낌. (l == 1일 때 WA가 나오며 이해는 되는데 반례를 못찾겠음..)
 * - 결정 문제로 바꿔 품.
 * - 기준 금액(= mid)을 사용하였을 때의 통장 사용 횟수(= cnt)를 이용.
 * 만약 cnt > m인 경우 mid값이 작기 때문이며, cnt < m인 경우 mid값이 크기 때문이다.
 * 여기서, 조건(cnt ==  m)을 충족시키는 최솟값 mid를 구하는 것이기 때문에 cnt <= m으로 바꾼 후 l값을 구해준다.
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

#define endl "\n"
#define INF 987'654'321

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 일수 (1 ≤ n ≤ 100k), 통장 횟수 (1 ≤ m ≤ n)
    cin >> n >> m;

    int mx = 0;         // 입력된 금액들 중 최대 금액
    vector<int> arr(n); // 금액 (1 ≤ 금액 ≤ 10k)
    for (auto &elem : arr)
        cin >> elem, mx = max(mx, elem);

    int l = mx, r = mx * n; // 초깃값 주의
    while (l <= r)
    {
        int cnt = 1; // 통장을 사용한 횟수 (= 금액을 리셋시킨 횟수)
        int mid = (l + r) / 2, money = mid;
        for (const auto &elem : arr)
        {
            money -= elem;
            if (money < 0) // 금액이 음수가 되었을 경우, 리셋한 후 값을 빼줌
                cnt++, money = mid - elem;
        }

        if (cnt > m) // 조건을 충족하는 값의 최솟값을 구함
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << l;
}