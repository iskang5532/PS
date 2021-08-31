/* 
 * 14003 가장 긴 증가하는 부분 수열 5
 * LIS
 * 시간 복잡도: O(NlogN) (LIS 알고리즘 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/14003
 * etc.) 기존 LIS 문제에서 LIS의 값을 찾아 출력하는 문제가 추가됨
 * lis에 저장된 값을 그대로 출력할 경우, [2 3 1]과 같은 수열일 경우 [1 3]이 출력이 된다. 때문에, 공간을 따로 만들어 값을 저장시켜 줌
 * 참고: https://seungkwan.tistory.com/8 (이론)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

struct P
{
    int k, pos; // 값 및 lis의 위치(값에 의한)
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<P> arr(n); // 수열과 수열의 값에 대한 lis의 위치를 저장  ex) arr[2] = {3, 2}일 경우 수열의 두 번째 값은 3이며 lis[2]에 위치함
    vector<int> lis;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        arr[i].k = k; // 수열의 값 저장

        auto pos = lower_bound(lis.begin(), lis.end(), k);
        if (pos == lis.end()) // lis에 값을 추가해야 하는 경우 (= lis의 길이가 증가)
        {
            arr[i].pos = lis.size(); // lis에서 현재 값의 위치 저장
            lis.push_back(k);
        }
        else
        {
            *pos = k;
            arr[i].pos = pos - lis.begin();
        }
    }

    int len = lis.size() - 1;                               // lis의 길이이며, -1인 이유는 arr의 길이는 n - 1이기 때문
    for (auto itr = arr.rbegin(); itr != arr.rend(); itr++) // 뒤에서부터 수열을 구하여 값에 맞는 arr값을 저장
        if ((*itr).pos == len)                              // lis의 현재 위치에 오는 값일 경우
        {
            lis[len] = (*itr).k; // lis 벡터에 값을 저장 (재활용)
            len--;               // 그 다음 값을 찾기 위해 -1 해줌
        }

    cout << lis.size() << endl;
    for (const auto &elem : lis)
        cout << elem << " ";
}

// 3   2 4 1
// ans: 2  2 4
//
// 10  1 5 10 3 13 18 19 15 16 17
// ans: 7  1 5 10 13 15 16 17