// 11000 강의실 배정, 19598 최소 회의실 개수
// https://boj.kr/11000 https://boj.kr/19598
/*
    sol.1) 그리디 (5,252KB, 60ms)
    시간 복잡도: ?
    풀이)
    0) 시작 시간 st와 종료 시간 ed를 입력받아 v에 저장.
    1) 시작 시간 st를 기준으로 오름차순 정렬.
    2) v의 값을 하나씩 가져옴.
     - 첫 번째 값일 시 큐에 저장.
     - 두 번째 값부터는 큐에 존재하는 값과 비교함.
     만약 pq.top()이 현재 구간의 st보다 작거나 같은 경우, 큐에서 값을 뺌. (= pq.top() <= st)
     이는 현재 탐색중인 시간대와 큐에 존재하는 시간대가 겹치지 않음을 의미.
     위 조건이 만족하지 않을 때까지 큐의 값을 계속 뺌.
    3) 큐에 존재하는 값은 결국 서로 겹치는 구간이며, 이는 사용해야 할 강의실의 개수이다.
    그러므로 큐의 크기가 가장 커지는 순간을 기록한 후 출력해준다.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>; // {st, ed}: 시작 시간 st, 종료 시간 ed (0 ≤ st < ed ≤ 10^9)

int main()
{
    FAST_IO;

    int n; // 수업의 수
    cin >> n;
    vector<pii> v(n);
    for (auto &[st, ed] : v)
        cin >> st >> ed;
    sort(v.begin(), v.end()); // 시작 시간 st 기준 오름차순 정렬

    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (const auto &[st, ed] : v)
    {
        while (pq.size() && pq.top() <= st) // 현재 시간대가 이전 시간대와 겹치는 부분이 없는 경우
            pq.pop();                       // 겹치는 부분이 나올 때까지 이전의 값 제거

        pq.push(ed);

        ans = max(ans, (int)pq.size());
    }

    cout << ans;
}

/*
    sol.2) ? (8,292KB, 76ms)
    시간 복잡도: ?
    풀이)
    - 시간 st와 ed의 값에 +1 및 -1을 넣어 최대로 값이 커지는 구간을 저장함.
    - 배열에 값을 저장한 후에 완전 탐색으로 풀려 했으나, 입력될 시간의 값이 클 경우 MLE.
    그러므로 배열을 생성하지 않고 큐에 저장된 값을 이용함.
    1) st와 ed를 입력받아 우선순위 큐인 pq에 저장. (오름차순 정렬)
    2) 큐의 값을 하나씩 가져옴.
    현재 값이 st인 경우, cnt++.
    현재 값이 ed인 경우, cnt--.
    - 가장 큰 cnt값을 ans에 저장한 후, ans 출력.
    - 중복된 값이 있을 수 있으므로, 같은 값이 pq에 존재하지 않을 때까지 재탐색.
    etc.) 22.02.10
    - 완탐인가 그리디인가
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define ST 0
#define ED 1
using pii = pair<int, int>;

struct cmp
{
    bool operator()(const pii &p1, const pii &p2) { return p1.first > p2.first; }
};

int main()
{
    FAST_IO;

    int n; // 수업의 수
    cin >> n;

    int mx = 0; // 가장 긴 종료 시간
    priority_queue<pii, vector<pii>, cmp> pq;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        pq.push({a, ST}), pq.push({b, ED});
        mx = max(mx, b);
    }

    int ans = 0, cnt = 0;
    while (pq.size())
    {
        auto [pos, b] = pq.top();
        pq.pop();
        b == ST ? cnt++ : cnt--;

        while (pq.size() && pos == pq.top().first) // 같은 값이 존재할 경우
        {
            b = pq.top().second;
            b == ST ? cnt++ : cnt--;
            pq.pop();
        }

        ans = max(ans, cnt);
    }

    cout << ans;
}