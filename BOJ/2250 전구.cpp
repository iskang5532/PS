/* 
 * 2550 전구
 * LIS
 * 시간 복잡도: O(NlogN) (LIS를 구할 때의 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/2550
 * etc.) 번호와 번호로 연결되어 있는 상태를 순서로 바꾸는 것이 복잡함.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vector<int> r(n + 1); // 좌측 스위치의 번호
    vector<pii> v(n + 1); // 좌측과 우측을 번호로 연결하여 저장하기 위한 공간
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        r[i] = k;
        v[k].first = i; // k값 스위치의 위치는 i
    }
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        v[k].second = i;
    }
    sort(v.begin(), v.end()); // 좌측 값을 기준으로 정렬

    vector<int> lis;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int k = v[i].second; // 우측값을 이용하여 LIS를 구함
        auto pos = lower_bound(lis.begin(), lis.end(), k);

        if (pos == lis.end())
        {
            p[i] = lis.size();
            lis.push_back(k);
        }
        else
        {
            p[i] = pos - lis.begin();
            *pos = k;
        }
    }

    vector<int> answer;
    int len = lis.size() - 1;
    for (int i = n; i >= 0; i--) // 구한 우측값을 이용해 좌측 스위치의 값을 알아냄
        if (p[i] == len)
        {
            len--;
            answer.push_back(r[i]);
        }
    sort(answer.begin(), answer.end());

    cout << lis.size() << endl;
    for (const auto &elem : answer)
        cout << elem << " ";
}