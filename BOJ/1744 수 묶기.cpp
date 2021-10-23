/*
    1744 수 묶기
    (2,024KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1744
    etc.) 예외처리에 신경을 많이 써야 했던 문제.
    - 입력된 값을 1을 기준으로 나눴으며, k >= 1인 경우 v1, k < 1인 경우 v2에 저장.
    - 양수인 경우 내림차순으로 정렬을 하였으며, 1 이외의 값 두 개를 묶어 서로 곱해줌.
    만약 값이 1이 나온 경우, 그 이후의 값은 모두 1이기 때문에 현재 값 1과 남아 있는 1을 모두 더해줌 (곱해주지 않음)
    - 음수인 경우 오름차순으로 정렬을 하였으며, 값 두개를 묶어 서로 곱해줌. (음수와 음수가 곱해질 경우 양수이며 0과 곱해질 경우 0)
    최적화를 위해 0이 나온 경우 더 이상의 연산은 의미가 없기 때문에 반복문을 종료시킬 수 있음.
    - 신경써야 할 점.
     - 1의 경우 곱셈보다 덧셈이 더 높음.
     - 음수끼리 곱을 이용해 양수로 만들 수 있음.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int get_result(const vector<int> &v, const bool flag) // 곱셈을 이용한 최댓값 구하기
{
    int ret = 0;

    int prev = v.front();
    for (int i = 1; i < v.size(); i++) // 두 번째 값부터 (v.size >= 2)
    {
        int curr = v[i];
        if (flag && curr == 1)
        {
            ret += v.size() - i;
            break;
        }
        // else if (!flag && curr == 0) // 현재 값이 0인 경우, 탈출 (더 이상의 연산이 필요 없기 때문)
        //     return ret;

        if (i & 1) // 현재 값이 두 번째일 경우 (x o x o..)
            ret += prev * curr, prev = 0;
        else // 현재 값이 첫 번째일 경우
            prev = curr;
    }

    ret += prev; // 남아 있는 이전값 더하기 (n % 1일 경우 값이 남아 있으며, !(n % 1)일 경우 값은 0)

    return ret;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 수열의 크기 (1 <= 10k)
    cin >> n;
    vector<int> v1, v2; // v1은 0을 포함한 양수, v2는 음수 (-10k <= 10k)
    if (n == 1)
    {
        int k;
        cin >> k, cout << k;
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (k >= 1)
            v1.push_back(k);
        else
            v2.push_back(k);
    }
    sort(v1.begin(), v1.end(), greater<int>()); // 내림차
    sort(v2.begin(), v2.end());                 // 오름차

    int l = 0, r = 0;
    if (!v1.empty())
        l = get_result(v1, true);
    if (!v2.empty())
        r = get_result(v2, false);

    cout << l + r;
}

// 5 -5 -3 -2 0 0
// ans: 15

// 4%
// 2 -1 -1
// ans: 1

// 31%
// 4 1 1 1 1
// ans: 4

// 59%
// 5 1 1 1 1 1
// ans: 5
