/* 
 * 1818 책정리
 * LIS
 * 시간 복잡도: O(NlogN)
 * 문제: https://www.acmicpc.net/problem/1818
 * etc.) 책을 하나 옮길 떄마다 LIS의 길이가 갱신(= 증가)한다.
 * 즉, LIS의 길이를 구한 후 책들의 개수에서 빼주게 된다면, 옮겨야 할 책의 개수를 구할 수 있다.
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
    cin >> n;

    vector<int> lis;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        auto pos = lower_bound(lis.begin(), lis.end(), k);
        if (pos == lis.end())
            lis.push_back(k);
        else
            *pos = k;
    }

    cout << n - lis.size();
}