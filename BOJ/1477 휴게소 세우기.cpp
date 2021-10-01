/* 
 * 1477 휴게소 세우기
 * 파라메트릭 서치
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/1447
 * etc.) 어려웠던 부분이 많았던 문제. (문제의 이해, 휴게소가 중복되게 짓지 못한다는 점, l, r의 if문 조건 구성)
 * - 구간의 간격(= mid)에 대한 결정 문제로 바꿔 품.
 * 만약 i to i-1의 길이가 mid보다 긴 경우 분할이 가능하며, mid보다 훨씬 큰 값이어서 두 번 이상 가능한 경우 추가적으로 카운팅.
 * 카운팅의 개수가 m보다 큰 경우(= cnt > m) mid값이 작기 때문에 값을 키워줌.
 * 카운팅의 개수가 m보다 작은 경우 (= cnt < m) mid값이 크기 때문에 값을 줄여줌.
 * 이 때, cnt == m이면서 mid의 최솟값을 구해야 하기 때문에 [cnt < m]을 [cnt <= m]으로 바꿔줌
 * 참고: https://paris-in-the-rain.tistory.com/44 (휴게소 중복에 대해)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m, len; // 현재 및 지을 휴게소의 개수 (n, m <= 100), 고속도로의 길이 (100 <= len <= 1k)
    cin >> n >> m >> len;
    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;
    arr.push_back(0), arr.push_back(len); // 시작점과 고속도로의 끝을 넣어줌
    sort(arr.begin(), arr.end());

    int l = 0, r = len;
    while (l <= r)
    {
        int cnt = 0;            // 건설할 휴게소의 개수
        int mid = (l + r) >> 1; // 간격

        for (int i = 0; i < arr.size() - 1; i++)
        {
            int dist = arr[i + 1] - arr[i]; // i to i-1까지의 거리 (현재 주유소부터 이전 주유소까지의 거리)

            if (dist % mid == 0) // 분할 길이에 딱 맞는 경우 (= 휴게소가 [i]에도 세워지기 때문에 cnt--)
                cnt--;
            cnt += dist / mid;
        }

        if (cnt > m)
            l = mid + 1;
        else // 최솟값을 출력해야 하기 때문에 값이 같은 경우(=) r을 옮겨 값의 크기를 줄임
            r = mid - 1;
    }

    cout << l;
}