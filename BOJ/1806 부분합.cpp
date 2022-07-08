// 1806 부분합
// https://www.acmicpc.net/problem/1806
/*
    투 포인터 (2,412KB, 8ms)
    시간 복잡도: O(2n)
    풀이)
    1) 입력된 수열의 첫 번째 값부터 s 이상이 될 때까지 sum에 저장.
    만약 s 이상이 안된 경우, s를 만들 수 없으므로 0을 출력.
    - l은 수열의 첫 번째 위치, r은 s 이상의 값을 만들 때 사용한 마지막 값의 위치를 가짐.
    2) s 이상을 만들 때 사용한 값의 개수를 ans에 저장. (단, min을 이용하여 이전값과 비교)
    3) 우측으로 한칸 씩 이동하는 느낌으로, sum에서 l번째 값을 빼주며 r+1번째 값을 더해준다. (이후 l++, r++)
    단, r+1번째 값은 sum < s일 경우에만 수행한다.
    r+1번째를 더해주지 않는 경우는 sum >= s일 것이며, l값을 빼도 sum >= s일 수 있다.
    즉, ans의 갱신이 가능한 최소 길이가 될 수 있으므로, r+1번째 값을 추가하여 길이를 늘리지 않는다.
    4) l < n이면서 l <= r(즉 최소 길이가 1 이상)일 경우 2)를 반복.
    etc.) 슬라이딩 윈도우인가 싶지만, 슬라이딩 윈도우는 간격이 항상 동일하다고 한다.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321

int main()
{
    FAST_IO;

    int n, s; // 수열의 길이 n(10 ≤ n < 100,000), 합 s(0 < s ≤ 100,000,000)
    cin >> n >> s;
    vector<int> v(n); // 수열 (1 ≤ v[i] ≤ 10,000)
    for (auto &i : v)
        cin >> i;

    int ans = INF; // 가장 짧은 부분합 길이
    int l = 0, r = 0;
    int sum = v[r];
    while (r + 1 < n && sum < s) // s 이상의 값이 나올 때까지 값을 더해줌 (+ OOB)
        r++, sum += v[r];
    while (l <= r && l < n) // 길이가 1이거나 OOB 직전까지
    {
        if (sum >= s) // 현재 합이 s 이상인 경우 (= 길이 갱신 가능)
            ans = min(ans, 1 + r - l);

        if (r + 1 < n && sum < s) // 합이 s 미만인 경우 (+ OOB)
            r++, sum += v[r];
        sum -= v[l], l++;
    }

    cout << (ans == INF ? '0' : ans);
}