/*
    2109 순회강연
    그리디? (2,224KB, 20ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2109
    풀이)
    - 탑-다운 느낌으로 풀이.
    1) 입력한 정보를 배열(= arr)에 저장 및 정렬시킴.
    비용을 기준으로 내림차순 정렬이며, 비용이 같을 경우 날짜를 기준으로 내림차순.
    - 입력된 정보에서 가장 높은 날짜를 저장 (= day)
    2) 마지막 날짜부터 1일째까지 역으로 강연을 잡아줌.
    조건(d >= day)에 만족하는 강연을 arr에서 탐색하며, 조건을 만족하는 첫 번째 강연은 비용이 가장 높을 것이다. (정렬했기 때문)
    그러므로 비용을 ans에 저장해주며, 해당 강연의 정보를 arr에서 제거.
    day에 강연을 잡았으므로, day-1번부터 다시 탐색. (같은 날에 강연을 두 번 할 수 없으므로 break)
    3) 이후 가능한 모든 날짜에 강연을 잡아줄 수 있도록 2)를 반복하며, 첫째 날까지 탐색을 마친 경우 ans를 출력.
    etc.) pq를 이용하여 푸는 문제인듯 싶은데 떠오르질 않는다.
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

struct pii
{
    int p, d; // 비용 및 날짜 (1 ≤ p, d ≤ 10k)
};

bool cmp(const pii &p1, const pii &p2) // 비용을 기준으로 내림차순 정렬 (같을 경우 날짜 내림차순)
{
    if (p1.p == p2.p)
        return p1.d > p2.d;
    return p1.p > p2.p;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 대학의 개수 (0 ≤ n ≤ 10k)
    cin >> n;

    int day = 0; // 대학에서 요청한 가장 높은 날짜
    vector<pii> arr(n);
    for (auto &[p, d] : arr)
    {
        cin >> p >> d;
        day = max(day, d);
    }

    sort(arr.begin(), arr.end(), cmp);

    int ans = 0;
    while (day != 0) // 마지막 날짜부터 시작하여 첫째 날까지 채움
    {
        for (int i = 0; i < arr.size(); i++) // day에 강연할 대학을 선택
            if (arr[i].d >= day)             // 강연 가능한 날짜인 경우, 강연 수락 (<day일 경우 시간이 지나서 강연 불가)
            {
                ans += arr[i].p;
                arr.erase(arr.begin() + i); // 현재 강연을 제거
                break; // day의 강연은 정했으므로 break
            }
        day--;
    }

    cout << ans;
}