/*
    11000 강의실 배정
    그리디 (5,252KB, 60ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/11000
    etc.)
    1) 시작 시간을 기준으로 정렬. (= arr)
    2) 값을 하나씩 가져옴.
     - 첫 번째 값일 시 큐에 넣음.
     - 두 번째 값부터는 큐에 존재하는 값과 비교함.
     만약 큐의 첫 번째 값의 t값이 현재 값의 s보다 작거나 같은 경우, 값을 빼줌. (= 겹치지 않음)
     이 조건이 만족하지 않을 때까지 큐의 값을 계속 받아옴. (혹은 큐가 비거나)
    3) 큐에 존재하는 값은 결국 서로 겹치는 구간이며, 이는 사용해야 할 강의실의 개수이다.
    그러므로 큐의 크기가 가장 커지는 순간을 기록한 후 출력해준다.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

struct pii
{
    int s, t; // 시작시간 S, 끝나는 시간 T(0 ≤ Si < Ti ≤ 10^9)
};

bool _greater_s(const pii &p1, const pii &p2) { return p1.s < p2.s; } // s 기준 오름차
struct _greater_t
{
    bool operator()(const pii &p1, const pii &p2) { return p1.t > p2.t; } // t 기준 오름차
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 수업의 수 N(1 ≤ N ≤ 200k)
    cin >> n;
    vector<pii> arr(n);
    for (auto &[s, t] : arr)
        cin >> s >> t;
    sort(arr.begin(), arr.end(), _greater_s);

    int ans = 0; // 사용해야 할 강의실 최대 개수
    priority_queue<pii, vector<pii>, _greater_t> pq;
    for (const auto &[s, t] : arr)
    {
        while (!pq.empty() && pq.top().t <= s) // 현재 시간대가 이전 시간대와 겹치는 부분이 없는 경우
            pq.pop();                          // 겹치는 부분이 나올 때까지 이전의 값 제거
        pq.push(pii{s, t});

        ans = max(ans, (int)pq.size());
    }

    cout << ans;
}