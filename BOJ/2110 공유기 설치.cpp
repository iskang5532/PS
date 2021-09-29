/* 
 * 2110 공유기 설치
 * 이분 탐색
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/2110
 * etc.) 문제를 이해하지 못해서 한참을 헤맨 문제..
 * - 두 집간의 거리를 이용하여 일정한 간격(= mid)으로 설치했을 때의 필요 기기 개수를 확인함.
 * 만약 필요 기기 개수가 c보다 적은 경우 거리를 좁혀 기기를 더 두게 하며, 이상인 경우 간격을 넓혀 사용 개수를 줄임.
 * 참고: https://www.crocus.co.kr/1000 (파라매트릭 서치에 대한 이론)
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

    int n, c; // 집의 개수 (2 <= n <= 200k), 공유기의 개수 (2 <= c <= n)
    cin >> n >> c;
    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;
    sort(arr.begin(), arr.end());

    int l = 1, r = arr.back(); // 기기간 최소 거리 및 최대 거리
    while (l <= r)
    {
        int cnt = 1;            // 거리에 맞추기 위해 사용한 기기의 개수 (1번에 설치하며 시작)
        int mid = (l + r) >> 1; // 최대 거리

        int curr = 0; //현재 위치 (default: [0])
        for (int next = 1; next < n; next++)
            if (arr[next] - arr[curr] >= mid) // 만약 curr ~ next간 거리가 mid 이상인 경우
                curr = next, cnt++;           // curr 위치를 바꿔주며 cnt++ (이는 next 위치에 기기를 하나 놓은 것)

        if (cnt >= c)
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r;
}

/* tc (ans: 4)
 * 5 2
 * 1 2 3 4 5
 * 
 * - 2 3 4 -
 * 위와 같이 공유기를 배치해야 한다. (기기간 거리가 최대치가 되는 설치 위치)
 * 1 - 3 - 5
 * 위와 같이 설치할 경우, 집에 골고루 전파가 되겠지만 질문에 대한 답이 아님. (이런 문제로 이해해서 오래걸림..)
 */
