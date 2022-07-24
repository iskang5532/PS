// 2022-07-23
// 23254 나는 기말고사형 인간이야
// https://www.acmicpc.net/problem/23254
/*
    그리디 (6,788KB, 784ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 큐에 저장한 후, 얻을 수 있는 점수를 기준으로 내림차순 정렬.
    주의할 점은, 100점을 넘기게 되면 더 이상 점수는 얻을 수 없음.
    - 큐에서 현재 점수 a, 시간당 얻는 점수 b를 꺼냄.
    - 1시간을 소모하여 점수를 획득함.
    만약 현재 점수에서 b를 얻어도 100점이 안 될 시, 점수 b를 얻은 후, 큐에 넣음.
    만약 현재 점수에서 b를 얻을 시 100점 이상이 될 시, 100점까지 부족한 점수만큼 획득.
    etc.) sort()로 이래저래 해보려다가 실패. 시간복잡도 계산이 헷갈림
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 200'003 // max n

struct cmp
{
    bool operator()(const pii &p1, const pii &p2)
    {
        return min(100 - p1.first, p1.second) < min(100 - p2.first, p2.second); // 얻을 수 있는 점수를 기준으로 내림차순 정렬
    };
};

int main()
{
    FAST_IO;

    int n, m; // 시간 n, 개수 m (1 ≤ n, m ≤ 200,000)
    cin >> n >> m;
    n *= 24;

    int tot = 0;
    vector<pii> v(m); // 기본 점수 및 오르는 점수
    for (auto &[a, b] : v)
        cin >> a, tot += a;
    for (auto &[a, b] : v)
        cin >> b;

    priority_queue<pii, vector<pii>, cmp> pq;
    for (const auto &elem : v)
        pq.push(elem);

    while (n-- && pq.size())
    {
        auto [a, b] = pq.top();
        pq.pop();

        if (a + b < 100)
            pq.push({a + b, b}), tot += b;
        else
            tot += 100 - a;
    }

    cout << tot;
}

// sol.2) sol.1 최적화 (6,788KB, 80ms)
#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 200'003 // max n

struct cmp
{
    bool operator()(const pii &p1, const pii &p2)
    {
        return min(100 - p1.first, p1.second) < min(100 - p2.first, p2.second);
    };
};

int main()
{
    FAST_IO;

    int n, m; // 시간 n, 개수 m (1 ≤ n, m ≤ 200,000)
    cin >> n >> m;
    n *= 24;

    int tot = 0;
    vector<pii> v(m); // 기본 점수 및 오르는 점수
    for (auto &[a, b] : v)
        cin >> a, tot += a;
    for (auto &[a, b] : v)
        cin >> b;

    priority_queue<pii, vector<pii>, cmp> pq;
    for (const auto &elem : v)
        pq.push(elem);

    while (n && pq.size())
    {
        auto [a, b] = pq.top();
        pq.pop();

        if (a + b < 100)
        {
            int cnt = min(n, (100 - a) / b);
            tot += b * cnt, n -= cnt;
            pq.push({a + b * cnt, b});
        }
        else
            tot += 100 - a, n--;
    }

    cout << tot;
}