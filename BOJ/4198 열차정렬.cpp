/* 
 * 4198 열차정렬
 * LIS
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/4198
 * etc.) LIS 알고리즘에서 lis를 구할 때, 컨테이너에 저장되어 있는 값보다 최대한 작은 값이 뒤 혹은 기존 자리에 들어가게 된다.
 * 그러나, 앞쪽에 값을 넣어주는 경우는 최대한 작은 값이 아닌 기존 값에 가까운, 즉 기존값보다 작되 최대한 큰 값이 입력되어야 한다. (그래야 이후 들어올 수 있는 값이 많아 짐)
 * 이러한 역할을 해주는 LDS를 구현하여 이용했음.
 * 또한, 기존 LIS 알고리즘은 입력값에 따라 beign()값을 바꾸는데 반해서, 이 풀이에서는 바꾸지 않음. 때문에 모든 원소를 기준점으로 이용하여 LIS 및 LDS를 조사함. (= 기준점 중복)
 * 참고: https://www.acmicpc.net/board/view/37580 (TC)
 * https://www.crocus.co.kr/956 (이론 참고)
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

    int n; // 0 <= 2k
    cin >> n;

    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem; // 0 <= INT_MAX?

    int answer = 0;             // 열차의 길이. 값은 열차의 최소 길이 (= 차량의 개수가 0개인 경우)
    for (int i = 0; i < n; i++) // arr[i]값을 기준으로 이후 나올 값들로부터 LIS 및 LDS를 구함
    {
        vector<int> lis;
        vector<int> lds;
        for (int j = i; j < n; j++) // LIS
        {
            int k = arr[j];

            auto pos = lower_bound(lis.begin(), lis.end(), k);
            if (pos == lis.end())
                lis.push_back(k);
            else if (pos != lis.begin()) // 기준값이 아닌 경우, 값을 변경
                *pos = k;
        }
        for (int j = i; j < n; j++) // LDS
        {
            int k = -arr[j]; // 값을 음수로 바꾸어 LDS를 구함

            auto pos = lower_bound(lds.begin(), lds.end(), k);
            if (pos == lds.end())
                lds.push_back(k);
            else if (pos != lds.begin())
                *pos = k;
        }

        answer = max(answer, static_cast<int>(lis.size() + lds.size() - 1)); // 참고 사이트 확인
    }

    cout << answer;
}

// 3
// 2 3 1
// ans: 3

// 13
// 455 319 64 159 314 183 605 884 861 101 298 571 301
// ans: 7

// 0
// ans: 0