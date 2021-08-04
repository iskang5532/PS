/* 
 * 1365 꼬인 전깃줄
 * LIS
 * 시간 복잡도: nlogn (LIS 구하는 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/1365
 * ETC.) 문제를 봤을 때 LIS를 이용해야 한다는 것을 알아 차리기가 매우 어려움..
 * - 개인적인 이해를 돕기 위한 설명 -
 * 좌측값에 우측값을 나열했을 때, 우측값이 정방향(= 이전 값보다 큰. LIS)인 경우는 꼬인 상황이 없다.
 * 그러나, 중간에 LIS가 망가지는 역방향(이전 값보다 작은)의 값이 생긴 경우, 선이 꼬이게 된다. (정렬된 좌측값에 대한 우측값을 출력하여 이해해보기)
 * - 정방향은 이전 값보다 무조건 크기 때문에 a값 기준으로 정렬(= 꼬일 일이 없음)이 되어 있을 경우, 꼬일 일이 절대 없음
 * - 역방향은 이전 값보다 작은 값이 들어오기 때문에 선이 꼬이게 됨
 * 참고: https://yabmoons.tistory.com/572 (이론 및 그림)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;

    vector<int> LIS(n);
    int len = 0; // 만들어진 LIS의 길이 (= 엉키지 않는 전깃줄의 최대 개수)
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        auto pos = lower_bound(LIS.begin(), LIS.begin() + len, k); // k값의 위치를 만들어진 LIS(= LIS.begin() + len)에서 탐색함
        *pos = k;                                                  // 구한 위치에 값을 넣어 줌

        if (pos == LIS.begin() + len) // 만약 k값의 위치가 LIS의 마지막 위치인 경우 (= 모든 값보다 크다는 것이며, LIS의 값이 하나 추가됨)
            len++;
    }

    cout << n - len; // 전깃줄의 개수 - 엉키지 않는 전깃줄의 개수 = 엉킨 전깃줄
}