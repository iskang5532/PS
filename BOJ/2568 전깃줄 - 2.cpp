/* 
 * 2568 전깃줄 - 2
 * LIS
 * 시간 복잡도: O(NlogN) (LIS를 구할 때의 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/2568
 * etc.) LIS의 값을 구하는 문제가 아닌, LIS가 아닌 값을 구하는 문제.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
#define l first
#define r second

bool cmp(const pair<int, int> &p1, const pair<int, int> &p2) // 오름차순
{
    return p1.l < p2.l; // 오름차순
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // <= 100k
    cin >> n;

    vector<pair<int, int>> arr(n); // 두 전봇대의 연결 (= 입력)
    for (auto &elem : arr)
        cin >> elem.l >> elem.r; // <= 500k

    sort(arr.begin(), arr.end(), cmp); // 좌측 전봇대를 기준으로 정렬해줌

    vector<int> lis;
    vector<int> P(n); // P[n]일 때, n번째 값의 LIS 위치  ex)P[7] == 4일 때, arr[7] == LIS[4]
    for (int i = 0; i < n; i++)
    {
        int k = arr[i].r;
        auto pos = lower_bound(lis.begin(), lis.end(), k); // 값이 LIS에서의 어울리는 위치를 찾아냄
        if (pos == lis.end())
        {
            P[i] = lis.size();
            lis.push_back(k);
        }
        else
        {
            P[i] = pos - lis.begin();
            *pos = k;
        }
    }

    int len = lis.size() - 1;
    for (int i = n - 1; i >= 0; i--)
        if (P[i] == len)
            len--;
        else
            P[i] = -1; // 재활용. i번째 값을 -1로 초기화하여 LIS가 아닌 값을 찾아낼 것임

    cout << n - lis.size() << endl;
    for (int i = 0; i < P.size(); i++)
        if (P[i] == -1) // 만약 i번째 값이 -1인 경우 (= LIS에 포함되지 않음)
            cout << arr[i].l << endl;
}