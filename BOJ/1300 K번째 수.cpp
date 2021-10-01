/* 
 * 1300 K번째 수
 * 파라메트릭 서치
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/1300
 * etc.) 여러 번 헤맸음. (long long, 2중 반복문으로 인한 시간초과, 최솟값을 구해야 하는 것에 대한 깨달음)
 * - 결정 문제로 바꾼 후 풀었음.
 * - 질문에서의 i번째 값을 구하는 문제를 바꾸었으며, 기준값(= mid) 이하 값의 개수가 i개일 때 i번째 값을 구할 수가 있다.
 * - 주의할 점은, n == 3일 때 [2], [3] 값 모두 2의 값으로 동일한 경우가 있다.
 * 이는 곧 일정 구간의 값은 결국 구간의 첫 번째 위치 (= [2])가 정답이 되기 때문에 최솟값을 구해줘야 한다.
 * 참고: https://blog.naver.com/jinhan814/222140914682 (36-37 line 참고)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    ll n, k; // 배열의 크기 (n <= 10^5), 위치 k (k <= min(10^9, n^2))
    cin >> n >> k;

    ll l = 1, r = k;
    while (l <= r)
    {
        int cnt = 0; // mid보다 작은 값의 개수

        ll mid = (l + r) / 2; // 기준값 (mid 이하의 값이 몇 개인가)
        for (int i = 1; i <= n; i++)
            cnt += min(n, mid / i);

        if (cnt < k)
            l = mid + 1;
        else // 최솟값을 출력해야 하기 때문에 값이 같은 경우(=) r을 옮겨 값의 크기를 줄임
            r = mid - 1;
    }

    cout << l;
}