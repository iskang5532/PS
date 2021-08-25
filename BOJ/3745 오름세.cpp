/* 
 * 3745 오름세
 * LIS
 * 시간 복잡도: O(NlogN)
 * 문제: https://www.acmicpc.net/problem/3745
 * etc.) 기본적인 LIS 문제인 듯함
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

    int n;
    while (cin >> n)
    {
        vector<int> arr(n);
        for (auto &elem : arr)
            cin >> elem;

        vector<int> LIS;
        for (int i = 0; i < n; i++)
        {
            int idx = arr[i];

            auto pos = lower_bound(LIS.begin(), LIS.end(), idx);
            if (pos == LIS.end())
                LIS.push_back(idx);
            else
                *pos = idx;
        }

        cout << LIS.size() << endl;
    }
}