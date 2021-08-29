/* 
 * 12014 주식
 * LIS
 * 시간 복잡도: O(NlogN)
 * 문제: https://www.acmicpc.net/problem/12014
 * etc.) 원하는 길이의 LIS가 존재하는지 알아내야 하는 문제.
 * LIS의 길이를 구하게 된다면, 그보다 작은 길이의 값은 존재함.
 * 추가로, 타 문제(2352)에서는 upper_bound를 이용해도 AC가 나왔지만 여기서는 안나옴. why?
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

    int tc; // 2 <= 100
    cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        int n, k; // 1 <= 10k
        cin >> n >> k;

        vector<int> lis;
        for (int i = 0; i < n; i++)
        {
            int c;
            cin >> c;

            auto pos = lower_bound(lis.begin(), lis.end(), c); // 입력된 값이 위치해야 할 장소를 lis에서 찾아줌
            if (pos == lis.end())                              // 만약 맨 뒤인 경우 (= 값을 하나 추가해야 하는 상광이며, LIS의 길이가 늘어남)
                lis.push_back(c);
            else
                *pos = c;
        }

        cout << "Case #" << t << endl;
        k <= lis.size() ? cout << true << endl
                        : cout << false << endl; // LIS의 길이 이하인 경우 true
    }
}