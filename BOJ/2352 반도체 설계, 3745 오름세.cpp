// 2352 반도체 설계
// https://www.acmicpc.net/problem/2352
/*
    LIS (2,532KB, 0ms)
    시간 복잡도: O(nlogn)
    풀이)
    - LIS를 저장할 벡터 lis를 선언한 후, lis에서 입력된 값 k에 맞는 위치를 찾아 넣음.
    - 만약 lis가 비어 있을 경우, 값을 넣음.
    - 만약 lis의 마지막 값이 k보다 작을 경우, k를 푸쉬. (가장 오른쪽에 추가)
    그 외, 이분 탐색을 이용해 k보다 작으면서 가장 가까운 값을 찾은 후, k로 바꿈.
    etc.) LIS로 O(nlogn)에 푸는 대표적인 문제인듯
 */

#include <iostream>
#include <vector>
#include <algorithm> // lower_bound

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 40'003

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    vector<int> lis;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (lis.empty() || lis.back() < k) // 비어 있거나 k가 가장 큰 값일 경우
            lis.push_back(k);
        else
        {
            auto pos = lower_bound(lis.begin(), lis.end(), k); // or upper_bound
            *pos = k;
        }
    }

    cout << lis.size();
}

// 3745 오름세
// https://www.acmicpc.net/problem/3745
// LIS (2,532KB, 0ms)

#include <iostream>
#include <vector>
#include <algorithm> // lower_bound

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 40'003

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    vector<int> lis;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (lis.empty() || lis.back() < k) // 비어 있거나 k가 가장 큰 값일 경우
            lis.push_back(k);
        else
        {
            auto pos = lower_bound(lis.begin(), lis.end(), k); // or upper_bound
            *pos = k;
        }
    }

    cout << lis.size();
}