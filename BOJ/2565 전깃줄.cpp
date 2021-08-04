/* 
 * 2565 전깃줄
 * LIS
 * 시간 복잡도: nlogn (LIS 구하는 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/2565
 * ETC.) 문제를 봤을 때 LIS를 이용해야 한다는 것을 알아 차리기가 매우 어려움..
 * - 개인적인 이해를 돕기 위한 설명 -
 * a값 기준 정렬되어 있을 경우, 정방향(= 이전 값보다 큰. LIS)은 전깃줄이 꼬일 상황이 없다.
 * 그러나, 중간에 LIS가 망가지는 역방향(이전 값보다 작은)의 값을 하나 넣을 경우, 선이 꼬이게 됨. (arr의 b값을 출력하여 이해해보기)
 * - 정방향은 이전 값보다 무조건 크기 때문에 a값 기준으로 정렬(= 꼬일 일이 없음)이 되어 있을 경우, 꼬일 일이 절대 없음
 * - 역방향은 이전 값보다 작은 값이 들어오기 때문에 선이 꼬이게 됨
 * 참고: https://yabmoons.tistory.com/572 (이론 및 그림)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

struct Link
{
    int a, b;
};

bool cmp(const Link &p1, const Link &p2) { return p1.a < p2.a; }; // a값을 기준으로 한 오름차순

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<Link> arr(n);
    for (auto &elem : arr)
        cin >> elem.a >> elem.b;
    sort(arr.begin(), arr.end(), cmp); // a값을 기준으로 정렬이 되어 있는 상태에서 b값들의 LIS를 구해야 함

    vector<int> LIS(n);
    int len = 0; // 만들어진 LIS의 길이 (= 엉키지 않는 전깃줄의 최대 개수)
    for (int i = 0; i < n; i++)
    {
        int k = arr[i].b;                                          // i번째 b값
        auto pos = lower_bound(LIS.begin(), LIS.begin() + len, k); // k값의 위치를 만들어진 LIS(= LIS.begin() + len)에서 탐색함
        *pos = k;                                                  // 위치에 값을 넣어 줌

        if (pos == LIS.begin() + len) // 만약 k값의 위치가 LIS의 마지막 위치인 경우 (= 모든 값보다 크다는 것이며, LIS의 값이 하나 추가됨)
            len++;
    }

    cout << n - len; // 전깃줄의 개수 - 엉키지 않는 전깃줄의 개수 = 엉킨 전깃줄
}