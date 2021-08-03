/* 
 * 12738 가장 긴 증가하는 부분 수열 3
 * LIS
 * 시간 복잡도: nlogn
 * 문제: https://www.acmicpc.net/problem/12738
 * ETC) lower_bound를 이용하여 자리를 찾는 방법이 신선했으며, lower_bound에 대한 개념 이해가 헷갈림
 * 참고: https://seungkwan.tistory.com/8
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

    vector<int> lis(n);
    int len = 0; // 수열 lis에 저장된 값의 개수 (= lis의 길이)
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        // 입력된 값 k를 lis의 길이(len)만큼의 범위를 탐색하여 위치를 찾아줌
        auto pos = lower_bound(lis.begin(), lis.begin() + len, k);
        *pos = k; // 위치에 값을 넣음

        if (pos == lis.begin() + len) // 값을 넣은 위치가 lis의 마지막 위치인 경우 (= 수열(lis)의 길이가 늘어남)
            len++;
    }

    cout << len;
}

// lower_bound
// 범위 내에 k 이상의 값을 가지고 있는 값의 위치를 반환.
// 없을 경우, 마지막 위치를 반환