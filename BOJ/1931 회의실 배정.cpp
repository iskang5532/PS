// 1931 회의실 배정
// https://www.acmicpc.net/problem/1931
/*
    sol.1) 그리디 (2,804KB, 24ms)
    시간 복잡도: ?
    풀이)
    - 입력된 st값과 ed값을 v에 저장한 후 정렬.
    정렬은 ed값 기준 오름차순 정렬. 만약 ed값이 같을 경우 st값을 기준으로 오름차순 정렬. (st값 정렬이 필요한 이유는, st == ed일 수도 있으므로)
    - 값을 하나씩 꺼내며, 현재 st가 이전 값의 ed(= r)보다 크거나 같은 경우, r값을 갱신해주며 ans++.
    r값보다 작은 st값은 사용할 수 없으므로 제외하며, 크거나 같을 때 r 이후의 시간대이므로 사용할 수 있게 됨.
    st와 r이 같을 때도 갱신하는 이유는, v의 st와 ed가 서로 같을 수 있기 때문. (st == ed)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct pii
{
    int st, ed;
    friend bool operator<(const pii &p1, const pii &p2) { return p1.ed != p2.ed ? p1.ed < p2.ed : p1.st < p2.st; } // ed 기준 오름차순 정렬 및  st 기준 오름차순 정렬)
};

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<pii> v(n);
    for (auto &[st, ed] : v)
        cin >> st >> ed;

    sort(v.begin(), v.end());

    int ans = 0;
    for (int pos = 0, r = 0; pos < n; pos++) // pos: v[], r: 이전 ed값
    {
        auto [st, ed] = v[pos]; // cur
        if (r <= st)
            r = ed, ans++;
    }

    cout << ans;
}

/*
    sol.2) 그리디, 우선순위 큐 (3,684KB, 32ms)
    시간 복잡도: ?
    풀이)
    - 입력된 st값과 ed값을 우선순위 큐 pq에 저장.
    pq느 ed값을 기준으로 오름차순 정렬을 함. 만약 ed값이 같을 경우, st값을 기준으로 오름차순 정렬. (st값 기준 정렬이 필요한 이유는, st == ed일 수도 있으므로)
    - 이전 ed값을 저장할 r을 선언. (첫 값은 0)
    - 큐의 st값과 비교. 만약 r보다 작은 경우, pq.pop(). (st가 r값보다 작을 시, 사용할 수 없는 시간대이므로 큐에서 제외하는 과정.)
    위 조건을 만족하지 않을 때까지 반복.
    - 만약 큐에 값이 남아있을 경우, r값을 큐의 ed값으로 갱신시킨 후 pq.pop(), ans++.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define st first
#define ed second
using pii = pair<int, int>;

struct cmp
{
    bool operator()(const pii &p1, const pii &p2) { return p1.ed != p2.ed ? p1.ed > p2.ed : p1.st > p2.st; }
};

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    priority_queue<pii, vector<pii>, cmp> pq;
    for (int i = 0; i < n; i++)
    {
        int st, ed;
        cin >> st >> ed;
        pq.push({st, ed});
    }

    int ans = 0;
    int r = 0; // 이전 ed값
    while (pq.size())
    {
        while (pq.size() && pq.top().st < r) // r 이전의 시간대는 모두 뺌
            pq.pop();

        if (pq.size())
        {
            r = pq.top().ed, pq.pop();
            ans++;
        }
    }

    cout << ans;
}

// 2
// 1 4
// 3 3
// ans: 1

// 15
// 1 4
// 7 7
// 3 5
// 0 6
// 5 7
// 3 8
// 5 9
// 6 10
// 8 11
// 8 12
// 7 7
// 7 7
// 7 7
// 2 13
// 12 14
// ans: 8
