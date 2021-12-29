// 20186 수 고르기
// https://www.acmicpc.net/problem/20186
/*
    정렬 (2,160KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 값을 선택할 시, 이전에 선택한 값의 개수를 세어 줘야 한다. 이는 모든 값을 계산한 후, 한 번에 처리해도 가능하다.
    1) 입력된 값 중 k개의 큰 값을 선택하여 더해줌.
    2) k*(k-1)/2를 빼줌. (값의 왼쪽에 선택된 값의 개수만큼 빼줘야 하며, 이는 즉 1:k-1개가 됨.)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // accumulate

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;

    sort(arr.begin(), arr.end(), greater<int>());
    int ans = accumulate(arr.begin(), arr.begin() + k, 0);
    ans -= k * (k - 1) >> 1; // 1:k-1까지의 합

    cout << ans;
}